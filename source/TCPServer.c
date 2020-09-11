
#include <func.h> 

int TCPServerBuild(int *server_fd, const char *ip_addr, short port) {
    *server_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(*server_fd, -1, "socket");
    int reuse = 1;
    setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    
    struct sockaddr_in server_sockaddr;
    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(port);
    server_sockaddr.sin_addr.s_addr = inet_addr(ip_addr);
    
    int ret = bind(*server_fd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr));
    ERROR_CHECK(ret, -1, "bind");
    
    ret =  listen(*server_fd, 10); 
    ERROR_CHECK(ret, -1, "listen");

    return 0;

}
