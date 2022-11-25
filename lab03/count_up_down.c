// Program to print all integers inclusive of n from 0 to n.
// By Jayden Nguyen z5362408
// 15/06/2022

#include <stdio.h>

int main(void) {
    int number;

    printf("Enter number: ");
    scanf("%i", &number);

    if (number > 0) {
        int i = 0;
        while (i <= number) {
            printf("%i\n", i);
            i++;
        }
    } else {
        int i = 0;
        while (i >= number) {
            printf("%i\n", i);
            i--;
        }
    }

    return 0;
}