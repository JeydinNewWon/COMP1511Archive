// A program that prints out the dice range.
// By Jayden Nguyen z5362408
// 08/06/2022

#include <stdio.h>


int main(void) {
    int number_of_sides;
    int number_of_dice;

    printf("Enter the number of sides on your dice: ");
    scanf("%d", &number_of_sides);

    printf("Enter the number of dice being rolled: ");
    scanf("%d", &number_of_dice);

    if (number_of_sides < 1 || number_of_dice < 1) {
        printf("These dice will not produce a range.\n");
    } else {
        int max;
        double average;
        max = number_of_dice * number_of_sides;
        average = ((number_of_dice + max) * 1.0)/2;

        printf("Your dice range is %d to %d.\n", number_of_dice, max);
        printf("The average value is %lf\n", average);
    }

    return 0;

}