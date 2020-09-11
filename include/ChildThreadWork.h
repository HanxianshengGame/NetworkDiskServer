#ifndef CHILDTHREADWORK_H_
#define CHILDTHREADWORK_H_

#include "../include/MessageProtocol.h"
#include "../include/DataBaseWork.h"
void *ChildThreadFunc(void *arg);
int ClientLoginHandler(int socket_sfd, MYSQL *mysql_conn, char *client_Path);
int ClientCmdHandle(int socket_sfd, int log_fd, MYSQL *conn, char *client_path, char *client_curpath, Msg_t *pMsg);

int handle_cmd_putsfile(int socket_sfd, const char *ware_house, const char *client_curpath, const char *file_path,Msg_t *pMsg);
int handler_cmd_putsdir(int socket_sfd, const char *ware_house, const char *client_curpath, const char *dir_name, Msg_t *pMsg);
int handler_cmd_ls(int socket_sfd, const char *ware_house, const char *client_curpath);
int handler_cmd_cd(int socket_sfd, const char *ware_house, char *des_path, char *client_path, char *client_curpath);

int handler_cmd_getsfile(int socket_sfd,const char * ware_house, const char *client_curpath, const char *file_path);
int handler_cmd_continue_getsfile(int socket_sfd, const char *ware_house, const char *client_curpath, const char *file_path);
int handler_cmd_getsdir(int socket_sfd, const char *ware_house, const char *client_curpath, const char *dir_path);
int handler_cmd_getsdir_core(int socket_sfd,const char *ware_house, const char *client_curpath, const char *dir_name, Msg_t *pMsg);
int handler_cmd_pwd(int clientFd,const char *ware_house, const char* client_curpath);
int handler_cmd_mkdir(int clientFd,const char *ware_house,const char* client_curpath,const char* dirname);
int handler_cmd_remove(int clientFd,const char *ware_house,const char* client_curpath,const char* filename);

#endif
