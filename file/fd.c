#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    const int flag = O_CREAT | O_RDONLY;
    const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    const int rfd = open("./fd_test.txt", flag, mode);
    const int wfd = open("./fd_test.txt", flag, mode);
    if (rfd == -1) {
        perror("failed to open rfd ");
        exit(1);
    }
    if (wfd == -1) {
        perror("failed to open wfd ");
        exit(1);
    }
    printf("rfd : %d\n"
            "wfd : %d\n", rfd, wfd);
    if (close(rfd) == -1)
        perror("failed to close rfd! ");
    if (close(wfd) == -1)
        perror("failed to close wfd! ");
    return 0;
}