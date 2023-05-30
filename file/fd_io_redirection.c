#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    const int wfd = open("./fd_io_redirection_test.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int fd_num_1_stdin = -1;
    if (wfd == -1) {
        perror("failed to open wfd ");
        exit(1);
    }
    if (close(1) == -1) { /* stdin : 1 */
        perror("failed to close stdin\n");
        exit(1);
    }
    fd_num_1_stdin = dup(wfd);
    if (fd_num_1_stdin == -1)
        perror("failed to duplicate file descriptor ");
    if (lseek(fd_num_1_stdin, 0, SEEK_END) == -1)
        perror("failed to move new_fd1's offset ");
    printf("this text will be written in file!\n");
    return 0;
}