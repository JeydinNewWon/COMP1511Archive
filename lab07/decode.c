// decode.c - written to decode certain 
// encoded phrases with a given mapping cipher.
// By Jayden Nguyen (z5362408)
// 13/07/2022

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
            int letter_index = 0;
            while (mapper[letter_index] != letter) {
                letter_index++;
            }

            printf("%c", 'a' + letter_index);

        } else if (isupper(letter)) {
            int letter_index = 0;
            while (mapper[letter_index] != tolower(letter)) {
                letter_index++;
            }

            printf("%c", 'A' + letter_index);
        } else {
            printf("%c", letter);
        }
    }


}