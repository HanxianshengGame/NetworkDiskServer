#include "../include/MessageProtocol.h"
#include <sys/types.h>
#include <sys/socket.h>
int ReceiveFixedSized(int client_sfd, void *buffer, int recv_sz) {
    char *p = (char *)buffer;
    int total = 0,ret;
    while(total < recv_sz) {
        ret = recv(client_sfd, p+total, recv_sz - total, 0);
        total+=ret;
    }
    return 0;
}
