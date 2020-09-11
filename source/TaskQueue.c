#include "../include/TaskQueue.h"

int TaskQueueInit(TaskQueue_t *task_queue) {
    task_queue->head = task_queue->tail = NULL;
    pthread_mutex_init(&task_queue->mutex, NULL);
    pthread_cond_init(&task_queue->cond_variable, NULL);
    task_queue->exit_flag = 0;
    return 0;
}
int TaskQueuePush(TaskQueue_t *task_queue, QueNode_t *push_node) {
    if(task_queue->head == NULL) {
        task_queue->head = task_queue->tail = push_node;
    } else {
        task_queue->tail->next = push_node;
        task_queue->tail = push_node;
    }
    
    ++task_queue->size;
    return 0;
}

int TaskQueuePop(TaskQueue_t *task_queue, QueNode_t **pop_node) {
    if(task_queue->size == 0) 
        return -1;
    *pop_node = task_queue->head;
    task_queue->head = task_queue->head->next;
    --task_queue->size;
    return 0;
}
int TaskQueueEmpty(const TaskQueue_t *task_queue) {
    return task_queue->size == 0 ? 1 : 0;
}

