// A program that takes in a list of numbers, is terminated
// by Ctrl-D and then prints that list in reverse.
// By Jayden Nguyen z5362408
// 22/06/2022

#include <stdio.h>

int main(void) {
    int number_list[100];

    int i = 0;
    printf("Enter numbers forwards:\n");
    while (scanf(" %d", &number_list[i]) == 1) {
        i++;
    }

    printf("Reversed:\n");

    while (i > 0) {
        printf("%d\n", number_list[i - 1]);
        i--;
    }

    return 0;
}