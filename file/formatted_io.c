#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 256

struct user_info {
    char id[MAX_STRING_LENGTH];
    char name[MAX_STRING_LENGTH];
    int age;
};

int main(void)
{
    FILE *const rfp = fopen("./formatted_io_test.txt", "r");
    FILE *const wfp = fopen("./formatted_io_test.txt", "a");
    struct user_info user = { 0, };
    int i = 0;
    if (rfp == NULL) {
        perror("failed to open file as read mode ");
        exit(1);
    }
    if (wfp == NULL) {
        perror("failed to open file as write mode ");
        exit(1);
    }
    printf("%d\n", getchar());
    while (getchar() != '!') {
        scanf("input here : %s %s %d", user.id, user.name, &user.age);
        fprintf("%s %s %d", user.id, user.name, &user.age);
    }
    while (fscanf(rfp, "%[^,], %[^,], %d\n", user.id, user.name, &user.age) == 3)
        printf("%s, %s, %d\n", user.id, user.name, user.age);
    if (fclose(rfp) == -1)
        perror("failed to close rfp ");
    if (fclose(wfp) == -1)
        perror("failed to close wfp ");
    return 0;
}