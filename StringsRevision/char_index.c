// Find the index of a character in a given string.
// Created by
//  ... (z0000000)
// Created on 2019-??-??

#include <stdio.h>

#define BUFFER_LENGTH 1024
#define NOT_IN_STRING -1

void read_line(int buffer_len, char *buffer);
int char_index(char c, char *string);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // Declare a buffer
    char buffer[BUFFER_LENGTH] = {0};

    // Read in a line...
    printf("Enter a line: ");
    read_line(BUFFER_LENGTH, buffer);

    // Get a character
    printf("Enter a character: ");
    char ch;
    if (scanf("%c", &ch) != 1) {
        printf("Character '%c' is not in the string.\n", ch);
        return 0;
    }

    // Find and print character index or "not in string"
    int index = char_index(ch, buffer);
    if (index == NOT_IN_STRING) {
        printf("Character '%c' is not in the string.\n", ch);
    } else {
        printf("Index of character '%c': %d\n", ch, index);
    }

    return 0;
}


// Read a line of input into `buffer`, excluding the newline;
// ensures that `buffer` is a null-terminated string.
void read_line(int buffer_len, char *buffer) {
    int i = 0;
    char input_letter;
    scanf("%c", &input_letter);
    while (i < buffer_len - 1 && input_letter != '\n') {
        buffer[i] = input_letter;
        i++;
        scanf("%c", &input_letter);
    }

    buffer[i] = '\0';
}

// Return the index of the first occurrence of
// character `c` in the string, or `NOT_IN_STRING`
int char_index(char c, char *string) {
    int i = 0;
    while (string[i] != '\0') {
        if (string[i] == c) {
            return i;
        } 
        i++;
    }
    return NOT_IN_STRING;
}
