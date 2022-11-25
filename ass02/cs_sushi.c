// cs_sushi.c
//
// This program was written by [Jayden Nguyen] (z5362408)
// on [20/07/2022]
//
// Writing a program that prints out a cs sushi train with various 
// command line interactions. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Additional libraries here

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  CONSTANTS  /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided constants
#define TRUE 1
#define FALSE 0

#define MAX_STRING_LENGTH 100
#define EMPTY_CUSTOMER "EMPTY"

#define COMMAND_ADD_TABLE 'a'
#define COMMAND_ADD_CUSTOMER 'c'
// TODO: you may choose to add additional #defines here.
#define COMMAND_PRINT 'p'
#define COMMAND_ADD_PLATE 'r'
#define COMMAND_PRINT_PLATE 't'
#define COMMAND_ORDER 'o'
#define COMMAND_BILL 'b'
#define COMMAND_QUIT 'q'
#define COMMAND_REVERSE 's'
#define COMMAND_ROTATE 'm'

// Provided Enums

// the numerical value is the cost of that plate color
enum plate_colour { RED = 3, GREEN = 4, BLUE = 5, PURPLE = 6, ORANGE = 7 };

enum sushi_type { VEGETARIAN, SEAFOOD, CHICKEN, TEMPURA };

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  STRUCTS  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided structs
struct table {
    char customer[MAX_STRING_LENGTH];
    struct plate *orders;
    struct table *next;
};

struct plate {
    char roll_name[MAX_STRING_LENGTH];
    enum plate_colour colour;
    enum sushi_type type;
    struct plate *next;
};

struct restaurant {
    struct table *tables;
    struct plate *plates;
};

struct extra_data {
    int quit;
    int train_reversed;
};

struct absolute_train_node {
    struct plate **plate_ptr;
    struct absolute_train_node *next;
};

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  FUNCTION PROTOTYPES  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Helper Functions
void print_restaurant(struct restaurant *restaurant);
int scanf_command(char *command);
void interpret_line(
    char buffer[MAX_STRING_LENGTH], char name[MAX_STRING_LENGTH],
    enum plate_colour *colour, enum sushi_type *type);

void interpret_order(
    char buffer[MAX_STRING_LENGTH], char customer[MAX_STRING_LENGTH],
    char roll[MAX_STRING_LENGTH]);

enum plate_colour string_to_colour(char colour[MAX_STRING_LENGTH]);
enum sushi_type string_to_type(char type[MAX_STRING_LENGTH]);
void remove_newline(char input[MAX_STRING_LENGTH]);
char color_to_char(enum plate_colour colour);
void to_type(char types[MAX_STRING_LENGTH], enum sushi_type type);
void to_colour(char cols[MAX_STRING_LENGTH], enum plate_colour colour);

// COMMANDS
void command_handler(char command, struct restaurant *sushi_restaurant, 
struct extra_data *extra_data);


void add_new_table(struct restaurant *sushi_restaurant);
void add_new_customer(struct restaurant *sushi_restaurant);
void add_new_plate(struct restaurant *sushi_restaurant, 
struct extra_data *extra_data);
void print_plates(struct restaurant *sushi_restaurant);


void add_order(struct restaurant *sushi_restaurant);
void final_bill(struct restaurant *sushi_restaurant);
void close_restaurant(struct restaurant *sushi_restaurant, 
struct extra_data *extra_data);
void reverse_train(struct restaurant *sushi_restaurant, 
struct extra_data *extra_data);
void rotate_train(struct restaurant *sushi_restaurant);
struct table *find_customer(struct restaurant *sushi_restaurant, 
char customer[MAX_STRING_LENGTH]);

struct plate *find_plate(struct restaurant *sushi_restaurant, 
char roll_name[MAX_STRING_LENGTH], int *found_plate);


// utility functions
struct table *create_table(struct table *next, 
struct plate *orders, char customer[MAX_STRING_LENGTH]);

