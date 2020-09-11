#ifndef  MESSAGEPROTOCOL_H_
#define  MESSAGEPROTOCOL_H_
enum CMD_TYPE{
    CD,
    LS,
    PUTSFILE,
    PUTSDIR,
    GETSFILE,
    GETSDIR,
    PWD,
    MKDIR,
    REMOVE,
    CMDERROR,
    CMDEOF,
    CMDQUIT,
    CMDLOGIN,
};
typedef struct Message {
    unsigned int                len;
    enum CMD_TYPE               cmd;
    char                         data[128];
}Msg_t;

int ReceiveFixedSized(int client_sfd, void *buffer, int recv_sz);
#endif
