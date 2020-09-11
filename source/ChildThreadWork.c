#include"../include/ChildThreadWork.h"
#include "../include/TaskQueue.h"
#include "../include/MyLog.h"
#include <sys/sendfile.h>
#include <string.h>

static const char ware_house[32] = "../warehouse/";
//thread clean

void CleanUpFunc(void *arg) {
    TaskQueue_t *task_queue = (TaskQueue_t *)arg;
#ifdef DEBUG
    printf("%d quit!\n", (int)pthread_self());
#endif
    pthread_mutex_unlock(&task_queue->mutex);
}

void *ChildThreadFunc(void *arg) {
    TaskQueue_t *task_queue = (TaskQueue_t *)arg;
    QueNode_t *work_task;
    Msg_t my_msg;
    int socket_sfd = -1;

    int log_fd = -1;
    //test client
    MYSQL *mysql_conn = NULL;
    char client_path[32];
    char client_curpath[128];
    pthread_cleanup_push(CleanUpFunc, task_queue);
    for( ; 1 ; ) {
        pthread_mutex_lock(&task_queue->mutex);
        if(TaskQueueEmpty(task_queue)) {
            pthread_cond_wait(&task_queue->cond_variable, &task_queue->mutex);
            if(1 == task_queue->exit_flag)
                pthread_exit(NULL);
        }
        int get_success = TaskQueuePop(task_queue, &work_task);
        if(get_success != -1) {
#ifdef DEBUG
            printf("%d get task!\n", (int)pthread_self());
#endif

            socket_sfd = work_task->client_sfd;
            log_fd  = work_task->log_fd;
            mysql_conn = work_task->mysql_conn;
            memset(&my_msg, 0, sizeof(my_msg));

            int login_success = 0;
#ifdef DEBUG
            printf("client_fd = %d log_fd = %d\n", socket_sfd, log_fd);
#endif
            memset(client_path, 0, sizeof(client_path));
            memset(client_curpath, 0, sizeof(client_curpath));
            login_success = ClientLoginHandler(socket_sfd, mysql_conn, client_path);

            if(login_success != -1) {

                printf("client  has connect, his operator dir: %s\n", client_path);
                strcat(client_path, "/");
                strcpy(client_curpath, client_path);
                
                ClientCmdHandle(socket_sfd,log_fd, mysql_conn, client_path, client_curpath, &my_msg);            
            }
#ifdef DEBUG 
            printf("%d finish task!\n", (int)pthread_self()); 
#endif
            free(work_task);
            socket_sfd  = -1;
            log_fd = -1;
            work_task = NULL;
        }
        pthread_mutex_unlock(&task_queue->mutex);
    }
    pthread_cleanup_pop(1);

}
int ClientLoginHandler(int socket_sfd, MYSQL *mysql_conn, char *client_path) {
    Msg_t msg;
    Msg_t *pMsg = &msg;
    memset(pMsg, 0, sizeof(Msg_t));

    //接收客户端发来的账号
    ReceiveFixedSized(socket_sfd, &pMsg->len, 4) ;
    ReceiveFixedSized(socket_sfd, &pMsg->cmd, 4);
    ReceiveFixedSized(socket_sfd, pMsg->data, pMsg->len);


    char account[16];
    char salt[32];
    memset(account, 0, sizeof(account));
    memset(salt, 0 ,sizeof(salt));

    strcpy(account, pMsg->data);
    int send_sz = 0;
    int ret = GetSaltFromDataBase(mysql_conn, pMsg->data, salt);
    memset(pMsg, 0, sizeof(Msg_t));
    if(ret == -1) {
        pMsg->len = 0;
        pMsg->cmd = CMDERROR;
        send_sz = send(socket_sfd, pMsg, 8+pMsg->len, MSG_WAITALL);
        if(send_sz == -1) {
#ifdef DEBUG
            printf("client has quit!\n");
#endif
        }

        return -1;
    }
    pMsg->len = strlen(salt);
    pMsg->cmd = CMDLOGIN;
    strcpy(pMsg->data, salt);
    send_sz = send(socket_sfd, pMsg, 8+pMsg->len, MSG_WAITALL);
    if(send_sz == -1) {
#ifdef DEBUG

        printf("client has quit!\n");
#endif
        return -1;
    }


    memset(pMsg, 0, sizeof(Msg_t));

    // 接收客户端发来的密文
    ReceiveFixedSized(socket_sfd, &pMsg->len, 4) ;
    ReceiveFixedSized(socket_sfd, &pMsg->cmd, 4);
    ReceiveFixedSized(socket_sfd, pMsg->data, pMsg->len);

    char crypt[128];
    memset(crypt, 0 ,sizeof(crypt));
    ret = GetCryptFromDataBase(mysql_conn, account,  crypt);
    if(strcmp(crypt, pMsg->data) == 0) {
#ifdef DEBUG
        printf("client: %s passwd right!\n", account);
#endif
        memset(pMsg, 0, sizeof(Msg_t));
        pMsg->len = 0;
        pMsg->cmd = CMDLOGIN;
        send_sz = send(socket_sfd, pMsg, 8+pMsg->len, MSG_WAITALL);
        if(send_sz == -1) {
#ifdef DEBUG
            printf("client has quit!\n");
#endif
            return -1;
        }
        strcpy(client_path,account);
        return 0;
    }
#ifdef DEBUG
    printf("client: %s passwd failure!\n", account);
#endif
    memset(pMsg, 0, sizeof(Msg_t));
    pMsg->len = 0;
    pMsg->cmd = CMDERROR;
    send_sz = send(socket_sfd, pMsg, 8+pMsg->len, MSG_WAITALL);
    if(send_sz == -1) {
#ifdef DEBUG

        printf("client has quit!\n");
#endif
        return -1;
    }
    return -1;

}

