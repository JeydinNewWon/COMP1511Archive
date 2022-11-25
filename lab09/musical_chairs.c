#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

struct chair *prev_chair(struct chair *chairs, struct chair *chair_to_check);
int list_size(struct chair *chairs);
struct chair *be_seated(char name[MAX_NAME_LENGTH], struct chair *heir);

// Do not edit these structs. You may use them exactly as
// they are but you cannot make changes to them

// player in the game of chairs
struct player {
    char name[MAX_NAME_LENGTH];
};

// A node in a linked list of chairs
struct chair {
    struct player *sitting;
    struct chair *next;
};

// DECLARE ANY FUNCTIONS YOU WRITE HERE
struct chair *last_chair(struct chair *chairs) {
    struct chair *curr_chair = chairs;
    if (curr_chair == NULL) {
        return chairs;
    }
    while (curr_chair->next != NULL) {
        curr_chair = curr_chair->next;
    }

    return curr_chair;
}

int list_size(struct chair *chairs) {
    int size = 0;
    struct chair *curr_chair = chairs;
    while (curr_chair != NULL) {
        size++;
        curr_chair = curr_chair->next;
    }

    return size;
}

struct chair *prev_chair(struct chair *chairs, struct chair *chair_to_check) {
    struct chair *prev_chair = NULL;
    struct chair *curr_chair = chairs;
    while (curr_chair != chair_to_check) {
        prev_chair = curr_chair;
        curr_chair = curr_chair->next;
    }

    return prev_chair;
}

// Make music for a certain number of turns.
// Each turn of music makes the players move
// one chair along the list.
// After they've moved that many times, the
// first chair in the list is removed, along
// with the person sitting in it.
struct chair *make_music(int turns, struct chair *chairs) {
    // IMPLEMENT THIS FUNCTION
    struct chair *final_chair = last_chair(chairs);
    int size = list_size(chairs);
    
    struct chair *curr_chair_iterator = final_chair;
    struct chair *curr_chair_prev = prev_chair(chairs, final_chair);
    // struct chair *chairs_list_copy;

    int i = 0;
    while (i < turns - 1 && i < size) {
        curr_chair_iterator = curr_chair_prev;
        curr_chair_prev = prev_chair(chairs, curr_chair_iterator);
        i++;
    }

    final_chair->next = chairs;

    if (curr_chair_prev != NULL) {
        curr_chair_prev->next = NULL;
    }


    /*
    int z = 0;
    while (z < size) {
        chairs_list_copy = be_seated(curr_chair_iterator->sitting->name, curr_chair_iterator->next);
        
        curr_chair_iterator = curr_chair_prev;
        curr_chair_prev = prev_chair(chairs, curr_chair_iterator);
        z++;
    }

    //circulize
    final_chair->next = chairs;


    struct chair *curr_chair = chairs;
    int i = 0;
    while (i < size) {
        int shift_count = 0;
        struct chair *shifted_pos = curr_chair;
        while (shift_count < turns) {
            shifted_pos = shifted_pos->next;
            shift_count++;
        }

        
        curr_chair = curr_chair->next;
        i++;
    }

    final_chair->next = NULL;*/
    if (curr_chair_iterator != NULL) {
        struct chair *temp = curr_chair_iterator->next;
        printf("%s\n", curr_chair_iterator->sitting->name);
        free(curr_chair_iterator->sitting);
        free(curr_chair_iterator);
        return temp;
    }
    
    return curr_chair_iterator;
}

// This helper function is only for this main, but
// it may help you to both understand and test this exercise.
// You may use this function for testing, but
// YOU CANNOT CHANGE THIS FUNCTION
struct chair *be_seated(char name[MAX_NAME_LENGTH], struct chair *heir) {
    struct chair *c = malloc(sizeof(struct chair));
    c->sitting = malloc(sizeof(struct player));
    strcpy(c->sitting->name, name);
    c->next = heir;
    return c;
}

// This is a main function which could be used
// to test your make_music function.
// It will not be marked.
// Only your make_music function will be marked.
int main(void) {
    struct chair *thrones = be_seated("Robert Baratheon", NULL);
    thrones = be_seated("Cersei Lannister", thrones);
    thrones = be_seated("Joffrey Baratheon", thrones);
    thrones = be_seated("Eddard Stark", thrones);
    thrones = be_seated("Spoiler Alert", thrones);
        
    thrones = make_music(1, thrones);
    thrones = make_music(2, thrones);
    thrones = make_music(0, thrones);
    thrones = make_music(-1, thrones);

    free(thrones->sitting);
    free(thrones);
        
    return 0;
}

// DEFINE ANY FUNCTIONS YOU WRITE HERE


