// Program which prints a letter depending on the user's request.
// by Jayden Nguyen z5362408

#include <stdio.h>

#define NUM_ALPHABET 26

int main(void) {

    char is_uppercase;
    printf("Uppercase: ");

    // TODO: scan is_uppercase
    scanf("%c", &is_uppercase);

    int index;
    printf("Index: ");

    scanf("%i", &index);

    // TODO: finish the program
    int letter;
    if (is_uppercase == 'y') {
        letter = index + 65;
        printf("The letter is %c\n", letter);
    } else {
        letter = index + 97;
        printf("The letter is %c\n", letter);
    }

    return 0;
}