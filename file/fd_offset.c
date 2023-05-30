#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    const int rfd = open("./fd_offset_test.txt", O_CREAT | O_RDONLY, mode);
    const int wfd = open("./fd_offset_test.txt", O_WRONLY, mode);
    int byte_counts = 0;
    char read_buf[256] = { 0, };
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
    if (lseek(rfd, 0, SEEK_SET) == -1)
        perror("failed to move rfd's offset ");
    if (lseek(wfd, 0, SEEK_SET) == -1)
        perror("failed to move wfd's offset ");
    if (write(wfd, "HELLO", 5) == -1)
        perror("failed to write() ");
    if (read(rfd, read_buf, sizeof(read_buf)) == -1)
        perror("errors occured in reading file ");
    printf("modified contents\n%s\n", read_buf);
    if (lseek(rfd, 6, SEEK_SET) == -1)
        perror("failed to move rfd's offset ");
    memset(read_buf, 0, sizeof(read_buf));
    if (read(rfd, read_buf, sizeof(read_buf)) == -1)
        perror("errors occured in reading file ");
    printf("modified contents\n%s\n", read_buf);
    if (close(rfd) == -1)
        perror("failed to close rfd! ");
    if (close(wfd) == -1)
        perror("failed to close wfd! ");
    return 0;
}