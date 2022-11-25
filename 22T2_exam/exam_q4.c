#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Do not change these #defines, or your program will fail the autotests!
#define EMPTY_LIST -42

struct node {
    struct node *next;
    int          data;
};

struct node *find_smallest_node(struct node *head) {
    struct node *smallest = head;
    struct node *current = head;
    while (current != NULL) {
        if (current->data < smallest->data) {
            smallest = current;
        }
        current = current->next;
    }

    return smallest;
}

// delete_smallest should find the (first) node with the smallest value,
// and remove that node from the list.
//
// delete_smallest should return the head of the new list.
struct node *delete_smallest(struct node *head) {
    if (head == NULL) {
        return head;
    }
    struct node *smallest = find_smallest_node(head);

    if (smallest == head) {
        struct node *temp = smallest->next;
        free(smallest);
        return temp;
    } else {
        struct node *prev_to_smallest = head;
        struct node *current = head->next;
        while (current != smallest) {
            prev_to_smallest = current;
            current = current->next;
        }

        prev_to_smallest->next = smallest->next;
        free(smallest);
        return head;
    }
}


// If you want, you can write this function to use for debugging.
// It gets called in the main function below.
// If you don't want to write this function, you can just run the
// autotests (which have their own print_list function).
static void print_list(struct node *head) {
    printf("TODO: write code here to print the list "
           "(or just run the autotest)\n");
}

////////////////////////////////////////////////////////////////////////
//               DO NOT CHANGE THE CODE BELOW                         //
////////////////////////////////////////////////////////////////////////

struct node *delete_smallest(struct node *head);
struct node *read_list(void);
static void print_list(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = read_list();

    // If you're getting an error here,
    // you have returned an uninitialized value
    struct node *new_head = delete_smallest(head);
    printf("The new list is: ");
    print_list(new_head);

    return 0;
}

// DO NOT CHANGE THIS FUNCTION
// create linked list from standard input
struct node *read_list(void) {
    struct node *head = NULL;
    struct node *tail = NULL;
    int num;
    while (scanf("%d", &num) == 1) {
        struct node *n = malloc(sizeof (struct node));
        n->data = num;
        n->next = NULL;
        if (head == NULL) {
            head = n;
        } else {
            tail->next = n;
        }
        tail = n;
    }
    return head;
}
