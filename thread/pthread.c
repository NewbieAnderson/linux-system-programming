#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *routine(void *arg)
{
    printf("routine() - new thread\n");
    return (void*)23;
}

int main(void)
{
    pthread_t thread;
    void *ret = 0;
    printf("main() - main thread\n");
    if (pthread_create(&thread, NULL, routine, NULL) != 0) {
        perror("failed to create new thread ");
        return 1;
    }
    if (pthread_join(thread, &ret) != 0) {
        perror("failed to join thread ");
        return 1;
    }
    printf("ret : %lld\n", (long long int)ret);
    return 0;
}