int ClientCmdHandle(int socket_sfd, int log_fd, MYSQL *conn,  char *client_path, char *client_curpath,Msg_t *pMsg) {
    char account[32];
    char log_info[512];
    time_t cur_time;
    memset(account, 0, sizeof(account));
    strcpy(account, client_path);
    account[strlen(account) - 1] = '\0';
    InsertRecordToLogTable(conn, account, "LOGIN", pMsg->data);
    for(; ;) {
        time(&cur_time);
        ReceiveFixedSized(socket_sfd, &pMsg->len, 4) ;
        ReceiveFixedSized(socket_sfd, &pMsg->cmd, 4);
        ReceiveFixedSized(socket_sfd, pMsg->data, pMsg->len);
#ifdef DEBUG
        printf("msg.len: %d, msg.cmd: %d, data: %s\n", pMsg->len, pMsg->cmd, pMsg->data);
#endif
        /* char trans_file_path[128]; */
        memset(log_info, 0, sizeof(log_info));

        switch(pMsg->cmd) {
        case CD:
            InsertRecordToLogTable(conn, account, "CD", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "cd", pMsg->data, ctime(&cur_time));
            handler_cmd_cd(socket_sfd, ware_house, pMsg->data, client_path, client_curpath);     
            break;
        case LS:
            InsertRecordToLogTable(conn, account, "LS", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "ls", pMsg->data, ctime(&cur_time));
            handler_cmd_ls(socket_sfd, ware_house, client_curpath);         
            break;
        case PUTSFILE:
            InsertRecordToLogTable(conn, account, "PUTSFILE", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "putsfile", pMsg->data, ctime(&cur_time));
            handle_cmd_putsfile(socket_sfd, ware_house, client_curpath, pMsg->data, pMsg);            
            break;
        case PUTSDIR:
            InsertRecordToLogTable(conn, account, "PUTSDIR", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "putsdir", pMsg->data, ctime(&cur_time));
            handler_cmd_putsdir(socket_sfd, ware_house, client_curpath, pMsg->data, pMsg);
            break;

        case GETSFILE:
            InsertRecordToLogTable(conn, account, "GETSFILE", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "getsfile", pMsg->data, ctime(&cur_time));
            handler_cmd_continue_getsfile(socket_sfd, ware_house, client_curpath, pMsg->data);
            break;
        case GETSDIR:
            InsertRecordToLogTable(conn, account, "GETSDIR", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "getsdir", pMsg->data, ctime(&cur_time));
            handler_cmd_getsdir(socket_sfd, ware_house, client_curpath, pMsg->data);
        case PWD:
            InsertRecordToLogTable(conn, account, "PWD", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "pwd", pMsg->data, ctime(&cur_time));
            handler_cmd_pwd(socket_sfd, ware_house, client_curpath);
            break;
        case REMOVE:
            InsertRecordToLogTable(conn, account, "REMOVE", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "remove", pMsg->data, ctime(&cur_time));
            handler_cmd_remove(socket_sfd, ware_house, client_curpath, pMsg->data);
            break;
        case MKDIR:
            InsertRecordToLogTable(conn, account, "MKDIR", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "mkdir", pMsg->data, ctime(&cur_time));
            handler_cmd_mkdir(socket_sfd, ware_house,client_curpath, pMsg->data);            
            break;
        case CMDERROR:
            InsertRecordToLogTable(conn, account, "CMDERROR", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "CMDERROR", pMsg->data, ctime(&cur_time));
            return 0;
        case CMDQUIT:
            InsertRecordToLogTable(conn, account, "QUIT", pMsg->data);
            sprintf(log_info, "%s %s %s %s", account, "CMDQUIT", pMsg->data, ctime(&cur_time));
            return 0;
        default :
            break;
        }
        WriteClientOperInfoToLog(log_fd, log_info, strlen(log_info));
        memset(pMsg, 0, sizeof(Msg_t));
    }
    return 0;
}

