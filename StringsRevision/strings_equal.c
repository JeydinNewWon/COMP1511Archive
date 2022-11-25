// String Equality
// Created by
//  ... (z0000000)
// Created on 2019-??-??

#include <stdio.h>
#include <assert.h>
// You cannot include string.h in this file.


int strings_equal(char *string1, char *string2);

int main(int argc, char *argv[]) {

    // Some simple assert-based tests.
    // You probably want to write some more.
    assert(strings_equal("", "") == 1);
    assert(strings_equal(" ", "") == 0);
    assert(strings_equal("", " ") == 0);
    assert(strings_equal(" ", " ") == 1);
    assert(strings_equal("\n", "\n") == 1);
    assert(strings_equal("This is 17 bytes.", "") == 0);
    assert(strings_equal("", "This is 17 bytes.") == 0);
    assert(strings_equal("This is 17 bytes.", "This is 17 bytes.") == 1);
    assert(strings_equal("Here are 18 bytes!", "This is 17 bytes.") == 0);

    printf("All tests passed.  You are awesome!\n");

    return 0;
}

int string_size(char *string) {
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }

    return i;
}

// Takes two strings, and if they are the same,
// returns 1, or 0 otherwise.
int strings_equal(char *string1, char *string2) {
    // Your code goes here!
    // Don't forget to return your result.
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
}
