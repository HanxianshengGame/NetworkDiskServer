#ifndef MYLOG_H_
#define MYLOG_H_
#include <string.h>
int StartMyLog(int *fd, const char *log_path);
int WriteClientOperInfoToLog(int fd, const char *content, size_t len);


#endif
