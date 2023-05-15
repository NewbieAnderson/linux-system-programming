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
    clock_t start, end;
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
    start = clock();
    fputs("un-buffered___\n", fp1);
    end = clock();
    printf("execution time (no buffered) : %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    start = clock();
    fputs("line-buffered_\n", fp2);
    end = clock();
    printf("execution time (line buffered) : %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    start = clock();
    fputs("block-buffered\n", fp3);
    end = clock();
    printf("execution time (fully buffered) : %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    if (fclose(fp1) == -1)
        perror("failed to close fp1 ");
    if (fclose(fp2) == -1)
        perror("failed to close fp2 ");
    if (fclose(fp3) == -1)
        perror("failed to close fp3 ");
    return 0;
}