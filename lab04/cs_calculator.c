// Program that is a basic C lang calculator that takes in squares and products.
// By Jayden Nguyen z5362408
// 22/06/2022

#include <stdio.h>
#include <math.h>

#define MAX_NUMBERS 2

int main(void) {

    char command;
    int num_1;
    int num_2;

    printf("Enter instruction: ");
    
    // use while scanf(x) == 1 to stop ctrl d from changing it
    while (scanf(" %c", &command) == 1) {

        scanf(" %d", &num_1);
        if (command == 'p') {
            scanf(" %d", &num_2);
        }
        
        if (command == 's') {
            printf("%d\n", (num_1) * num_1);
        } else {
            int product = 1;
            int i = 0;
            while (i < num_2) {
                product *= num_1;
                i++;
            }

            printf("%d\n", product);
        }

        printf("Enter instruction: ");
    }
    return 0;
}