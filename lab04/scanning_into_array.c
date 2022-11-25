// 
// Written 22/06/2022
// By Jayden Nguyen z5362408
//
// Takes in a list of numbers and the number of numbers and then 
// returns the minimum and maximum numbers of that list.
//

#include <stdio.h>

#define MAX_SIZE 100

// Given an integer array, iterate over the array and print the minimum and
// maximum values in the array.
void print_array_minmax(int length, int numbers[MAX_SIZE]);

int main(void) {
	// TODO: Create an integer array of size MAX_SIZE
	// HINT: Do not use the user input as the length of the array!

    int array_size;

    printf("How many numbers: ");
    // TODO: Fill in code that takes the quantity of numbers from the user
    scanf("%i", &array_size);

    int number_list[array_size];

    printf("Please enter numbers: ");
    // TODO: Fill in code that scans in integers from the user
    int i = 0;
    while (i < array_size) {
        scanf("%i", &number_list[i]);
        i++;
    }
    
    print_array_minmax(array_size, number_list);
    // TODO: Change this statement to match your variables and array.
    //      Refer to the documentation below for correct usage!

    return 0;
}

//////////////////////// DO NOT CHANGE THE CODE BELOW! ////////////////////////

// Given an integer array, iterate over the array and print the minimum and
// maximum values in the array.
//
// Takes in:
// - `length` -- The length of the array.
// - `numbers[MAX_SIZE]` -- The integer array to iterate over.
//
// Returns: nothing.
void print_array_minmax(int length, int numbers[MAX_SIZE]) {
    int index = 0;
    if (length > 0) {
        int minimum = numbers[index];
        int maximum = numbers[index];

        while (index < length) {
            if (numbers[index] < minimum) {
                minimum = numbers[index];
            } else if (numbers[index] > maximum) {
                maximum = numbers[index];
            }
            
            index++;
        }

        printf("Minimum: %d\nMaximum: %d\n", minimum, maximum);
    }
    
    return;
}
