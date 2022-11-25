#include <stdio.h>
#include <stdlib.h>


struct my_struct {
    int a;
    int b;
    int c;

};


int main(void) {
    struct my_struct my_struct = { 
        .a = 10,
        .b = 11,
        .c = 12
    };

    printf("%d %d %d \n ", my_struct.a, my_struct.b, my_struct.c);

}