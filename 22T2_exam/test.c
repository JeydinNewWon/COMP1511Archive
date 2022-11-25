// Casear.c 
// By Jayden Nguyen (z5362408)
// 13/07/2022
// A program that takes in a string and
// encrypts it by shifting each letter
// by a given integer.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
    int shift;
    scanf("%d ", &shift);

    char letter;
    while (scanf("%c", &letter) == 1) {
        shift = shift % 26;
        int new_letter = letter + shift;
        int new_shift = 0; 

        if (islower(letter)) {
            if (new_letter > 'z') {
                new_shift = new_letter - 'z';
                new_letter = new_shift + ('a' - 1);
            } else if (new_letter < 'a') {
                new_shift = 'a' - new_letter;
                new_letter = ('z' + 1) - new_shift;
            }

            printf("%c", new_letter);

        } else if (isupper(letter)) {
            if (new_letter > 'Z') {
                new_shift = new_letter - 'Z';
                new_letter = new_shift + ('A'-1);
            } else if (new_letter < 'A') {
                new_shift = 'A' - new_letter;
                new_letter = ('Z' + 1) - new_shift; 
            }
            printf("%c", new_letter);
        } else {
            printf("%c", letter);
        }
    }

    return 0;
}