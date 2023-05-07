#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("./fp_test.txt", "w");
    if (fp == NULL) {
        perror("failed to open file ");
        exit(1);
    }
    if (fclose(fp) == -1)
        perror("failed to close file ");
    return 0;
}