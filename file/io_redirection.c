#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int wfd = open("./fd_test.txt", O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int fd_num_1_stdin;
    if (wfd == -1) {
        perror("failed to open wfd ");
        exit(1);
    }
    if (close(1) == -1) {
        perror("failed to close stdin\n");
        exit(1);
    }
    fd_num_1_stdin = dup(wfd);
    if (fd_num_1_stdin == -1)
        perror("failed to duplicate file descriptor ");
    if (lseek(fd_num_1_stdin, 0, SEEK_END) == -1)
        perror("failed to move new_fd1's offset ");
    printf("\nthis text will be written in file!");
    return 0;
}