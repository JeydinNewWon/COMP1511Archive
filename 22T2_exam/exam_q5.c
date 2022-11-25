#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHARS 256

int main() {
    printf("Enter the base line:\n");
    char base_line[MAX_CHARS + 2];

    fgets(base_line, MAX_CHARS + 2, stdin);

    int test = strlen(base_line) - 1;

    if (base_line[test] == '\n') {
        base_line[test] = '\0';
    } 

    printf("Enter the test lines:\n");
    char test_line_1[MAX_CHARS + 2];
    char test_line_2[MAX_CHARS + 2];

    fgets(test_line_1, MAX_CHARS + 2, stdin);

    int t_1 = strlen(test_line_1) - 1;

    if (test_line_1[t_1] == '\n') {
        test_line_1[t_1] = '\0';
    } 

    fgets(test_line_2, MAX_CHARS + 2, stdin);

    int t_2 = strlen(test_line_2) - 1;

    if (test_line_2[t_2] == '\n') {
        test_line_2[t_2] = '\0';
    }

    int test_1_diff = 0;
    int test_1_i = 0;
    while (test_1_i < strlen(test_line_1)) {
        if (tolower(base_line[test_1_i]) != tolower(test_line_1[test_1_i])) {
            test_1_diff++;
        }
        test_1_i++;
    } 

    int test_2_diff = 0;
    int test_2_i = 0;
    while (test_2_i < strlen(test_line_2)) {
        if (tolower(base_line[test_2_i]) != tolower(test_line_2[test_2_i])) {
            test_2_diff++;
        }
        test_2_i++;
    }

    if (test_1_diff < test_2_diff) {
        printf("%d %s\n", test_1_diff, test_line_1);
    } else if (test_2_diff < test_1_diff) {
        printf("%d %s\n", test_2_diff, test_line_2);
    } else {
        printf("%d %s\n", test_1_diff, test_line_1);
    }
}
