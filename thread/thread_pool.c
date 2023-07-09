#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define THREAD_COUNT 5
#define THREAD_STATE_IS_NOT_WOKRING 0
#define THREAD_STATE_IS_WORKING 1

struct thread {
    pthread_t tid;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    unsigned char thread_num;
    unsigned char state;
};

void *task_function(void *arg)
{
    struct thread *task = (struct thread *)arg;
    pthread_mutex_t *mutex_ptr = &(task->mutex);
    pthread_cond_t *cond_ptr = &(task->cond);
    srand(time(NULL));
    while (task->state == THREAD_STATE_IS_NOT_WOKRING) {
        pthread_mutex_lock(mutex_ptr);
        pthread_cond_wait(cond_ptr, mutex_ptr);
        printf("hello i am thread %d!\n", task->thread_num);
        usleep(1);
        task->state = THREAD_STATE_IS_NOT_WOKRING;
        pthread_mutex_unlock(mutex_ptr);
    }
    return NULL;
}

int main(void)
{
    struct thread *task_threads = (struct thread *)malloc(sizeof(struct thread) * THREAD_COUNT);
    int i;
    for (i = 0; i < THREAD_COUNT; ++i) {
        task_threads[i].state = THREAD_STATE_IS_NOT_WOKRING;
        task_threads[i].thread_num = i + 1;
        pthread_mutex_init(&(task_threads[i].mutex), NULL);
        pthread_cond_init(&(task_threads[i].cond), NULL);
        pthread_create(&(task_threads[i].tid), NULL, task_function, &task_threads[i]);
    }
    while (1) {
        for (i = 0; i < THREAD_COUNT; ++i) {
            if (task_threads[i].state == THREAD_STATE_IS_WORKING)
                continue;
            pthread_cond_signal(&(task_threads[i].cond));
        }
    }
    for (i = 0; i < THREAD_COUNT; ++i) {
        pthread_mutex_destroy(&(task_threads[i].mutex));
        pthread_cond_destroy(&(task_threads[i].cond));
        memset(&task_threads[i], 0, sizeof(struct thread));
    }
    free(task_threads);
    task_threads = NULL;
    return 0;
}