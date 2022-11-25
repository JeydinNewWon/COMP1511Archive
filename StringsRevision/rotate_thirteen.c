// Perform the ROT13 algorithm on a string
// Completed by
//  ... (z0000000)
// Completed on 2019-??-??

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 256

// Add your own #defines here

void rotate_thirteen(char *string);
char rotate_one(char c);
void rotate_thirteen(char *string);
int strings_equal(char *string1, char *string2);
int string_size(char *string);

// Add your own function prototypes here

int main(int argc, char *argv[]) {
    // Example tests
    char test_a[MAX_LENGTH] = "Hello, world!";
    rotate_thirteen(test_a);
    assert(strings_equal("Uryyb, jbeyq!", test_a));

    char test_b[MAX_LENGTH] = "abcdefghijklmnopqrstuvwxyz";
    rotate_thirteen(test_b);
    assert(strings_equal("nopqrstuvwxyzabcdefghijklm", test_b));

    char test_c[MAX_LENGTH] = "The quick brown fox jumped over the lazy dog.";
    rotate_thirteen(test_c);
    assert(strings_equal("Gur dhvpx oebja sbk whzcrq bire gur ynml qbt.", test_c));

    // Add your own tests here

    printf("All tests passed. You are awesome!\n");

    return 0;
}

void rotate_thirteen(char *string) {
    int i = 0;
    while (string[i] != '\0') {
        if (isupper(string[i])) {
            char temp = tolower(string[i]);
            int rotated = temp + 13;
            if (rotated > 'z') {
                rotated -= 26;
            }

            string[i] = toupper(rotated);  

        } else if (islower(string[i])) {
            char temp = string[i];
            int rotated = temp + 13;
            if (rotated > 'z') {
                rotated -= 26;
            }

            string[i] = rotated;
        } 
        i++;
    }
}

char rotate_one(char c) {
    // Use your code from the rotate_one exercise up here
    return 0;
}

int string_size(char *string) {
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }

    return i;
}

int strings_equal(char *string1, char *string2) {
    int i = 0;
    int is_equal = 1;
    while (string1[i] != '\0' && string2[i] != '\0') {
        if (string1[i] != string2[i]) {
            is_equal = 0;
        }
        i++;
    }

    if (string_size(string1) != string_size(string2)) {
        is_equal = 0;
    }

    return is_equal;
    return 0;
}
