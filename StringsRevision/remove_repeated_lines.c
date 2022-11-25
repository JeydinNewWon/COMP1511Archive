#include <stdio.h>
#include <string.h>


#define MAX_LINES_AND_CHARS 256

int main(void) {

    char remembered_lines[MAX_LINES_AND_CHARS + 1][MAX_LINES_AND_CHARS + 1];

    int i = 0;
    int j = 0;
    char input_char;

    char input_str[MAX_LINES_AND_CHARS + 1];
    while (scanf("%c", &input_char) == 1) {
        if (input_char != '\n') {
            input_str[j] = input_char;
            j++;
        } else if (input_char == '\n') {
            input_str[j] = '\0';


            int counter_remembered = 0;
            int print = 1;
            while (counter_remembered < i) {
                if (strcmp(remembered_lines[counter_remembered], input_str) == 0) {
                    print = 0;
                }
                counter_remembered++;
            }

            if (print) {
                printf("%s\n", input_str);
                strcpy(remembered_lines[i], input_str);
                i++;
            }
            j= 0;
        }
    }

}