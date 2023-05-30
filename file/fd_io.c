#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    const int rfd = open("./fd_io_test.txt", O_CREAT | O_RDONLY, mode);
    const int wfd = open("./fd_io_test.txt", O_WRONLY, mode);
    char read_buf[256] = { 0, };
    const char *const write_string = "Hello\nFile Descriptor world!";
    const int write_string_len = strlen(write_string);
    int byte_counts = 0;
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
    if (write(wfd, write_string, write_string_len) != write_string_len)
        perror("failed to write all bytes in write buffer ");
    while ((byte_counts = read(rfd, read_buf, 3)) > 0) {
        printf("trying to read by 3 bytes, actually read %d bytes...\n"
                "%s\n", byte_counts, read_buf);
        memset(read_buf, 0, sizeof(read_buf));
    }
    if (byte_counts == -1)
        perror("errors occured in reading file ");
    if (close(rfd) == -1)
        perror("failed to close rfd! ");
    if (close(wfd) == -1)
        perror("failed to close wfd! ");
    return 0;
}