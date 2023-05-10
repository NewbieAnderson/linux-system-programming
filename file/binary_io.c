#include <stdio.h>
#include <stdlib.h>

typedef char byte_t;

int main(void)
{
    FILE *rbfp = fopen("./fp_bin_test.txt", "rb+");
    FILE *wbfp = fopen("./fp_bin_test.txt", "ab+");
    byte_t write_buf[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    byte_t read_buf[6] = { 0, };
    const int write_data = 0x10090807;
    int read_data = 0;
    size_t write_count;
    int i;
    if (rbfp == NULL) {
        perror("failed to open file ");
        exit(1);
    }
    if (wbfp == NULL) {
        perror("failed to open file ");
        exit(1);
    }
    write_count = fwrite(write_buf, sizeof(byte_t) * 2, 3, wbfp);
    printf("write %ld items in buffer\n", write_count);
    if (write_count == EOF)
        perror("failed to write bytes ");
    write_count = fwrite(&write_data, sizeof(int), 1, wbfp);
    printf("write %ld items in variable (4 bytes)\n", write_count);
    if (write_count == EOF)
        perror("failed to write bytes ");
    write_count = fread(read_buf, sizeof(byte_t) * 2, 3, rbfp);
    printf("read %ld items in buffer\n", write_count);
    if (write_count == EOF)
        perror("failed to read bytes ");
    for (i = 0; i < 6; ++i)
        printf("0x%02X ", read_buf[i]);
    printf("\n");
    write_count = fread(&read_data, sizeof(int), 1, rbfp);
    if (write_count == EOF)
        perror("failed to read bytes ");
    printf("0x%02X ", read_data & 0xFF);
    printf("0x%02X ", (read_data >> 8) & 0xFF);
    printf("0x%02X ", (read_data >> 16) & 0xFF);
    printf("0x%02X\n", (read_data >> 24) & 0xFF);
    if (fclose(rbfp) == -1)
        perror("failed to close file ");
    if (fclose(wbfp) == -1)
        perror("failed to close file ");
    return 0;
}