// Assignment 0 - CS Chardle
// cs_chardle.c
//
// This program was written by Jayden Nguyen (z5362408)
// on 02/06/2022.
//
// This program is a guessing game modelled after Wordle. It reads in input of a letter and allows the user to guess for a fixed number of guesses until they get the correct answer.

#include <stdio.h>

#define MAX_ROUNDS 10
#define SCREEN_HEIGHT 10
#define CONVERT_TO_LOWERCASE 32

// prints out the game instructions.
void print_game_instructions(void) {
    printf("[COMP1511 Guessing Game: CS Chardle]\n\n");
    printf("Welcome to the COMP1511 guessing game.\n");
    printf("You will need to input a letter to guess,\n");
    printf("Then let the player see the screen, and make guesses.\n");
}

// prints out a list of stars depending on the integer of screen height.
void astericks_print(void) {
    int astericks_count = 0;
    while (astericks_count < SCREEN_HEIGHT) {
        printf("*\n");
        astericks_count++;
    }

}

int main(void) {
    print_game_instructions();

    char correct_letter;

    printf("What letter will the player guess? ");
    scanf("%c", &correct_letter);

    int is_lowercase = 'a' <= correct_letter && correct_letter <= 'z';
    int is_uppercase = 'A' <= correct_letter && correct_letter <= 'Z';

    if (is_lowercase || is_uppercase) {

        if (is_uppercase) {
            correct_letter += CONVERT_TO_LOWERCASE;
        }

        printf("The answer is '%c' (ascii %i).\n", correct_letter, correct_letter);
        
        astericks_print();

        int guess_count = 0;
        int continue_guess = 0;

        while (guess_count < MAX_ROUNDS && continue_guess == 0) {

            char guess;

            printf("What is guess #%d? ", guess_count + 1);
            scanf(" %c", &guess);

            if ((guess == correct_letter) || (guess + CONVERT_TO_LOWERCASE == correct_letter)) {
                printf("Congratulations! You got the letter right!\n");
                continue_guess = 1;

            } else if ('a' <= guess && guess <= 'z') {
                if (guess < correct_letter) {
                    printf("Not quite! Guess later in the alphabet.\n");
                } else {
                    printf("Not quite! Guess earlier in the alphabet.\n");
                }

            } else if ('A' <= guess && guess <= 'Z') {
                if (guess + CONVERT_TO_LOWERCASE < correct_letter) {
                    printf("Not quite! Guess later in the alphabet.\n");
                } else {
                    printf("Not quite! Guess earlier in the alphabet.\n");
                }
            }
            else {
                printf("Your guess must be a valid letter!\n");
            }

            guess_count++;
        }

    } else {
        printf("The answer must be a valid letter!\n");
    }

    return 0;
}
