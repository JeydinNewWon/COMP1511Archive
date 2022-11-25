#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int mixed(struct node *head);
struct node *read_list(void);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(void) {
    // create linked list from standard input
    struct node *head = read_list();

    int result = mixed(head);
    printf("%d\n", result);

    return 0;
}

// mixed should return 1 if list contains both even and odd numbers
// mixed should return 0 otherwise
int mixed(struct node *head) {
    int contains_even = 0;
    int contains_odd = 0;

    struct node *current = head;
    while (current != NULL) {
        if (current->data % 2 == 0) {
            contains_even = 1;
        } else if (current->data % 2 != 0) {
            contains_odd = 1;
        }
        current = current->next;
    }

    return contains_even && contains_odd;
}


// DO NOT CHANGE THIS FUNCTION
// create linked list from integers on standard input
struct node *read_list(void) {
    struct node *head = NULL;
    struct node *tail = NULL;
    int num;
    while (scanf("%d", &num) == 1) {
        struct node *new = malloc(sizeof(struct node));
        new->data = num;
        new->next = NULL;
        if (head == NULL) {
            head = new;
        } else {
            tail->next = new;
        }
        tail = new;
    }
    return head;
}