int handler_cmd_getsdir(int socket_sfd, const char *ware_house, const char *client_curpath, const char *dir_path) {
    Msg_t msg;
    Msg_t *pMsg = &msg;
    handler_cmd_getsdir_core(socket_sfd, ware_house, client_curpath, dir_path, pMsg);
    pMsg->len = 0;
    pMsg->cmd = CMDEOF;
    int send_sz = send(socket_sfd, pMsg, 8, 0);
    if(send_sz == -1) {
#ifdef DEBUG
        printf("client has closed!\n");
#endif
    }
    else {
#ifdef DEBUG
        printf("Gets Dir %s over!\n", dir_path);
#endif
    }
    return 0;


}

int handler_cmd_getsdir_core(int socket_sfd,const char *ware_house, const char *client_curpath, const char *dir_name, Msg_t *pMsg) {
    memset(pMsg, 0, sizeof(Msg_t));
    pMsg->len = strlen(dir_name);
    pMsg->cmd = PUTSDIR;
    memcpy(pMsg->data, dir_name, pMsg->len);
#ifdef DEBUG
    printf("transfer dir: %s\n", pMsg->data);
#endif
    int send_sz = send(socket_sfd, pMsg, 8+pMsg->len, 0);
    if(send_sz == -1){
#ifdef DEBUG
        printf("server has closed!\n");
#endif
        exit(-1);
    }

    struct dirent *cur_dirent = {0};

    char total_dir_path[128];
    memset(total_dir_path, 0, sizeof(total_dir_path));

    sprintf(total_dir_path, "%s%s%s", ware_house, client_curpath, dir_name);
    DIR *dirp = opendir(total_dir_path);

    char new_dir_path[128];
    char new_file_path[128];
    while((cur_dirent = readdir(dirp)) != NULL) {
        if(strcmp("..", cur_dirent->d_name) == 0 || strcmp(".", cur_dirent->d_name) == 0) {
            continue;
        }
        if(cur_dirent->d_type == 4) {
            memset(new_dir_path, 0, sizeof(new_dir_path));
            sprintf(new_dir_path, "%s/%s", dir_name, cur_dirent->d_name);
            handler_cmd_getsdir_core(socket_sfd, ware_house, client_curpath,new_dir_path, pMsg);
        } else {
            memset(new_file_path, 0 ,sizeof(new_file_path));
            sprintf(new_file_path, "%s/%s", dir_name, cur_dirent->d_name);
#ifdef DEBUG
            printf("transfer child file: %s\n", new_file_path);
#endif
            memset(pMsg, 0, sizeof(Msg_t));
            pMsg->len = strlen(new_file_path);
            pMsg->cmd = PUTSFILE;

            memcpy(pMsg->data, new_file_path, pMsg->len);
            send_sz = send(socket_sfd, pMsg, 8+pMsg->len, 0);
            if(send_sz == -1){
#ifdef DEBUG
                printf("client has closed!\n");
#endif
                break;
            }
            handler_cmd_getsfile(socket_sfd, ware_house, client_curpath, new_file_path);
        }
    }
    closedir(dirp);
    return 0;

}