struct plate *create_plate(char roll_name[MAX_STRING_LENGTH],
enum plate_colour colour, enum sushi_type type, 
struct plate *next );

int train_size(struct plate *head_plate);
struct plate *find_lowest_type(struct plate *head_plate);
struct plate *find_last_plate(struct plate *head_plate);
struct plate *find_prev_plate(struct plate *head_plate, 
struct plate *test_plate);
struct plate *find_highest_type(struct plate *head_plate);

void add_plate_to_train(struct restaurant *sushi_restaurant, 
struct plate *new_plate, struct plate *last_plate,
struct plate *prev_plate, int size);



////////////////////////////////////////////////////////////////////////////////
//////////////////////////  FUNCTION IMPLEMENTATIONS  //////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    struct restaurant *sushi_restaurant;

    printf("Welcome to CSE Sushi Restaurant!\n");

    sushi_restaurant = malloc(sizeof(struct restaurant));
    sushi_restaurant->tables = NULL;
    sushi_restaurant->plates = NULL;

    struct extra_data extra_data = { 
        .quit = FALSE,
        .train_reversed = FALSE
    };

    print_restaurant(sushi_restaurant);

    printf("Enter command: ");

    char command;
    while (scanf_command(&command) == 1) {
        command_handler(command, sushi_restaurant, &extra_data);
        if (extra_data.quit) {
            free(sushi_restaurant);
            printf("Thank you for dining with CSE Sushi Restaurant!\n");
            return 0;
        }
        printf("Enter command: ");
    }

    close_restaurant(sushi_restaurant, &extra_data);
    free(sushi_restaurant);
    printf("Thank you for dining with CSE Sushi Restaurant!\n");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ADDITIONAL FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Handles potential commands that are inputted via 
// the command line. It continually scans in potential inputs called
// by main and then executes the corresponding appropriate command 
// functions. 
void command_handler(char command, 
struct restaurant *sushi_restaurant , struct extra_data *extra_data) {

    if (command == COMMAND_PRINT) {
        print_restaurant(sushi_restaurant);
    } else if (command == COMMAND_ADD_TABLE) {
        add_new_table(sushi_restaurant);
    } else if (command == COMMAND_ADD_CUSTOMER) {
        add_new_customer(sushi_restaurant);
    } else if (command == COMMAND_ADD_PLATE) {
        add_new_plate(sushi_restaurant, extra_data);
    } else if (command == COMMAND_PRINT_PLATE) {
        print_plates(sushi_restaurant);
    } else if (command == COMMAND_ORDER) {
        add_order(sushi_restaurant);
    } else if (command == COMMAND_BILL) {
        final_bill(sushi_restaurant);
    } else if (command == COMMAND_QUIT) {
        close_restaurant(sushi_restaurant, extra_data);
    } else if (command == COMMAND_REVERSE) {
        reverse_train(sushi_restaurant, extra_data);
    } else if (command == COMMAND_ROTATE) {
        rotate_train(sushi_restaurant);
    }
}

// Command that adds a new empty table to 
// the sushi train.
// Called with 'a'.
void add_new_table(struct restaurant *sushi_restaurant) {
    struct table *new_table = create_table(NULL, NULL, EMPTY_CUSTOMER);
    struct table *current = sushi_restaurant->tables;

    if (current == NULL) {
        sushi_restaurant->tables = new_table;
        return;
    }

    while (current->next != NULL) {
        current = current->next;
    } 

    current->next = new_table;
}

// Assigns a new customer to an empty table.
// Takes in one argument, that is, their
// name. 
// Called with 'c'.
void add_new_customer(struct restaurant *sushi_restaurant) {
    printf("Enter customer name: ");
    char customer_name[MAX_STRING_LENGTH];
    fgets(customer_name, MAX_STRING_LENGTH, stdin);

    int len = strlen(customer_name);
    customer_name[len - 1] = '\0';

    struct table *current = sushi_restaurant->tables;

    while (current != NULL) {
        if (strcmp(current->customer, EMPTY_CUSTOMER) == 0) {
            strcpy(current->customer, customer_name);
            return;
        }
        current = current->next;
    }

    printf("No empty tables!\n");
}

