#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int WriteClientOperInfoToLog(int fd, const char *content, size_t len) {
    int write_sz = write(fd, content, len);
    if(write_sz == -1) {
        printf("write log failure!\n");
        return -1;
    }
    write(fd, "\n", 1);
    return 0;
}

int StartMyLog(int *fd, const char *log_path) {
  *fd = open(log_path, O_WRONLY|O_APPEND);
  return *fd == -1 ? -1:0;
}
