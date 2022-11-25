#include <stdio.h>

#define MAX_CHARS 256

int main(void) {
    char input_string[MAX_CHARS];

    fgets(input_string, MAX_CHARS, stdin);

    int index;
    scanf(" %d", &index);

    printf("The character in position %d is '%c'\n", index, input_string[index]);

    return 0;
}