#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "TaskQueue.h"

typedef struct ThreadPool {
    TaskQueue_t task_queue;
    pthread_t   *thread_ids; 
}ThreadPool_t;

int ThreadPoolInit(ThreadPool_t *thread_pool, int thread_num);
int ThreadPoolStart(ThreadPool_t *thread_pool, int thread_num);


#endif
