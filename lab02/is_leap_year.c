// A program to determine if a year is a leap year.
// By Jayden Nguyen z5362408
// 08/06/2022

#include <stdio.h>

int main(void) {
    int year;

    printf("Enter year: ");
    scanf("%d", &year);

    if (year % 4 != 0) {
        printf("%d is not a leap year.\n", year);
    } else if (year % 100 != 0) {
        printf("%d is a leap year.\n", year);
    } else if (year % 400 != 0) {
        printf("%d is not a leap year.\n", year);
    } else {
        printf("%d is a leap year.\n", year);
    }

}