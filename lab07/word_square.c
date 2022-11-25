// word_square.c - prints out a 
// given string n times, where
// n is the length of the given string.
// By Jayden Nguyen - z5362408
// 13/07/2022

#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

int main(void) {
    char input_string[MAX_STRING_LENGTH];

    printf("Input word:\n");
    fgets(input_string, MAX_STRING_LENGTH, stdin);
    int letter_count = 0;

    int i = 0;
    while (input_string[i] != '\0') {
        letter_count++;
        i++;
    }

    printf("Word square is:\n");
    i = 0;
    while (i < letter_count - 1) {
        printf("%s", input_string);
        i++;
    }
    return 0;
}