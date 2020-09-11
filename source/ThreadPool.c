#include "../include/ThreadPool.h"
#include "../include/ChildThreadWork.h"
int ThreadPoolInit(ThreadPool_t *thread_pool, int thread_num) {
    memset(thread_pool, 0, sizeof(ThreadPool_t));
    TaskQueueInit(&thread_pool->task_queue);
    
    thread_pool->thread_ids = (pthread_t*)calloc(thread_num, sizeof(pthread_t));
    return 0;
}
int ThreadPoolStart(ThreadPool_t *thread_pool, int thread_num) {
    for(int i = 0; i != thread_num; ++i) {
        pthread_create(&thread_pool->thread_ids[i], NULL, ChildThreadFunc, &thread_pool->task_queue);
    }

   
    return 0;
}