// Adds a new plate to the sushi train.
// takes in three arguments, that is the
// name of the dish, its colour and
// its type. 
// Called with 'r'.
void add_new_plate(struct restaurant *sushi_restaurant, 
struct extra_data *extra_data) {
    char args[MAX_STRING_LENGTH];
    fgets(args, MAX_STRING_LENGTH, stdin);

    char dish_name[MAX_STRING_LENGTH];
    enum plate_colour colour;
    enum sushi_type type;

    interpret_line(args, dish_name, &colour, &type);
    struct plate *head_plate = sushi_restaurant->plates;
    int size = train_size(head_plate);
    struct plate *last_plate = find_last_plate(head_plate);

    struct plate *current_plate, *prev_plate;
    int i = 0;

    if (!extra_data->train_reversed) {
        struct plate *lowest_type = find_lowest_type(head_plate);
        current_plate = lowest_type;
        prev_plate = find_prev_plate(head_plate, lowest_type);

        if (last_plate != NULL) {
            last_plate->next = head_plate;
        }

        while (i < size && current_plate->type <= type) {
            prev_plate = current_plate;
            current_plate = current_plate->next;
            i++;
        }
    } else {
        struct plate *highest_type = find_highest_type(head_plate);
        current_plate = highest_type;
        prev_plate = find_prev_plate(head_plate, highest_type);

        if (last_plate != NULL) {
            last_plate->next = head_plate;
        }

        while (i < size && current_plate->type >= type) {
            prev_plate = current_plate;
            current_plate = current_plate->next;
            i++;
        }
    } 
    
    struct plate *new_plate = create_plate(dish_name, colour, 
                              type, current_plate);
                              
    add_plate_to_train(sushi_restaurant, new_plate, 
    last_plate, prev_plate, size);
}

// prints the current plates that are 
// on the sushi train.
// Called with 'p'.
void print_plates(struct restaurant *sushi_restaurant) {
    struct plate *current_plate = sushi_restaurant->plates;

    if (current_plate == NULL) {
        printf("    empty :(\n");
        return;
    }

    while (current_plate != NULL) {
        char str_type[MAX_STRING_LENGTH];
        char str_colour[MAX_STRING_LENGTH];

        to_type(str_type, current_plate->type);
        to_colour(str_colour, current_plate->colour);

        printf("    %s-%s-%s\n", current_plate->roll_name, str_type, str_colour);
        printf("      |\n");
        printf("      v\n");
        current_plate = current_plate->next;
    }
}

// Adds a new order to a table.
// Takes in input of the customer and
// the dish name.
// If the order is already in the train,
// take it off the train and give it to
// the respective customer's table.
// Else, it takes the input of a new
// plate and adds it to the respective
// customer's table.
// Called with 'o'.
void add_order(struct restaurant *sushi_restaurant) {
    char args[MAX_STRING_LENGTH];
    fgets(args, MAX_STRING_LENGTH, stdin);

    char customer[MAX_STRING_LENGTH];
    char roll_name[MAX_STRING_LENGTH];

    interpret_order(args, customer, roll_name);

    struct table *current_table = find_customer(sushi_restaurant, 
                                  customer);

    if (current_table == NULL) {
        return;
    }
    int found_plate = FALSE;
    struct plate *current_plate = find_plate(sushi_restaurant, 
                                  roll_name, &found_plate);
    struct plate *prev_plate = find_prev_plate(sushi_restaurant->plates, 
                               current_plate);

    struct plate *current_order = current_table->orders;

    if (current_order != NULL) {
        while (current_order->next != NULL) {
            current_order = current_order->next;
        }
    }

    if (found_plate) {
        if (prev_plate == NULL) {
            sushi_restaurant->plates = current_plate->next;
        } else {
            prev_plate->next = current_plate->next;
        }
        current_plate->next = NULL;
        if (current_order == NULL) {
            current_table->orders = current_plate;
        } else {
            current_order->next = current_plate;
        }

    } else {
        printf("Enter dish details: ");
        char new_args[MAX_STRING_LENGTH];
        fgets(new_args, MAX_STRING_LENGTH, stdin);

        char new_roll[MAX_STRING_LENGTH];
        enum plate_colour new_colour;
        enum sushi_type new_type;

        interpret_line(new_args, new_roll, &new_colour, &new_type);

        struct plate *new_order = create_plate(new_roll, 
                                  new_colour, new_type, NULL);
        if (current_order == NULL) {
            current_table->orders = new_order;
        } else {
            current_order->next = new_order;
        }
    }
}

