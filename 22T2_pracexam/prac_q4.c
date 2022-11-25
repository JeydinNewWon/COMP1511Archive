#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int product(struct node *head1, struct node *head2);
struct node *read_list(void);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(void) {
    // create two linked lists from standard input
    struct node *head1 = read_list();
    struct node *head2 = read_list();

    int result = product(head1, head2);
    printf("%d\n", result);

    return 0;
}

// product should return the sum of the elements in list1 multiplied by 
// the corresponding element in list2
// if one list is longer than the other, the extra list elements are ignored 
int product(struct node *head1, struct node *head2) {
    struct node *curr_1 = head1;
    struct node *curr_2 = head2;

    int product_sum = 0;
    while (curr_1 != NULL && curr_2 != NULL) {
        if (curr_1->data != -1 && curr_2->data != -1) {
            product_sum += curr_1->data * curr_2->data;
        }
        
        curr_1 = curr_1->next;
        curr_2 = curr_2->next;
    }

    return product_sum;
}

// DO NOT CHANGE THIS FUNCTION
// create linked list from integers on standard input
struct node *read_list(void) {
    struct node *head = NULL;
    struct node *tail = NULL;
    int num;
    while (scanf("%d", &num) == 1 && num != -1) {
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
