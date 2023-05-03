#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    const int rfd = open("./fd_test.txt", O_CREAT | O_RDONLY, mode);
    const int wfd = open("./fd_test.txt", O_CREAT | O_WRONLY, mode);
    int new_fd1;
    int byte_counts = 0;
    char read_buf[256] = { 0, };
    const char *write_string = "Hello\nFile Descriptor world!";
    const int write_string_len = strlen(write_string);
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
    if (close(1) == -1)
        perror("failed to close stdin\n");
    new_fd1 = dup(wfd);
    if (new_fd1 == -1)
        perror("failed to duplicate file descriptor ");
    if (lseek(new_fd1, 0, SEEK_END) == -1)
        perror("failed to move new_fd1's offset ");
    printf("\nthis text will be written in file!");
    if (close(rfd) == -1)
        perror("failed to close rfd! ");
    if (close(wfd) == -1)
        perror("failed to close wfd! ");
    return 0;
}