// calculates the final bill for a given customer.
// takes all their plates and sums them to
// give a final bill. The value of each plate
// depends on its colour. 
// Called with 'b'.
void final_bill(struct restaurant *sushi_restaurant) {
    printf("Enter customer name: ");
    char customer[MAX_STRING_LENGTH];

    fgets(customer, MAX_STRING_LENGTH, stdin);
    int len = strlen(customer);
    if (customer[len - 1] == '\n') {
        customer[len - 1] = '\0';
    }

    struct table *current_customer = find_customer(sushi_restaurant, 
                                     customer);
    if (current_customer == NULL) {
        return;
    }

    int bill = 0;
    struct plate *current_order = current_customer->orders;
    while (current_order != NULL) {
        struct plate *temp = current_order->next;
        bill += current_order->colour;
        free(current_order);
        current_order = temp;
    }

    current_customer->orders = NULL;
    strcpy(current_customer->customer, EMPTY_CUSTOMER);

    printf("Thank you for dining with CSE Sushi! Your total is: $%d\n", bill);
}

// Closes the restaurant and frees all 
// the tables associated with it.
// removes everything from the trains 
// and eliminates the tables.
// Called with 'q'.
void close_restaurant(struct restaurant *sushi_restaurant, 
struct extra_data *extra_data) {

    struct table *current_table = sushi_restaurant->tables;
    while (current_table != NULL) {
        struct table *temp_table = current_table->next;

        struct plate *current_order = current_table->orders;
        while (current_order != NULL) {
            struct plate *temp_order = current_order->next;
            free(current_order);
            current_order = temp_order;
        }

        current_table->orders = NULL;

        free(current_table);
        current_table = temp_table;
    }

    sushi_restaurant->tables = NULL;

    struct plate *current_plate = sushi_restaurant->plates;
    while (current_plate != NULL) {
        struct plate *temp_plate = current_plate->next;
        free(current_plate);
        current_plate = temp_plate;
    }

    sushi_restaurant->plates = NULL;
    extra_data->quit = TRUE;
}

// Command that reverses 
// the current order of the train.
// Called with 'r'.
void reverse_train(struct restaurant *sushi_restaurant, 
struct extra_data *extra_data) {
    int size = train_size(sushi_restaurant->plates);
    

    if (size == 0) {
        extra_data->train_reversed = !(extra_data->train_reversed);
        return;
    }

    struct plate *last_plate = find_last_plate(sushi_restaurant->plates);
    struct plate *curr_plate = last_plate;
    struct plate *prev_plate = find_prev_plate(sushi_restaurant->plates, 
                               last_plate);


    int i = 0;
    while (i < size) {
        curr_plate->next = prev_plate;
        curr_plate = prev_plate;
        prev_plate = find_prev_plate(sushi_restaurant->plates, 
                     curr_plate);
        i++;
    }

    sushi_restaurant->plates = last_plate;
    extra_data->train_reversed = !(extra_data->train_reversed);
}

