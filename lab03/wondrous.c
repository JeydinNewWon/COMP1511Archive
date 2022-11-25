// Prints out a set of numbers according to the Collatz Conjecture.
// By Jayden Nguyen - z5362408
// 15/06/2022

#include <stdio.h>

int main(void) {
    int number;
    
    printf("What number would you like to see: ");
    scanf("%i", &number);

    while (number != 1) {
        int counter = 0;
        while (counter < number) {
            printf("*");
            counter++;
        }
        printf("\n");
        if (number % 2 == 0) {
            number = number/2;
        } else {
            number = 3*number + 1;
        }
    }

    return 0;
}