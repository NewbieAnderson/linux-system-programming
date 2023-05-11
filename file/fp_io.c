#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *rfp = fopen("./fp_test.txt", "r");
    FILE *wfp = fopen("./fp_test.txt", "a");
    char buf[256] = { 0, };
    char *addr = NULL;
    int ch = '\0';
    int i;
    if (rfp == NULL) {
        perror("failed to open file as read mode ");
        exit(1);
    }
    if (wfp == NULL) {
        perror("failed to open file as write mode ");
        exit(1);
    }
    printf("reading...\n");
    while ((ch = fgetc(rfp)) != EOF)
        putc(ch, stdout);
    putchar('\n');
    puts("Hello puts()!");
    if (fputs("Hello fputs()!\n", wfp) < 0)
        perror("failed to write in wfp by using fputs() ");
    addr = fgets(buf, 256, rfp);
    if (addr < 0)
        perror("failed to read by using fgets() ");
    if (fclose(rfp) == -1)
        perror("failed to close rfp ");
    if (fclose(wfp) == -1)
        perror("failed to close wfp ");
    return 0;
}