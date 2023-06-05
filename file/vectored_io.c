#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(void)
{
    const char *const write_buf1 = "Hello Str1!\n";
    const char *const write_buf2 = "hello, this is Str2!\n";
    const char *const write_buf3 = "i am Str3!\n";
    const int write_buf1_len = strlen(write_buf1);
    const int write_buf2_len = strlen(write_buf2);
    const int write_buf3_len = strlen(write_buf3);
    char *const read_buf1 = malloc(sizeof(char) * write_buf2_len);
    char *const read_buf2 = malloc(sizeof(char) * write_buf1_len);
    char *const read_buf3 = malloc(sizeof(char) * write_buf3_len);
    struct iovec write_iov[3] = {
        {
            .iov_base = (void*)write_buf2,
            .iov_len = write_buf2_len
        },
        {
            .iov_base = (void*)write_buf1,
            .iov_len = write_buf1_len
        },
        {
            .iov_base = (void*)write_buf3,
            .iov_len = write_buf3_len
        },
    };
    struct iovec read_iov[3] = {
        {
            .iov_base = (void*)read_buf1,
            .iov_len = write_buf2_len
        },
        {
            .iov_base = (void*)read_buf2,
            .iov_len = write_buf1_len
        },
        {
            .iov_base = (void*)read_buf3,
            .iov_len = write_buf3_len
        },
    };
    ssize_t bytes = 0;
    int fd = open("./vectored_io_test.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (read_buf1 == NULL || read_buf2 == NULL || read_buf3 == NULL)
        exit(1);
    if (fd == -1) {
        perror("failed to open vectored_io_test.txt ");
        exit(1);
    }
    bytes = writev(fd, write_iov, 3);
    printf("%ld byte wrote\n", bytes);
    if (bytes == -1) {
        perror("failed to write buffers ");
        exit(1);
    }
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("failed to move fd\'s offset ");
        exit(1);
    }
    bytes = readv(fd, read_iov, 3);
    printf("%ld byte read\n", bytes);
    if (bytes == -1) {
        perror("failed to read buffers ");
        exit(1);
    }
    printf("read_iov[0].iov_base : %s\n"
            "read_iov[1].iov_base : %s\n"
            "read_iov[2].iov_base : %s\n"
            "read_buf1 : %s\n"
            "read_buf2 : %s\n"
            "read_buf3 : %s\n", (char*)read_iov[0].iov_base,
                                (char*)read_iov[1].iov_base,
                                (char*)read_iov[2].iov_base,
                                read_buf1, read_buf2, read_buf3);
    if (close(fd) == -1)
        perror("failed to close fd ");
    return 0;
}