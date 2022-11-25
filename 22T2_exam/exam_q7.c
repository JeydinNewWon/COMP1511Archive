// exam_q7.c
//
// This program was written by Jayden Nguyen (z5362408)
// on 12/08/2022
//
// One line summary of what this exercise does.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES_AND_CHARS 1000

#define TRUE 1
#define FALSE 0

int get_size(char pipe_layout[MAX_LINES_AND_CHARS +  2]) {
    int size =0;
    int i = 0;
    while (pipe_layout[i] != '\0') {
        size++;
        i++;
    }

    return i;
}

int is_pipe(char a) {
    return (a == '|' || a == '\\' || a == '/');
}

int pipe_counter(char pipe_layout[MAX_LINES_AND_CHARS + 2]) {
    int i = 0;
    int size = get_size(pipe_layout);
    int pipe_count = 0;
    while (i < size) {
        if (is_pipe(pipe_layout[i])) {
            pipe_count++;
        }
        i++;
    }

    return pipe_count;
}

int straight_pipe_count(char pipe_layout[MAX_LINES_AND_CHARS + 2]) {
    int i = 0;
    int size = get_size(pipe_layout);
    int straight_pipe_count = 0;
    while (i < size) {
        if (pipe_layout[i] == '|') {
            straight_pipe_count++;
        }
        i++;
    }

    return straight_pipe_count;
}

void print_arr(char input_data[MAX_LINES_AND_CHARS][MAX_LINES_AND_CHARS + 2], int row_size) {
    int r = 0;
    while (r < row_size) {
        printf("%s\n", input_data[r]);
        r++;
    }

}

int is_possible(char str_1[MAX_LINES_AND_CHARS + 2], char str_2[MAX_LINES_AND_CHARS + 2]) {
    int possible = TRUE;
    int i = 0;
    int str_1_size = strlen(str_1);
    while (i < str_1_size && possible) {
        if (str_1[i] == '|') {
            if (!is_pipe(str_2[i])) {
                possible = FALSE;
            }
        } else if (str_1[i] == '\\') {
            if (i != str_1_size - 1) {
                if (!is_pipe(str_2[i+1])) {
                    possible = FALSE;
                }
            }
        } else if (str_2[i] == '/') {
            if (i != 0) {
                if (!is_pipe(str_2[i-1])) {
                    possible = FALSE;
                }
            }
        }
        i++;
    }

    return possible;
}

int main(void) {
    char input_data[MAX_LINES_AND_CHARS][MAX_LINES_AND_CHARS + 2];

    char input_letter;
    int row = 0;
    int col = 0;
    while (scanf("%c", &input_letter) == 1) {
        if (input_letter != '\n') {
            input_data[row][col] = input_letter;
            col++;
        } else {
            input_data[row][col] = '\0';
            row++;
            col = 0;
        }
    }

    int swap = TRUE;
    while (swap) {
        swap = FALSE;
        int start_row = 1;
        while (start_row < row - 1) {
            if (pipe_counter(input_data[start_row]) < pipe_counter(input_data[start_row + 1])) {
                char temp[MAX_LINES_AND_CHARS + 2];
                strcpy(temp, input_data[start_row + 1]);
                strcpy(input_data[start_row + 1], input_data[start_row]);
                strcpy(input_data[start_row], temp);
                swap = TRUE;

            }
            start_row++;
        }
    }

    int straight_swap = TRUE;
    while (straight_swap) {
        straight_swap = FALSE;
        int i = 1;
        while (i < row - 1) {
            if (pipe_counter(input_data[i]) == pipe_counter(input_data[i+1]) && 
            straight_pipe_count(input_data[i]) < straight_pipe_count(input_data[i + 1])) {
                char temp[MAX_LINES_AND_CHARS + 2];
                strcpy(temp, input_data[i + 1]);
                strcpy(input_data[i + 1], input_data[i]);
                strcpy(input_data[i], temp);
                straight_swap = TRUE;
            }
            i++;
        }
    }

    int possible_swap = TRUE;
    while (possible_swap) {
        possible_swap = FALSE;
        int i = 1;
        while (i < row - 1) {
            if (pipe_counter(input_data[i]) == pipe_counter(input_data[i+1]) &&
            !is_possible(input_data[i], input_data[i+1])) {
                char temp[MAX_LINES_AND_CHARS + 2];
                strcpy(temp, input_data[i + 1]);
                strcpy(input_data[i + 1], input_data[i]);
                strcpy(input_data[i], temp);
                possible_swap = TRUE;
            }
            i++;
        }
    }


    print_arr(input_data, row);

    return 0;
}
