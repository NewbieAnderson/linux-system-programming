#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    int fd = 12345;
    int err = 0;
    char buf[256] = { 0, };
    if (close(fd) == -1) {
        err = errno;
        if (strerror_r(err, buf, 256) == -1)
            perror("failed to call strerror_r ");
        printf("failed to call close() : %s\n", buf);
    }
    return 0;
}