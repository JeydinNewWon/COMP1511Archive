// exam_q3.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// One line summary of what this exercise does.
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 10000

int main(void) {
    int my_numbers[MAX_NUMBERS];

    int input_num;
    int arr_counter = 0;
    while (scanf(" %d", &input_num) == 1) {
        my_numbers[arr_counter] = input_num;
        arr_counter++;
    }

    int min_distance = -1;

    int i = 0;
    while (i < arr_counter) {
        int j = i - 1;
        while (j >= 0) {
            if (my_numbers[j] == my_numbers[i]) {
                if (min_distance == -1) {
                    min_distance = i - j;
                } else if (i - j < min_distance) {
                    min_distance = i - j;
                }
            }
            j--;
        }
        i++;
    }


    
    printf("The minimum distance was: %d\n", min_distance);

    return 0;
}
