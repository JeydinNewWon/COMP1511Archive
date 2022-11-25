// Starter code for prac_q3

#include <stdio.h>

#define MAX_INPUTS 100

int main(void) {
    int inputs[MAX_INPUTS];

    int i = 0;
    int scanned_number;
    scanf(" %d", &scanned_number);
    inputs[i] = scanned_number;
    i++;

    while (scanned_number != 0) {
        scanf(" %d", &scanned_number);
        inputs[i] = scanned_number;
        i++;
    }

    int j = 0;
    while (inputs[j] != 0 && j < i + 1) {
        if (j % 2 == 0) {
            printf("%d ", inputs[j]);
        }
        j++;
    }

    j = 0;
    while (inputs[j] != 0 && j < i + 1) {
        if (j % 2 != 0) {
            printf("%d ", inputs[j]);
        }
        j++;
    }

    printf("\n");
    return 0;
}
