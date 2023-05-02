#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int fd = open("./io_test_result.txt", O_CREAT, mode);
    if (fd == -1) {
        printf("failed to open!\n");
        exit(1);
    }
    if (close(fd) == -1)
        printf("failed to close!\n");
    return 0;
}