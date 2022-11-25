// A program that runs a number guessing game until the use guesses the correct answer.
// By Jayden Nguyen - z5263408
// 15/06/2022

#include <stdio.h>

int main(void) {
    int answer;

    printf("Answer: ");
    scanf("%i", &answer);

    int guess;
    printf("Guess: ");
    scanf(" %i", &guess);

    while (guess != answer) {
        if (guess < answer) {
            printf("Too low\n");
        } else {
            printf("Too high\n");
        }
        printf("Guess: ");
        scanf(" %i", &guess);
    }

    printf("Correct!\n");

    return 0;
}