int handler_cmd_continue_getsfile(int socket_sfd, const char *ware_house, const char *client_curpath, const char *file_path) {

    Msg_t msg;
    Msg_t *pMsg = &msg;
    memset(pMsg, 0, sizeof(Msg_t));
    char file_name[128];
    memset(file_name, 0, sizeof(file_name));
    sprintf(file_name, "%s%s%s", ware_house, client_curpath, file_path); 



    ReceiveFixedSized(socket_sfd, &pMsg->len, 4);  
    ReceiveFixedSized(socket_sfd, &pMsg->len, 4);
    ReceiveFixedSized(socket_sfd, pMsg->data, pMsg->len);

    int continue_pos = 0;
    memcpy(&continue_pos, pMsg->data, 4);

    struct stat stat_buf;
    memset(&stat_buf, 0, sizeof(stat_buf));
#ifdef DEBUG
    printf("filename= %s, len = %d\n",file_name, (int)strlen(file_name) );
#endif

    stat(file_name, &stat_buf);

    pMsg->cmd = PUTSFILE;
    pMsg->len = 4;

#ifdef  DEBUG
    printf("file_sz: %d\n", (int)stat_buf.st_size);
#endif
    int file_sz = stat_buf.st_size - continue_pos;
    memcpy(pMsg->data, &file_sz, pMsg->len);
#ifdef  DEBUG
    printf("client_cur_file_sz: %d\n", continue_pos);
#endif

#ifdef DEBUG
    printf("trans_file_sz = %d\n", file_sz);
#endif
    int send_sz = send(socket_sfd, pMsg, 8+pMsg->len, 0);
    if(send_sz == -1) {
        printf("client has closed !\n");
        return -1;
    }

    int cur_send_sz = 0;
    int fdr = open(file_name, O_RDWR, 0666);
    lseek(fdr, continue_pos -1, SEEK_SET);
    int read_sz = 0;
    while(cur_send_sz < file_sz) {
        read_sz = read(fdr, pMsg->data, sizeof(pMsg->data));
        pMsg->len = read_sz;
        pMsg->cmd = PUTSFILE;
        send_sz = send(socket_sfd, pMsg, 8+pMsg->len, 0);

        if(send_sz == -1) {
            printf("client has closed!\n");
            return -1;
        }
        cur_send_sz += (send_sz - 8);
    }

    printf("send file: %s over!\n", file_name);

    close(fdr);
    return 0;

}

int handler_cmd_getsfile(int socket_sfd,const char * ware_house, const char *client_curpath, const char *file_path) {

    Msg_t msg;
    Msg_t *pMsg = &msg;
    memset(pMsg, 0, sizeof(Msg_t));
    char file_name[128];
    memset(file_name, 0, sizeof(file_name));
    sprintf(file_name, "%s%s%s", ware_house, client_curpath, file_path); 

    struct stat stat_buf;
    memset(&stat_buf, 0, sizeof(stat_buf));
#ifdef DEBUG
    printf("filename= %s, len = %d\n",file_name, (int)strlen(file_name) );
#endif
    stat(file_name, &stat_buf);
    pMsg->cmd = PUTSFILE;
    pMsg->len = 4;
    int file_sz = stat_buf.st_size;
    memcpy(pMsg->data, &file_sz, pMsg->len);
#ifdef DEBUG
    printf("file_sz = %d\n", file_sz);
#endif
    int send_sz = send(socket_sfd, pMsg, 8+pMsg->len, 0);
    if(send_sz == -1) {
        printf("client has closed !\n");
        return -1;
    }

    int cur_send_sz = 0;
    int fdr = open(file_name, O_RDWR, 0666);
    int read_sz = 0;
    while(cur_send_sz < file_sz) {
        read_sz = read(fdr, pMsg->data, sizeof(pMsg->data));
        pMsg->len = read_sz;
        pMsg->cmd = PUTSFILE;
        send_sz = send(socket_sfd, pMsg, 8+pMsg->len, 0);

        if(send_sz == -1) {
            printf("server has closed!\n");
            return -1;
        }
        cur_send_sz += (send_sz - 8);
    }

    printf("send file: %s over!\n", file_name);

    close(fdr);
    return 0;

}





