// String to Lower
// string_to_lower.c
//
// This program was written by Jayden Nguyen z5362408
// on 13/07/2022
//
// This exercise takes in a string and prints it
// out in all lowercase.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1024

void string_to_lower(char *string);

int main(void) {

    char str[MAX_LEN] = "Hi, mY nAmE iS sPonGEbOb sQuArePanTS.";
    string_to_lower(str);
    printf("%s\n", str);

    return 0;
}

// Convert the characters in `buffer` to lower case
void string_to_lower(char *string) {
    int i = 0;
    while (string[i] != '\0') {
        if (isupper(string[i])) {
            string[i] = tolower(string[i]);
        }
        i++;
    }
    
}