// Command that rotates the current
// train. Takes in one input, a number
// which to rotate the train by. It can
// be negative or positive.
// Called with 'm'.
void rotate_train(struct restaurant *sushi_restaurant) {
    char args[MAX_STRING_LENGTH];

    fgets(args, MAX_STRING_LENGTH, stdin);
    int rotations = atoi(args);

    struct plate *head_plate = sushi_restaurant->plates;
    int size = train_size(head_plate);
    struct plate *last_plate = find_last_plate(head_plate);

    int actual_rot = rotations % size;

    if (actual_rot > 0) {
        struct plate *curr_plate = head_plate;
        
        int i = 0;
        while (i < actual_rot - 1) {
            curr_plate = curr_plate->next;
            i++;
        }

        last_plate->next = head_plate;
        sushi_restaurant->plates = curr_plate->next;
        curr_plate->next = NULL;
    } else if (actual_rot < 0) {
        struct plate *curr_plate = last_plate;
        struct plate *prev_plate = find_prev_plate(head_plate, curr_plate);

        actual_rot = abs(actual_rot);

        int i = 0;
        while (i < actual_rot - 1) {
            curr_plate = prev_plate;
            prev_plate = find_prev_plate(head_plate, curr_plate);
            i++;
        }

        last_plate->next = head_plate;
        prev_plate->next = NULL;
        sushi_restaurant->plates = curr_plate;
    }

}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////UTILITY FUNCTIONS/////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Utility function that creates 
// a new table and returns it.
// Takes in the next table, 
// any possible orders and
// any given names.
struct table *create_table(struct table *next, 
struct plate *orders, char customer[MAX_STRING_LENGTH]) {
    struct table *new_table = malloc(sizeof(struct table));
    new_table->next = next;
    new_table->orders = orders;
    strcpy(new_table->customer, customer);

    return new_table;
}


// Utility function that creates
// a new plate and then returns it.
// Takes in a roll name,
// the plate's colour,
// its sushi type, and the plate
// that is potentially next to it.
struct plate *create_plate(char roll_name[MAX_STRING_LENGTH],
enum plate_colour colour, enum sushi_type type, 
struct plate *next) {
    struct plate *new_plate = malloc(sizeof(struct plate));
    strcpy(new_plate->roll_name, roll_name);
    new_plate->colour = colour;
    new_plate->type = type;
    new_plate->next = next;

    return new_plate;
}

// Utility function that returns 
// an integer which is the size of the train.
int train_size(struct plate *head_plate) {
    if (head_plate == NULL ) {
        return 0;
    }

    int i = 0;
    struct plate *current = head_plate;
    while (current != NULL) {
        i++;
        current = current->next;
    }

    return i;
}

// Utility function returns a plate pointer
// to the 'lowest' sushi type in the sushi_train.
struct plate *find_lowest_type(struct plate *head_plate) {
    if (head_plate == NULL) {
        return NULL;
    }

    struct plate *lowest = head_plate;
    struct plate *current = head_plate;
    while (current != NULL) {
        if (current->type < lowest->type) {
            lowest = current;
        }
        current = current->next;
    }

    return lowest;
}

// Utility function returns a plate pointer
// to the 'highest' sushi type in the sushi_train.
struct plate *find_highest_type(struct plate *head_plate) {
    if (head_plate == NULL) {
        return NULL;
    }

    struct plate *highest = head_plate;
    struct plate *current = head_plate;

    while (current != NULL) {
        if (current->type > highest->type) {
            highest = current;
        }
        current = current->next;
    }

    return highest;
}

// Utility function that returns a pointer to
// the last plate in the sushi_train.
struct plate *find_last_plate(struct plate *head_plate) {
    if (head_plate == NULL) {
        return head_plate;
    }

    struct plate *current = head_plate;
    while (current->next != NULL) {
        current = current->next;
    }

    return current;
}