int HandleClientLs(char *basePath,int clientFd)
{
    DIR *dir;
    struct dirent *ptr;
    char base[1000];
    if ((dir=opendir(basePath)) == NULL)
    {
        perror("Open dir error...");
        closedir(dir);
        return -1;

    }

    Msg_t* msg = (Msg_t*)calloc(1,sizeof(Msg_t));
    while ((ptr=readdir(dir)) != NULL)
    {
        puts("read success");
        memset(msg,0,sizeof(Msg_t));
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8){    ///file
            sprintf(msg->data,"%s/%s\n",basePath,ptr->d_name);
            msg->len = strlen(msg->data);
            send(clientFd,msg,sizeof(Msg_t),0);
        }
        else if(ptr->d_type == 10){    ///link file
            sprintf(msg->data,"%s/%s\n",basePath,ptr->d_name);
            msg->len = strlen(msg->data);
            send(clientFd,msg,sizeof(Msg_t),0);
        }
        else if(ptr->d_type == 4)    ///dir
        {
            memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            sprintf(msg->data,"\033[1m\033[45;33m%s\033[0m\n",base);
            msg->len = strlen(msg->data);
            send(clientFd,msg,sizeof(Msg_t),0);
            //readFileList(base);
        }

    }
    //我的判断指令结束方法
    memset(msg,0,sizeof(Msg_t));
    msg->cmd = CMDEOF;
    send(clientFd,msg,sizeof(Msg_t),0);
    closedir(dir);
    free(msg);
    return 1;

}


int handler_cmd_ls(int socket_sfd, const char *ware_house, const char *client_curpath) {
    char total_file_path[128] = {0};
    sprintf(total_file_path, "%s%s", ware_house, client_curpath);
#ifdef DEBUG
    printf("ls dir_path: %s\n", total_file_path);
#endif
    total_file_path[strlen(total_file_path) -1] = 0;
    HandleClientLs(total_file_path, socket_sfd);
    return 0;
}

int HandleClientPutsFile(int socket_sfd,   const char *file_path, Msg_t *pMsg) {
    memset(pMsg, 0, sizeof(Msg_t));
    int newfd =  open(file_path,O_CREAT|O_RDWR,0666);

    ReceiveFixedSized(socket_sfd, &pMsg->len, 4) ;
    ReceiveFixedSized(socket_sfd, &pMsg->cmd, 4);
    ReceiveFixedSized(socket_sfd, pMsg->data, pMsg->len);

    int des_file_sz = 0;
    memcpy(&des_file_sz, pMsg->data, pMsg->len);
#ifdef DEBUG
    printf("transfer_file size: %d\n", des_file_sz);
#endif

    int cur_file_sz = 0;
    while(cur_file_sz < des_file_sz) {
        memset(pMsg, 0, sizeof(Msg_t));
        ReceiveFixedSized(socket_sfd, &pMsg->len, 4) ;
        ReceiveFixedSized(socket_sfd, &pMsg->cmd, 4);
        ReceiveFixedSized(socket_sfd, pMsg->data, pMsg->len);
        int write_sz = write(newfd, pMsg->data, pMsg->len);
        cur_file_sz += write_sz;
    }
#ifdef DEBUG
    printf("transfer file : %s over!\n", file_path);
#endif
    close(newfd);

    return 0;
}



