// Prints the first n digits of pi, where n is specified 
// By Jayden Nguyen z5362408
// 22/06/2022

#include <stdio.h>

#define MAX_DIGITS 10

void print_pi(int num_digits);

int main(void) {
    // DO NOT EDIT CODE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    printf("How many digits of pi would you like to print? ");
    int digits;
    scanf("%d", &digits);
    print_pi(digits);

    return 0;
    // DO NOT EDIT CODE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void print_pi(int num_digits) {
    // DO NOT CHANGE THIS LINE
    int pi[MAX_DIGITS] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    // TODO: Finish this function below
    int i = 0;
    while (i < num_digits) {
        if (i == 0) {
            printf("%d.", pi[i]);
        } else {
            printf("%d", pi[i]);
        }
        i++;
    }
    printf("\n");

}