// Utility function that returns a pointer
// to a plate that is immediately before to
// the inputted plate in the sushi train.
struct plate *find_prev_plate(struct plate *head_plate, 
struct plate *test_plate) {
    struct plate *prev_plate = NULL;
    struct plate *current_plate = head_plate;
    while (current_plate != NULL && current_plate != test_plate) {
        prev_plate = current_plate;
        current_plate = current_plate->next;
    }

    return prev_plate;
}


// Utility function that actually 
// performs the actual action of adding 
// a new plate to the sushi train.
void add_plate_to_train(struct restaurant *sushi_restaurant, 
struct plate *new_plate, struct plate *last_plate, 
struct plate *prev_plate, int size) {
    if (prev_plate == NULL) {
        sushi_restaurant->plates = new_plate;
        if (size > 0) {
            last_plate->next = NULL;
        }
    } else {
        prev_plate->next = new_plate;
        if (prev_plate == last_plate) {
            new_plate->next = NULL;
            
        } else {
            last_plate->next = NULL;
        }
    }

}

// Utility function that returns a 
// table pointer that corresponds
// to an inputted customer name 
// if found. Else, return NULL.
struct table *find_customer(struct restaurant *sushi_restaurant, 
char customer[MAX_STRING_LENGTH]) {
    struct table *current_table = sushi_restaurant->tables;
    int found = FALSE;
    while (current_table != NULL && !found) {
        if (strcmp(customer, current_table->customer) == 0) {
            found = TRUE;
        }

        if (!found) {
            current_table = current_table->next;
        }
    }

    if (!found) {
        printf("There is no customer with that name!\n");
        return NULL;
    }

    return current_table;
}