int handle_cmd_putsfile(int socket_sfd, const char *ware_house, const char *client_curpath, const char *file_path,Msg_t *pMsg) {
    char total_file_path[128] = {0}; 
    sprintf(total_file_path, "%s%s%s", ware_house, client_curpath, file_path);

#ifdef DEBUG
    printf("client want to puts %s\n", total_file_path);
#endif

    HandleClientPutsFile(socket_sfd, total_file_path, pMsg);
    return 0;

}

int  HandleClientPutsDir(int socket_sfd, const char *ware_house, const char *client_curpath, const char *dir_name,Msg_t *pMsg) {
    char path[256];
    while(1) {
        memset(pMsg, 0, sizeof(Msg_t));
        memset(path, 0, sizeof(path));
        ReceiveFixedSized(socket_sfd, &pMsg->len, 4) ;
        ReceiveFixedSized(socket_sfd, &pMsg->cmd, 4);
        ReceiveFixedSized(socket_sfd, pMsg->data, pMsg->len);
#ifdef DEBUG
        printf("transfer content %s\n", pMsg->data);
#endif
        if(pMsg->cmd == PUTSDIR) {
            sprintf(path, "%s%s%s", ware_house, client_curpath, pMsg->data);
#ifdef DEBUG

            printf("mkdir: %s\n", path);
#endif
            mkdir(path, 0777);
        } else if(pMsg->cmd == PUTSFILE){
            sprintf(path, "%s%s%s", ware_house, client_curpath, pMsg->data);

#ifdef DEBUG
            printf("mkfile: %s\n", path);
#endif
            HandleClientPutsFile(socket_sfd, path, pMsg);
        } else {
            printf("PutDir over!\n");
            break;
        }         

    }
    return 0;

}

int handler_cmd_putsdir(int socket_sfd, const char *ware_house, const char *client_curpath, const char *dir_name, Msg_t *pMsg) {
    HandleClientPutsDir(socket_sfd, ware_house, client_curpath, dir_name, pMsg);
    return 0;
}
/* int SubCmdString(Msg_t *pMsg, char *file_path) { */
/*     size_t i = 0; */
/*     for(; i!=pMsg->len; ++i) { */
/*         if(pMsg->data[i] == ' ') { */
/*             while(i+1 != pMsg->len && pMsg->data[i+1] == ' ') */
/*                 ++i; */
/*             ++i; */
/*             break; */
/*         } */
/*     } */
/*     sprintf(file_path, "%s%s%s", ware_house, client_curpath, pMsg->data + i); */
/*     /1* file_path[file_path_sz] = 0; *1/ */
/* #ifdef DEBUG */
/*     printf("client want to puts %s\n", file_path); */
/* #endif */

/*     return 0; */
/* } */




