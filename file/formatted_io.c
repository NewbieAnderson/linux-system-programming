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
    FILE *const rfp = fopen("./formatted_io_test.csv", "r");
    FILE *const wfp = fopen("./formatted_io_test.csv", "a");
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
    printf("input id name age (Ctrl+D is EOF) : ");
    /* EOF of scanf in linux is 'Ctrl+D' */
    while (scanf("%s %s %d", user.id, user.name, &user.age) != EOF) {
        printf("input id name age (Ctrl+D is EOF) : ");
        fprintf(wfp, "%s, %s, %d\n", user.id, user.name, user.age);
        fflush(stdin);
        fflush(wfp);
    }
    printf("\n");
    while (fscanf(rfp, "%[^,], %[^,], %d\n", user.id, user.name, &user.age) == 3)
        printf("%s, %s, %d\n", user.id, user.name, user.age);
    if (fclose(rfp) == -1)
        perror("failed to close rfp ");
    if (fclose(wfp) == -1)
        perror("failed to close wfp ");
    return 0;
}