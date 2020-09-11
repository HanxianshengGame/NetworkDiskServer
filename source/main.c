#include "../include/ThreadPool.h"
#include "../include/TCPServer.h"
#include "../include/Epoll.h"
#include "../include/MyLog.h"
#include "../include/DataBaseWork.h"
int pipe_fds[2];
void SigHandleFunc(int signal_num) {
#ifdef DEBUG
    printf("%d SIG is coming!\n", signal_num);
#endif
    write(pipe_fds[1], "exit", 4);
}
int main(int argc, char **argv)
{
    ARGS_CHECK(argc, 4);
    
    pipe(pipe_fds);
    if(fork()) {
        close(pipe_fds[0]);
        signal(SIGUSR1, SigHandleFunc);
        wait(NULL);
#ifdef  DEBUG
        printf("parent process has exit!\n");
#endif
        close(pipe_fds[1]);
        exit(0);
    }

    
    close(pipe_fds[1]);

    MYSQL *mysql_conn = NULL;
    int conn_ret = ConnectDataBase(&mysql_conn, "localhost", "root", "525907", "file_server_database");
    ERROR_CHECK(conn_ret, -1, "connect database");
#ifdef DEBUG
    printf("Database connect success!\n");
#endif
    
    int log_fd = -1;
    StartMyLog(&log_fd, "../Log");
#ifdef DEBUG
    printf("Log Start!\n");
#endif
    ThreadPool_t thread_pool;
    int thread_num = atoi(argv[3]);
    ThreadPoolInit(&thread_pool, thread_num);
    ThreadPoolStart(&thread_pool, thread_num);
    

#ifdef DEBUG
    printf("ThreadPool create success!\n");
#endif
    
    int server_fd; 
    TCPServerBuild(&server_fd, argv[1], atoi(argv[2]));

    int epoll_fd;
    EpollBuild(&epoll_fd);
    struct epoll_event epoll_event;
    EpollAddListener(epoll_fd, &epoll_event, server_fd, EPOLLIN);
    EpollAddListener(epoll_fd, &epoll_event, pipe_fds[0], EPOLLIN);
    
    int client_fd; 
    struct epoll_event response_event;
    memset(&response_event, 0, sizeof(response_event));

    int response_num;
    for(; 1 ;) {
        response_num = epoll_wait(epoll_fd, &response_event, 1, -1);
        ERROR_CHECK(response_num, -1, "epoll_wait");
        if(response_event.data.fd == server_fd) {

            client_fd = accept(server_fd, NULL, NULL);
            QueNode_t *task_node = (QueNode_t *)calloc(1, sizeof(QueNode_t));
            task_node->client_sfd = client_fd;
#ifdef DEBUG
            printf("new task client_sfd: %d\n", client_fd);
#endif
            task_node->log_fd = log_fd;
            task_node->mysql_conn = mysql_conn;

            pthread_mutex_lock(&thread_pool.task_queue.mutex);
            TaskQueuePush(&thread_pool.task_queue, task_node);
            pthread_cond_signal(&thread_pool.task_queue.cond_variable);
            pthread_mutex_unlock(&thread_pool.task_queue.mutex);        

        } else if(response_event.data.fd == pipe_fds[0]){
            
          pthread_mutex_lock(&thread_pool.task_queue.mutex);
           thread_pool.task_queue.exit_flag = 1;
           pthread_cond_broadcast(&thread_pool.task_queue.cond_variable);
           pthread_mutex_unlock(&thread_pool.task_queue.mutex);
           for(int i = 0; i!= thread_num; ++i)
               pthread_join(thread_pool.thread_ids[i], NULL);
           break;
        }
    }

    //TODO 线程池的退出
    close(log_fd);
    close(pipe_fds[0]);
    close(server_fd);
    exit(0);
}

