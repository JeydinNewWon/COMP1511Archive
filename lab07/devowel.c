// Devowel.c, which takes in a string 
// and then prints it out minus any lowercase vowels.
// By Jayden Nguyen - z5362408
// Written on 13/07/2022

#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


int is_lowercase_vowel(char letter) {
    if (letter == 'a') {
        return TRUE;
    } else if (letter == 'e') {
        return TRUE;
    } else if (letter == 'i') {
        return TRUE;
    } else if (letter == 'o') {
        return TRUE;
    } else if (letter == 'u') {
        return TRUE;
    } else {
        return FALSE;
    }

}

int main(void) {
    char letter;
    while (scanf("%c", &letter) == 1) {
        if (!is_lowercase_vowel(letter)) {
            printf("%c", letter);
        }
    }

    return 0;
}