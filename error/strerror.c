#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    int err = 0;
    for (err = 0; err < 10; ++err)
        printf("error code %d : %s\n", err, strerror(err));
    return 0;
}