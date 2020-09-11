#ifndef TASKQUEUE_H_
#define TASKQUEUE_H_
#include <func.h>
#include <mysql/mysql.h>
typedef struct QueNode {
    int       client_sfd;
    int       log_fd;
    MYSQL     *mysql_conn;
    struct QueNode *next;
}QueNode_t;

typedef struct TaskQueue {
    QueNode_t *head;
    QueNode_t *tail;
    size_t     size;
    pthread_mutex_t mutex;
    pthread_cond_t  cond_variable;
    int        exit_flag;
}TaskQueue_t;

int TaskQueueInit(TaskQueue_t *task_queue);
int TaskQueuePush(TaskQueue_t *task_queue, QueNode_t *push_node);
int TaskQueuePop(TaskQueue_t *task_queue, QueNode_t **pop_node);
int TaskQueueEmpty(const TaskQueue_t *task_queue);
#endif
