#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fd = 12345;
    if (close(fd) == -1)
        perror("failed to call close() ");
    return 0;
}