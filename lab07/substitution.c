// 
// By Jayden Nguyen (z5362408)
// 13/07/2022
// encrypts text based on a given cipher for the standard alphabet
// and substitutes it.
// 

#include <stdio.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

int main(void) {
    char mapper[ALPHABET_LENGTH + 2];

    printf("Enter mapping:\n");
    fgets(mapper, ALPHABET_LENGTH + 2, stdin);

    printf("Enter text:\n");
    char letter;
    while (scanf("%c", &letter) == 1) {
        if (islower(letter)) {
            int letter_index = letter - 'a';
            printf("%c", mapper[letter_index]);
        } else if (isupper(letter)) {
            int letter_index = letter - 'A';
            printf("%c", toupper(mapper[letter_index]));
        } else {
            printf("%c", letter);
        }
    }
}