//判断是否存在文件夹
int judge_dir(const char *ware_house,char *client_curpath,char *recvpath)
{
    char total_client_curpath[128];
    memset(total_client_curpath, 0 ,sizeof(total_client_curpath));
    sprintf(total_client_curpath, "%s%s%s", ware_house, client_curpath, recvpath);
#ifdef DEBUG
    printf("cd total_path: %s\n", total_client_curpath);
#endif
    total_client_curpath[strlen(total_client_curpath)-1] = 0;
    DIR *dir;
    struct dirent *ptr;
    if ((dir=opendir(total_client_curpath)) == NULL)
    {
        perror("Open dir error...");
        closedir(dir);
        return -1;
    }
    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 4)    ///dir
        {
            if(strcmp(recvpath,ptr->d_name) ==0)
            {
                closedir(dir);
                return 1;
            }
            else break;
        }

    }
    closedir(dir);
    return 0;
}
int HandlerClientCd(char* recvpath,const char *ware_house,char *client_path,char* client_curpath,int clientFd)
{

    Msg_t* msg = (Msg_t*)calloc(1,sizeof(Msg_t));
    memset(msg,0,sizeof(Msg_t));
    if(strcmp(recvpath,".")==0){
        sprintf(msg->data,"cd sucess\n");
        msg->len = strlen(msg->data);
        send(clientFd,msg,sizeof(Msg_t),0);
    }
    else if(strcmp(recvpath,"..") == 0)
    {
        int cutnum =2;
        /* int slash_num = count_slash(client_curpath,cutnum,client_path); */
        if(strcmp(client_curpath,client_path)==0)
        {
            sprintf(msg->data,"in the root dir\n");
            msg->len = strlen(msg->data);
            send(clientFd,msg,sizeof(Msg_t),0);
            //发送命令结束标志
            memset(msg,0,sizeof(Msg_t));
            msg->cmd = CMDEOF;
            send(clientFd,msg,sizeof(Msg_t),0);
            return 0;
        }
        int pathlen = strlen(client_curpath);
        int now_slash_num = 0;
        //截断path
        for(int i = pathlen-1;i>=0;i--)
        {
            if(client_curpath[i] =='/')
                now_slash_num++;
            client_curpath[i] = '\0';
            if(now_slash_num == cutnum)
                break;
        }
        strcat(client_curpath, "/");
        sprintf(msg->data,"cd sucess\n");
        msg->len = strlen(msg->data);
        send(clientFd,msg,sizeof(Msg_t),0);
        printf("curpath = %s%s\n",ware_house,client_curpath);
    }
    else
    {
        //TODO
        int res = judge_dir(ware_house,client_curpath,recvpath);
        if( res ==0 )
        {
            sprintf(msg->data,"dir dose not exit\n");
            msg->len = strlen(msg->data);
            send(clientFd,msg,sizeof(Msg_t),0);
            //发送命令结束标志
            memset(msg,0,sizeof(Msg_t));
            msg->cmd = CMDEOF;
            send(clientFd,msg,sizeof(Msg_t),0);
            return -1;
        }
        strcat(client_curpath,recvpath);
        strcat(client_curpath,"/");
        //查找服务器端是否存在该目录
        sprintf(msg->data,"cd sucess\n");
        puts(client_curpath);
        msg->len = strlen(msg->data);
        send(clientFd,msg,sizeof(Msg_t),0);
    }
    //发送命令结束标志
    memset(msg,0,sizeof(Msg_t));
    msg->cmd = CMDEOF;
    send(clientFd,msg,sizeof(Msg_t),0);
    free(msg);
    return 0;
}

int handler_cmd_cd(int socket_sfd, const char *ware_house, char *des_path, char *client_path, char *client_curpath) {
    HandlerClientCd(des_path, ware_house, client_path, client_curpath, socket_sfd);
    return 0;

}
int handler_cmd_pwd(int clientFd,const char *ware_house, const char* client_curpath) {
    Msg_t msg ;
    Msg_t* pMsg = &msg;
    memset(pMsg,0,sizeof(Msg_t));
    sprintf(pMsg->data,"%s%s\n",ware_house,client_curpath);
    pMsg->len = strlen(client_curpath);
#ifdef DEBUG

    printf("%s\n",pMsg->data);
#endif
    send(clientFd,pMsg,sizeof(Msg_t),0);
    return 0;
}
int handler_cmd_mkdir(int clientFd,const char *ware_house,const char* client_curpath,const char* dirname)
{
    char buf[128] ={0};

    sprintf(buf,"%s%s%s",ware_house, client_curpath,dirname);
#ifdef DEBUG
    printf("mkdir : %s\n", buf);
#endif
    mkdir(buf,O_CREAT|0666);

    return 0;
}
int handler_cmd_remove(int clientFd,const char *ware_house,const char* client_curpath,const char* filename)
{
#ifdef DEBUG

    puts("removing");
#endif
    char buf[256] ={0};
    sprintf(buf,"%s%s%s",ware_house,client_curpath,filename);
#ifdef DEBUG
   printf("remove file : %s\n", buf);
#endif
    int ret = remove(buf);
    ERROR_CHECK(-1,ret,"remove");
    return 0;
}


