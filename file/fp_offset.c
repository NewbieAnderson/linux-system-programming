#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *const rfp = fopen("./formatted_io_test.csv", "r");
    FILE *const wfp = fopen("./formatted_io_test.csv", "a");
    if (rfp == NULL) {
        perror("failed to open file as read mode ");
        exit(1);
    }
    if (wfp == NULL) {
        perror("failed to open file as write mode ");
        exit(1);
    }
    if (fclose(rfp) == -1)
        perror("failed to close rfp ");
    if (fclose(wfp) == -1)
        perror("failed to close wfp ");
    return 0;
}