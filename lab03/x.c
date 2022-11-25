// Program to print a massive 'x' depending on the user input
// By Jayden Nguyen - z5362408
// 15/06/2022

#include <stdio.h>

int main(void) {
    int size;

    printf("Enter size: ");
    scanf("%i", &size);

    int row = 0;
    while (row < size) {
        int col = 0;
        while (col < size) {
            if (col == row || (col == size - row - 1)) {
                printf("*");
            } else {
                printf("-");
            }
            col++;
        }
        printf("\n");
        row++;
    }

    return 0;
}