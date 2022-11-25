#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

enum bracket_type {
    CURVED,
    CURLY,
    ARROW,
    ANGLED,
    NONE
};

struct char_node {
    char data;
    int validated;
    struct char_node *next;
    enum bracket_type bracket_type;
};

struct char_node *create_node(char data, struct char_node *next) {
    struct char_node *new_node = malloc(sizeof(struct char_node));
    new_node->data = data;
    new_node->validated = FALSE;
    new_node->next = next;

    if (data == '(' || data == ')') {
        new_node->bracket_type = CURVED;
    } else if (data == '{' || data == '}') {
        new_node->bracket_type = CURLY;
    } else if (data == '<' || data == '>') {
        new_node->bracket_type = ARROW;
    } else if (data == '[' || data == ']') {
        new_node->bracket_type = ANGLED;
    } else {
        new_node->bracket_type = NONE;
    }

    return new_node;
}

void append(char data, struct char_node **head) {
    struct char_node *current = *head;
    struct char_node *new_node = create_node(data, NULL);
    if (current == NULL) {
        *head = new_node;
        return;
    }
    /*
    if (is_closed_one(new_node->data)) {
        struct char_node *first_pair = find_first_pair(*head, new_node);
        if (first_pair != NULL) {
            new_node->validated = TRUE;
            first_pair->validated = TRUE;
        }
    }*/

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
}

int is_open_one(char data) {
    return (data == '(' || data == '{' || data == '<' || data == '[');
}

int is_closed_one(char data) {
    return (data == ')' || data == '}' || data == '>' || data == ']');
}

/*
struct char_node *find_first_pair(struct char_node *head, struct char_node *test_node) {
    struct char_node *found = NULL;
    struct char_node *current = head;
    while (current != test_node) {
        if (is_closed_one(test_node->data) && current->bracket_type == test_node->bracket_type
        && !current->validated) {
            found = current;
        }
        current = current->next;
    }

    return found;
}

struct char_node *find_closed_pair(struct char_node *start, struct char_node *end) {
    struct char_node *found = NULL;
    struct char_node *current = start;
    while (current != end) {
        if (is_open_one(end->data)) {
            found = current;
        }
    }
}*/

struct char_node *find_last_open(struct char_node *head, struct char_node *end) {
    struct char_node *last_open = NULL;
    struct char_node *current = head;
    while (current != end) {
        if (is_open_one(current->data) && !current->validated) {
            last_open = current;
        }
        current = current->next;
    }

    return last_open;
}

struct char_node *find_prev(struct char_node *head, struct char_node *test) {
    struct char_node *current = head;
    struct char_node *prev = NULL;
    while (current != test) {
        prev = current;
        current = current->next;
    }

    return prev;
}

char get_closed_one(char data) {
    if (data == '(') {
        return ')';
    } else if (data == '{') {
        return '}';
    } else if (data == '<') {
        return '>';
    } else if (data == '[') {
        return ']';
    }
}



int main(void) {
    char input_data;
    struct char_node *head = NULL;

    while (scanf(" %c", &input_data) == 1) {
        append(input_data, &head);
    }

    struct char_node *current = head;
    int valid = TRUE;
    struct char_node *expected = NULL;
    while (current != NULL && valid) {
        if (is_closed_one(current->data)) {
            expected = find_last_open(head, current);
            if (expected == NULL) {
                valid = FALSE;
            } else {
                if (expected->bracket_type == current->bracket_type) {
                    expected->validated = TRUE;
                    current->validated = TRUE;
                } else {
                    valid = FALSE;
                }
            }
        }

        if (valid) {
            current = current->next;
        }

    }

    int final_check_flag = FALSE;

    if (valid) {
        struct char_node *final_check = head;
        while (final_check != NULL) {
            if (is_open_one(final_check->data) && !final_check->validated) {
                valid = FALSE;
                final_check_flag = TRUE;
            } else if (is_closed_one(final_check->data) && !final_check->validated) {
                valid = FALSE;
                final_check_flag = TRUE;
            }
            final_check = final_check->next;
        }
        
    }


    if (valid) {
        printf("Valid Sequence!\n");
    } else {
        printf("Invalid Sequence, the correct closing sequence is:\n");
        struct char_node *err_curr = current;
        while (err_curr != NULL) {
            if (is_open_one(err_curr->data) && !err_curr->validated) {
                printf("%c\n", get_closed_one(err_curr->data));
            }
            err_curr = find_prev(head, err_curr);
        }

        if (final_check_flag) {
            err_curr = head;
            while (err_curr->next != NULL) {
                err_curr = err_curr->next;
            }

            while (err_curr != NULL) {
                if (is_open_one(err_curr->data) && !err_curr->validated) {
                    printf("%c\n", get_closed_one(err_curr->data));
                }
                err_curr = find_prev(head, err_curr);
            }

        }
    }

    struct char_node *free_curr = head;
    while (free_curr != NULL) {
        struct char_node *temp = free_curr->next;
        free(free_curr);
        free_curr = temp;
    }

    return 0;
}
