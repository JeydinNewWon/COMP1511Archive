#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct arg_node {
    int data;
    struct arg_node *next;
};

int evaluate_shreys_calculator_notation(int len, char *strings[]);
struct arg_node *prepend(struct arg_node **head, int data);
int is_operator(char data[]);
struct arg_node *create_node(struct arg_node *next, int data);
struct arg_node *remove_node(struct arg_node **head, struct arg_node *to_be_rm);

// your exam q6 code here!
// len - number of strings in the array
// strings - array of strings (operators and operands)
int evaluate_shreys_calculator_notation(int len, char *strings[]) {
    int i = 0;
    struct arg_node *head = NULL;
    /*
    int j = 0;
    while (j < len) {
        printf("%s\n", strings[j]);
        j++;
    }*/
    while (i < len) {
        if (is_operator(strings[i])) {
            struct arg_node *first_num = head->next;
            remove_node(&head, first_num);
            struct arg_node *second_num = head;
            remove_node(&head, second_num);

            int res;
            if (strings[i][0] == 'x') {
                res = first_num->data * second_num->data;
            } else if (strings[i][0] == '+') {
                res = first_num->data + second_num->data;
            } else if (strings[i][0] == '/') {
                res = first_num->data / second_num->data;
            } else {
                res = first_num->data - second_num->data;
            }
            free(first_num);
            free(second_num);
            prepend(&head, res);

        } else {
            prepend(&head, atoi(strings[i]));
        }
        i++;
    }

    int final_res = head->data;
    free(head);
    return final_res;
}

struct arg_node *create_node(struct arg_node *next, int data) {
    struct arg_node *new_node = malloc(sizeof(struct arg_node));
    new_node->next = next;
    new_node->data = data;

    return new_node;
}

struct arg_node *prepend(struct arg_node **head, int data) {
    struct arg_node *new_node = create_node(*head, data);
    *head = new_node;
    return *head;
    
}

struct arg_node *remove_node(struct arg_node **head, struct arg_node *to_be_rm) {
    struct arg_node *prev = NULL;
    struct arg_node *current = *head;

    while (current != to_be_rm) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    return current;

}

int is_operator(char data[]) {
    
    return (data[0] == 'x' || data[0] == '+' || data[0] == '-' || data[0] == '/');

}

///////////// PROVIDED CODE ///////////////
// DO NOT MODIFY THESE FUNCTIONS

// we may use a different main function for marking
// please ensure your evaluate_shreys_calculator_notation function is implemented. 
// DO NOT MODIFY THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    printf("%d\n", evaluate_shreys_calculator_notation(argc - 1, &argv[1]));
    return 0;
}
