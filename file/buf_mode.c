#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 64

int main(void)
{
    FILE *const fp1 = fopen("./buf_mode_test.txt", "a");
    FILE *const fp2 = fopen("./buf_mode_test.txt", "a");
    FILE *const fp3 = fopen("./buf_mode_test.txt", "a");
    char buf1[BUFFER_SIZE] = { 0, };
    char buf2[BUFFER_SIZE] = { 0, };
    char buf3[BUFFER_SIZE] = { 0, };
    double start_time = 0;
    if (fp1 == NULL) {
        perror("failed to open file ");
        exit(1);
    }
    if (fp2 == NULL) {
        perror("failed to open file ");
        exit(1);
    }
    if (fp3 == NULL) {
        perror("failed to open file ");
        exit(1);
    }
    setvbuf(fp1, buf1, _IONBF, BUFFER_SIZE);
    setvbuf(fp2, buf2, _IOLBF, BUFFER_SIZE);
    setvbuf(fp3, buf3, _IOFBF, BUFFER_SIZE);
    start_time = (double)clock();
    fputs("un-buffered___\n", fp1);
    printf("execution time (no buffered) : %.2lfms\n", ((double)clock() - start_time));
    start_time = (double)clock();
    fputs("line-buffered_\n", fp2);
    printf("execution time (line buffered) : %.2lfms\n", ((double)clock() - start_time));
    start_time = (double)clock();
    fputs("block-buffered\n", fp3);
    printf("execution time (fully buffered) : %.2lfms\n", ((double)clock() - start_time));
    if (fclose(fp1) == -1)
        perror("failed to close fp1 ");
    if (fclose(fp2) == -1)
        perror("failed to close fp2 ");
    if (fclose(fp3) == -1)
        perror("failed to close fp3 ");
    return 0;
}