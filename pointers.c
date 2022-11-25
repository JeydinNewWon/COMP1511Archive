#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *queer = malloc(sizeof(*queer));
    *queer = 69;

    printf("%p\n", queer);
    return 0;
}