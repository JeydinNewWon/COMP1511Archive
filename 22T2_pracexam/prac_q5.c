#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHARS 256

int is_checked(char checked[MAX_CHARS], char letter_to_check, int *checked_size) {
    int found = 0;
    int i = 0;

    while (i < *checked_size && !found) {
        if (tolower(letter_to_check) == tolower(checked[i])) {
            found = 1;
        }
        i++;
    }

    return found; 
}

int main(void) {
    char string_1[MAX_CHARS + 2];
    char string_2[MAX_CHARS + 2];

    fgets(string_1, MAX_CHARS + 2, stdin);
    fgets(string_2, MAX_CHARS + 2, stdin);

    int str_1_len = strlen(string_1);

    if (string_1[str_1_len - 1] == '\n') {
        string_1[str_1_len - 1] = '\0';
    }

    int str_2_len = strlen(string_2);

    if (string_2[str_2_len - 1] == '\n') {
        string_2[str_2_len - 1] = '\0';
    }

    char checked[MAX_CHARS];
    int checked_size = 0;

    int overlap = 0;
    int i = 0;
    while (i < str_1_len - 1) {
        int j = 0;
        while (j < str_2_len - 1) {
            char str_1_char = tolower(string_1[i]);
            char str_2_char = tolower(string_2[j]);
            int is_alpha = islower(str_1_char) && islower(str_2_char);

            if (str_1_char == str_2_char && 
                !is_checked(checked, str_1_char, &checked_size) && is_alpha) {
                overlap++;
                checked[checked_size] = str_1_char;
                checked_size++;
            }
            j++;
        }
        i++;
    }

    printf("%d\n", overlap);

    return 0;
}