// Utility function that returns a 
// plate pointer that corresponds to
// a certain roll_name. 
struct plate *find_plate(struct restaurant *sushi_restaurant, 
char roll_name[MAX_STRING_LENGTH], int *found_plate) {
    struct plate *current_plate = sushi_restaurant->plates;
    while (current_plate != NULL && !(*found_plate)) {
        if (strcmp(roll_name, current_plate->roll_name) == 0) {
            *found_plate = TRUE;
        }
        if (!(*found_plate)) {
            current_plate = current_plate->next;
        }
    }

    return current_plate;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
/////////////////////////// (DO NOT EDIT BELOW HERE) ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided Function - DO NOT EDIT
void print_restaurant(struct restaurant *restaurant) {
    int i;
    if (restaurant == NULL) {
        printf("ERROR: No restaurant!\n");
        return;
    };

    printf("CSE Sushi Restaurant\n");
    struct table *table = restaurant->tables;
    int table_num = 0;
    while (table != NULL) {
        int table_length = 5;
        if (strcmp(table->customer, EMPTY_CUSTOMER) != 0) {
            table_length = strlen(table->customer) + 4;
        }
        // calculate number of plates
        int number_of_plates = 0;
        struct plate *curr = table->orders;
        while (curr != NULL) {
            number_of_plates++;
            curr = curr->next;
        }

        printf(" ");
        for (i = 0; i < table_length; i++) {
            printf("_");
        }
        printf(" ");

        // print out the top row
        for (i = 0; i < number_of_plates; i++) {
            printf("    _____ ");
        }

        printf("\n");

        // print out the data
        int occupied = FALSE;
        if (strcmp(table->customer, "EMPTY") != 0) {
            occupied = TRUE;
        }
        if (occupied) {
            printf("|  %s  |-->", table->customer);
        } else {
            printf("|  %d  |-->", table_num);
        }

        // print out the plates
        struct plate *order = table->orders;
        while (order != NULL) {
            printf("|  %c  |-->", color_to_char(order->colour));

            order = order->next;
        }

        printf("\n");
        printf(".");
        for (i = 0; i < table_length; i++) {
            printf("-");
        }
        printf(".");
        // print out the top row
        for (i = 0; i < number_of_plates; i++) {
            printf("   |-----|");
        }

        printf("\n");
        table = table->next;
        table_num++;
    }
}

// Helper Function
// scans a single character from the user and returns the value of scanf;
//
// Parameters:
//  - command: a pointer to a character to store the command
//
// Returns:
//  - the value that scanf returns (this will be 1 if it was successfully read);
//
// Usage:
//  ```
//  char command;
//  while (scanf_command(&command) == 1) {
//  ```
// this function does some wizadry that you **do not need to understand**
// for you to ensure that subsequent
// calls to fgets works correctlly.
int scanf_command(char *command) {
    // read in character + newline + null-terminator
    char buffer[3];
    char *result = fgets(buffer, 3, stdin);
    if (result == NULL) {
        return EOF;
    }

    // a non a-z character probably means not a char
    if (buffer[0] < 'a' || buffer[0] > 'z') {
        return EOF;
    }

    // set the character
    *command = buffer[0];
    return 1;
}

// Helper Function
// You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
//
// Given a raw string in the format: [string] [enum1] [enum2]
// This function will extract the relevant values into the given variables.
// The function will also remove any newline characters.
//
// For example, if given: "salmon red seafood"
// The function will copy the string:
//     "salmon" into the 'name' array
// And will copy the enums:
//     red      into the colour pointer
//     seafood  into the type pointer
//
// If you are interested, `strtok` is a function which takes a string,
// and splits it up into before and after a "token" (the second argument)
//
// Parameters:
//     buffer  = A null terminated string in the following format
//               [string] [enum1] [enum2]
//     name    = An array for the [string] to be copied into
//     colour  = A pointer to where [enum1] should be stored
//     type    = A pointer to where [enum2] should be stored
// Returns:
//     None
void interpret_line(
    char buffer[MAX_STRING_LENGTH], char name[MAX_STRING_LENGTH],
    enum plate_colour *colour, enum sushi_type *type) {
    // Remove extra newline
    remove_newline(buffer);

    // Extract value 1 as string (sushi roll name)
    char *name_str = strtok(buffer, " ");
    if (name_str != NULL) {
        // Extract word
        strcpy(name, name_str);
    }

    // Extract value 2 as str, then enum
    char *colour_str = strtok(NULL, " ");
    if (colour_str != NULL) {
        *colour = string_to_colour(colour_str);
    }

    // Extract value 2 as str, then enum
    char *type_str = strtok(NULL, " ");
    if (type_str != NULL) {
        *type = string_to_type(type_str);
    }

    if (name_str == NULL || colour_str == NULL || type_str == NULL) {
        // If any of these are null, there were not enough words.
        printf("Could not properly interpret line: %s.\n", buffer);
    }
}

// Helper Function
// You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
//
// Given a raw string in the following foramt: [string1] [string2]
// This function will extract the relevant values into the given variables.
// The function will also remove any newline characters.
//
// For example, if given: "Gab salmon"
// The function will put:
//     "Gab" into the 'customer' array
//     "salmon" into the 'roll' array
//
// Parameters:
//     buffer   = A null terminated string in the following format
//                [string1] [string2]
//     customer = An array for the [string1] to be copied into
//     roll     = An array for the [string2] to be copied into
// Returns:
//     None
void interpret_order(
    char buffer[MAX_STRING_LENGTH], char customer[MAX_STRING_LENGTH],
    char roll[MAX_STRING_LENGTH]) {
    // Remove extra newline
    remove_newline(buffer);

    // Extract value 1 as string
    char *customer_str = strtok(buffer, " ");
    if (customer_str != NULL) {
        strcpy(customer, customer_str);
    }

    // Extract value 2 as string
    char *roll_str = strtok(NULL, " ");
    if (roll_str != NULL) {
        strcpy(roll, roll_str);
    }

    if (customer_str == NULL || roll_str == NULL) {
        // If any of these are null, there were not enough words.
        printf("Could not properly interpret line: %s.\n", buffer);
    }
}

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will remove and first newline it sees.
// The newline character wil be replaced with a null terminator ('\0')
void remove_newline(char input[MAX_STRING_LENGTH]) {
    // Find the newline or end of string
    int index = 0;
    while (input[index] != '\n' && input[index] != '\0') {
        index++;
    }
    // Goto the last position in the array and replace with '\0'
    // Note: will have no effect if already at null terminator
    input[index] = '\0';
}

// Helper Function
// You likely do not need to change this function.
//
// Given an enum plate_colour will return the first letter of enum, or ? if the
// value is not one of the plate_colour values.
// Parameters:
//     colour  = enum plate_colour for a plate
// Returns:
//     char    = character represtning the first letter of the plate colour
char color_to_char(enum plate_colour colour) {
    if (colour == RED) {
        return 'r';
    } else if (colour == GREEN) {
        return 'g';
    } else if (colour == BLUE) {
        return 'b';
    } else if (colour == PURPLE) {
        return 'p';
    } else if (colour == ORANGE) {
        return 'o';
    } else {
        return '?';
    }
}

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will return the corresponding enum plate_colour, or FALSE
// if the string doesn't correspond with the enums.
// Parameters:
//     colour  = string representing the corresponding enum plate_colour value
// Returns:
//     enum plate_colour
enum plate_colour string_to_colour(char colour[MAX_STRING_LENGTH]) {
    if (strcmp(colour, "red") == 0) {
        return RED;
    } else if (strcmp(colour, "green") == 0) {
        return GREEN;
    } else if (strcmp(colour, "blue") == 0) {
        return BLUE;
    } else if (strcmp(colour, "purple") == 0) {
        return PURPLE;
    } else if (strcmp(colour, "orange") == 0) {
        return ORANGE;
    }
    return FALSE;
}

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will return the corresponding enum sushi_type, or FALSE
// if the string doesn't correspond with the enums.
// Parameters:
//     type  = string representing the corresponding enum sushi_type value
// Returns:
//     enum sushi_type
enum sushi_type string_to_type(char type[MAX_STRING_LENGTH]) {
    if (strcmp(type, "vegetarian") == 0) {
        return VEGETARIAN;
    } else if (strcmp(type, "seafood") == 0) {
        return SEAFOOD;
    } else if (strcmp(type, "chicken") == 0) {
        return CHICKEN;
    } else if (strcmp(type, "tempura") == 0) {
        return TEMPURA;
    }
    return FALSE;
}

// Helper Function
// You likely do not need to change this function.
//
// Given an enum sushi_type will return the enum name as a string, or "ERROR" if
// the value was not one of the given enums.
// Parameters:
//     types  = string to store the name of the enum in
//     type   = sushi_type enum to have the name stored in types.
// Returns:
//     None
void to_type(char types[MAX_STRING_LENGTH], enum sushi_type type) {
    if (type == VEGETARIAN) {
        strcpy(types, "vegetarian");
    } else if (type == SEAFOOD) {
        strcpy(types, "seafood");
    } else if (type == CHICKEN) {
        strcpy(types, "chicken");
    } else if (type == TEMPURA) {
        strcpy(types, "tempura");
    } else {
        strcpy(types, "ERROR");
    }
}

// Helper Function
// You likely do not need to change this function.
//
// Given an enum plate_colour will return the enum name as a string, or "ERROR"
// if the value was not one of the given enums.
// Parameters:
//     cols   = string to store the name of the enum in
//     colour = plate_colour enum to have the name stored in cols
// Returns:
//     None
void to_colour(char cols[MAX_STRING_LENGTH], enum plate_colour colour) {
    if (colour == RED) {
        strcpy(cols, "red");
    } else if (colour == BLUE) {
        strcpy(cols, "blue");
    } else if (colour == GREEN) {
        strcpy(cols, "green");
    } else if (colour == PURPLE) {
        strcpy(cols, "purple");
    } else if (colour == ORANGE) {
        strcpy(cols, "orange");
    } else {
        strcpy(cols, "ERROR");
    }
}
