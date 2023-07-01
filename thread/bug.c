#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_COUNT 10

int g_account = 0;

void *try_add(void *arg)
{
    int i;
    int flag = 0;
    printf("[%lld-1] routine()\n", (long long int)arg);
    printf("[%lld-2] start...\n", (long long int)arg);
    for (i = 0; i < 100000000; ++i) {
        if (!flag) {
            printf("[%lld-3] running!\n", (long long int)arg);
            ++flag;
        }
        ++g_account;
    }
    printf("[%lld-4] end...\n", (long long int)arg);
    return NULL;
}

int main(void)
{
    pthread_t tids[THREAD_COUNT] = { 0, };
    int i;
    for (i = 0; i < THREAD_COUNT; ++i) {
        if (pthread_create(&tids[i], NULL, try_add, (void *)((long long int)i + 1)) != 0) {
            perror("failed to create new thread ");
            return 1;
        }
    }
    for (i = 0; i < THREAD_COUNT; ++i) {
       if (pthread_join(tids[i], NULL) != 0) {
            perror("failed to join thread ");
            return 1;
        }
    }
    printf("g_account : %d\n", g_account);
    return 0;
}