#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    int _errno = 0; /* do not use "errno" as variable name */
    for (_errno = 0; _errno < 10; ++_errno)
        printf("errno %d : %s\n", _errno, strerror(_errno));
    return 0;
}