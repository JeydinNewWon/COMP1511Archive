// CS Hotel.

// A Hotel system written in C with various commands.
// It takes in an initial set of guests, 
// followed by a series of commands
// that one can enter. 
//
// This program was written by Jayden Nguyen (z5362408)
// z5362408@unsw.edu.au
// on 1/07/2022
//

#include <stdio.h>

// Additional libraries here

#include <stdlib.h>

// Provided constants
#define TRUE 1
#define FALSE 0

#define TOTAL_FLOORS 8
#define ROOMS_PER_FLOOR 8
#define INITIAL_PRICE 10
#define NO_BOOKING -1

// Your constants here
#define DEFAULT_REVENUE 0
#define NO_FLOOR_FOUND -TOTAL_FLOORS
#define MAX_BURG_MOVES 3

// Provided struct
struct room {
    int booking_id;
    int price;
    int is_group;
    int is_royal;
};

// Extra Structs 
struct extra_data {
    int highest_guest_id;
    int prev_revenue; 
};

struct burg_room {
    int row;
    int col;
    int valid;
};

struct node {
    struct burg_room data;
    struct node *next;
};

struct LinkedList {
    struct node *head_ptr;
    int size;
};

struct vivid_res {
    int is_possible;
    int guests_needed;
};


// Provided functions use for game setup
// You do not need to use these functions yourself.
void init_hotel(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);

// You will need to use these functions for stage 1.
void print_hotel(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
void print_hotel_with_prices(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);

// utility functions
int validate_inputs(
                int floor, 
                int room_on_floors
            );

int get_revenue(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

int available_rooms_for_group(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                int floor
            );

void add_group_to_rooms(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                int number_of_guests, 
                int floor, 
                int booking_id
            );

void cheapest_group_floor(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                struct extra_data *extra_data, 
                int number_of_guests, 
                int booking_id
            );

int best_room (
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                int booking_id
            );

int royal_remove_group(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR],
                int booking_id
            );
void add_royal_to_room(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                struct extra_data *extra_data,
                int floor,
                int room_on_floor
            );

//////////////////////////////////////////////////

struct node *create_node(
                struct burg_room data, 
                struct node *address, 
                struct LinkedList *LinkedList
            );

void append (   
                struct LinkedList *LinkedList, 
                struct burg_room data  
            );

struct node *first_out(
                struct LinkedList *LinkedList
            );

int burglar_possible(
                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

void init_visited(
                int visited[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

void set_first_room( 
                    struct burg_room *first_room,
                    int found_bottom_room,
                    int room 
            );

void visit (    
                struct burg_room directions[MAX_BURG_MOVES], 
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                int row, 
                int col
            );

void get_vivid_data(
                int height, 
                int width, 
                char vivid_data[height][width]
            );

struct vivid_res check_vivid_room(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                int floor,
                int room_on_floor,
                int height, 
                int width, 
                char vivid_data[height][width]
            );

//////////////////////////////////////////////////
// main commands
void command_handler(
                char command, 
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                struct extra_data *additional_data
            );

// Stage 1
void find_guest(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

void add_guest(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                struct extra_data *extra_data
            );

void remove_guest(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

// Stage 2
void set_floor_price(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

void set_all_room_prices(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

void revenue_details(
                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR],
                struct extra_data *extra_data
            );

void add_guest_best_room(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                struct extra_data *extra_data
            );

void swap_rooms(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

// Stage 3
void add_group(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                struct extra_data *extra_data
            );

void group_option_1(
                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR],
                struct extra_data *extra_data
            );

void group_option_2(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                struct extra_data *extra_data
            );

void add_royal(
                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR],
                struct extra_data *extra_data
            );

// Stage 4

void burglar( 
                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

void vivid(     
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

void vivid_option_1(
                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );

void vivid_option_2(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
            );



// Your function prototypes here:

int main(void) {
    struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR];
    init_hotel(hotel);

    printf("Welcome to the CS Hotel!!\n\n");

    // TODO: Add your setup phase
    printf("Add your current guests, how many guests? ");
    int number_of_guests;
    scanf(" %d", &number_of_guests);

    printf("Input in your guests room numbers\n");

    int i = 0;
    int room_counter = 0;

    while (i < number_of_guests) {
        int floor, room_on_floor;

        scanf(" %d %d", &floor, &room_on_floor);
        if (validate_inputs(floor, room_on_floor)) {
            int room_to_book_id = hotel[floor][room_on_floor].booking_id;
            if (room_to_book_id == NO_BOOKING) {
                hotel[floor][room_on_floor].booking_id = room_counter;
                room_counter++;
            } else {
                printf("Room already occupied!\n");
            }
        } else {
            printf("Invalid room number!\n");
        }
        i++;

    }

    print_hotel(hotel);
    printf("Enter a command: ");
    char command;

    struct extra_data extra_data = { 
                                    .highest_guest_id = room_counter, 
                                    .prev_revenue = DEFAULT_REVENUE 
                                };

    while (scanf(" %c", &command) == 1) {
        command_handler(command, &hotel, &extra_data);
        printf("Enter a command: ");
    }
 
    // TODO: keep scanning in commands from the user until the user presses
    // ctrl-d

    printf("Bye!\n");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ADDITIONAL FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// This function handles all the commands 
// and is the main control centre
void command_handler(
                        char command, 
                        struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                        struct extra_data *extra_data 
    ) {
    if (command == 'p') {
        print_hotel(*hotel);
    } else if (command == '?') {
        find_guest(hotel);
    } else if (command == 'a') {
        add_guest(hotel, extra_data);
    } else if (command == 'l') {
        remove_guest(hotel);
    } else if (command == 'c') {
        print_hotel_with_prices(*hotel);
    } else if (command == '$') {
        set_floor_price(hotel);
    } else if (command == '^') {
        set_all_room_prices(hotel);
    } else if (command == 'r') {
        revenue_details(hotel, extra_data);
    } else if (command == 'j') {
        add_guest_best_room(hotel, extra_data);
    } else if (command == 's') {
        swap_rooms(hotel);
    } else if (command == 'g') {
        add_group(hotel, extra_data);
    } else if (command == '!') {
        add_royal(hotel, extra_data);
    } else if(command == 'b') {
        burglar(hotel);
    } else if (command == 'v') {
        vivid(hotel);
    }
}

// finds a guest and prints their 
// booking id for a given room and floor 
void find_guest(
                    struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {
    int floor, room_on_floor;
    scanf(" %d %d", &floor, &room_on_floor);

    if (validate_inputs(floor, room_on_floor)) {
        int booking_id = 
        (*hotel)[floor][room_on_floor].booking_id;
        if (booking_id != NO_BOOKING) {
            printf("Booking ID at Floor %d, Room %d is : %d\n", 
                    floor, 
                    room_on_floor, 
                    booking_id
                );
        } else {
            printf("Floor %d, Room %d is empty.\n", 
                    floor, 
                    room_on_floor
                );
        }

    } else {
        printf("Invalid room number!\n");
    }
    
}

// adds a guest to the hotel for
// a given room and floor
void add_guest(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                struct extra_data *extra_data
    ) {
    int floor, room_on_floor;
    scanf(" %d %d", &floor, &room_on_floor);

    if (validate_inputs(floor, room_on_floor)) {
        int booking_id = 
        (*hotel)[floor][room_on_floor].booking_id;

        if (booking_id == NO_BOOKING) {
            (*hotel)[floor][room_on_floor].booking_id = 
            extra_data->highest_guest_id;

            printf("Guest's booking id is: %d\n", 
                extra_data->highest_guest_id);
                extra_data->highest_guest_id++;

        } else {
            printf("Room already occupied!\n");
        }

    } else {
        printf("Invalid room number!\n");
    }
}

// removes a guest from hotel
// on a given room and floor
void remove_guest(
            struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {

    int floor, room_on_floor;

    scanf(" %d %d", 
            &floor, 
            &room_on_floor
        );

    if (validate_inputs(floor, room_on_floor)) {
        int booking_id = 
        (*hotel)[floor][room_on_floor].booking_id;

        if (booking_id != NO_BOOKING) {
            (*hotel)[floor][room_on_floor].booking_id = NO_BOOKING;
            (*hotel)[floor][room_on_floor].is_royal = FALSE;
            (*hotel)[floor][room_on_floor].is_group = FALSE;
            
            printf("Goodbye booking %d!\n", 
                     booking_id
                );
        } else {
            printf("This room is already empty.\n");
        }

    } else {
        printf("Invalid room number!\n");
    }


}

// sets a given price for all
// rooms on a given floor
void set_floor_price(
                        struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {
    int floor, new_price;
    scanf(" %d %d", 
            &floor, 
            &new_price
        );

    if ( 0 <= floor && floor < TOTAL_FLOORS ) {
        if (new_price >= 0) {
            int i = 0;
            while (i < ROOMS_PER_FLOOR) {
                (*hotel)[floor][i].price = new_price;
                i++;
            }
            
        } else {
            printf("Invalid price!\n");
        }
    } else  {
        printf("Invalid floor number!\n");
    }

}

// sets the price of the entire hotel
// by a given price change.
void set_all_room_prices(
                            struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {
    int price_change;
    scanf(" %d", &price_change);

    int floor = 0;
    while (floor < TOTAL_FLOORS) {
        int room = 0;
        while (room < ROOMS_PER_FLOOR) {
            (*hotel)[floor][room].price += price_change;
            if ((*hotel)[floor][room].price < 0) {
                (*hotel)[floor][room].price = 0;
            }
            room++;
        }
        floor++;
    }

}

// prints out the revenue for the current night.
// Also prints out revenue last time 
// that the command was called.
void revenue_details(
                        struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                        struct extra_data *extra_data
    ) {
    int current_revenue = get_revenue(hotel);
    int prev_revenue = extra_data->prev_revenue;

    printf("The total revenue for the night is $%d\n",
            current_revenue
        );

    if (current_revenue > prev_revenue) {      
        printf("This is $%d more than last time :)\n",
                current_revenue - prev_revenue
            );
    } else if (current_revenue < prev_revenue) {
        printf("This is $%d less than last time (haha lol)\n", 
                prev_revenue - current_revenue
            );
    } else {
        printf(
                "This is the same as the last time you asked :\\ \n"
            );
        
    }

    extra_data->prev_revenue = current_revenue;

}

// adds a guest to the highest possible room,
// going from left to right
void add_guest_best_room(
                            struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                            struct extra_data *extra_data
    ) {

    int found_room = best_room(hotel, extra_data->highest_guest_id);
    if (found_room) {
        extra_data->highest_guest_id++;
    }

}

// swap the rooms of two 
// specified floor and room 
// numbers. It takes in four arguments. 
void swap_rooms(
                    struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {
    int floor_a, room_on_floor_a, 
        floor_b, room_on_floor_b;
       
    
    scanf(" %d %d %d %d", 
            &floor_a, 
            &room_on_floor_a, 
            &floor_b, 
            &room_on_floor_b
        );

    if  ( validate_inputs(floor_a, room_on_floor_a) 
          && validate_inputs(floor_b, room_on_floor_b)
        ) {

        struct room temp = 
                            (*hotel)[floor_a][room_on_floor_a];

        struct room updated_room_a = {
            .price = temp.price,
            .booking_id = 
                        (*hotel)[floor_b][room_on_floor_b].booking_id,
            .is_royal = 
                        (*hotel)[floor_b][room_on_floor_b].is_royal,
            .is_group = 
                        (*hotel)[floor_b][room_on_floor_b].is_group
        };

        struct room updated_room_b = {
            .price = 
                     (*hotel)[floor_b][room_on_floor_b].price,
            .booking_id = temp.booking_id,
            .is_royal = temp.is_royal,
            .is_group = temp.is_group
        };

        (*hotel)[floor_a][room_on_floor_a] = 
                                            updated_room_a;
        (*hotel)[floor_b][room_on_floor_b] = 
                                            updated_room_b;
        
    } else {
        printf("Invalid room number!\n");
    }
}

// adds an entire group with two options.
// option 1 adds the group to the
// cheapest, lowest possible floor.
// option 2 adds the group to the 
// highest available floor.
void add_group(
                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                struct extra_data *extra_data
    ) {
    int option;
    scanf(" %d", &option);
    if (option == 1) {
        group_option_1(hotel, extra_data);
    } else {
        group_option_2(hotel, extra_data);
    }

}

// option 1 adds the group to the
// cheapest, lowest possible floor.
void group_option_1(
                        struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                        struct extra_data *extra_data
    ) {
    int number_of_guests;
    scanf(" %d", &number_of_guests);
    cheapest_group_floor(
                            hotel, 
                            extra_data, 
                            number_of_guests, 
                            extra_data->highest_guest_id
                        );

    extra_data->highest_guest_id++;
}

// option 2 adds the group to the 
// highest available floor.
void group_option_2(
                        struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                        struct extra_data *extra_data
                    ) {
    int number_of_guests, budget;

    scanf(" %d %d", &number_of_guests, &budget);

    int floor = 0;
    int found_floor = FALSE;
    while (floor < TOTAL_FLOORS && !found_floor) {
        if (available_rooms_for_group(hotel, floor + 1) >= 
            number_of_guests) {
            if (budget >= (*hotel)[floor][0].price) {
                found_floor = TRUE;
            }           
        }
        if (!found_floor) {
            floor++;
        }
    }

    if (found_floor) {
        add_group_to_rooms(
                            hotel, 
                            number_of_guests, 
                            floor, 
                            extra_data->highest_guest_id
                        );
        extra_data->highest_guest_id++;
    } else {
        printf("No available floor for your group booking!\n");
    }
    
}


// adds a royal guest to the hotel.
// royal guests will remove any 
// If a group occupies the room, it
// pushed the group to cheapest
// and lowest floor.
// Otherwise, the guest is removed
// and placed into the highest
// possible room.
void add_royal(
                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                struct extra_data *extra_data
    ) {

    int floor, room_on_floor;
    scanf(" %d %d", &floor, &room_on_floor);
    struct room room = (*hotel)[floor][room_on_floor];

    if (validate_inputs(floor, room_on_floor)) {
        if (!room.is_royal) {
            if (room.is_group) {
                int group_count = royal_remove_group(hotel, room.booking_id);
                add_royal_to_room(hotel, extra_data, floor, room_on_floor);
                cheapest_group_floor(hotel, extra_data, group_count, room.booking_id);
                

            } else if (room.booking_id != NO_BOOKING) {
                add_royal_to_room(hotel, extra_data, floor, room_on_floor);
                best_room(hotel, room.booking_id);
                
            } else {
                add_royal_to_room(hotel, extra_data, floor, room_on_floor);
            }

            extra_data->highest_guest_id++;


        } else {
            printf("Your Royal Highness, this room is not available\n");
        }
    } else {
        printf("Invalid room number!\n");
    }


}

// checks if a burglar can reach the rooftop.
void burglar(
                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {

    int found_top = burglar_possible(hotel);   
    if (found_top) {
        printf("Possible for a burglar to reach the rooftop!\n");
    } else {
        printf("Impossible for a burglar to reach the rooftop!\n");
    }

}

// checks if a vivid display is possible,
// given the hotel's layout.
// It has two options.
// Option 1 checks if it is possible,
// Option 2 checks the rooms needed
// to complete a desired display.
void vivid(
            struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {
    int option;
    scanf(" %d", &option);
    if (option == 1) {
        vivid_option_1(hotel);
    } else if (option == 2) {
        vivid_option_2(hotel);
    }
}

// vivid option 1, checks if 
// a given vivid display is possible.
void vivid_option_1(
                    struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {
    int height, width;

    scanf(" %d %d\n", &height, &width);
    
    if (height > TOTAL_FLOORS ||
        width > ROOMS_PER_FLOOR) {
        printf("Display impossible!\n");
        return;
    }

    char vivid_data[height][width];

    get_vivid_data(height, width, vivid_data);

    int row = 0;
    int vivid_possible = FALSE;
    while (row < TOTAL_FLOORS && !vivid_possible) {
        int col = 0;
        while (col < ROOMS_PER_FLOOR && !vivid_possible) {
            if (
                check_vivid_room(
                hotel, 
                row, 
                col, 
                height,
                width, 
                vivid_data).is_possible
                ) {

                vivid_possible = TRUE;
            }

            if (!vivid_possible) {
                col++;
            }
        }
        if (!vivid_possible) {
            row++;
        } 
    }

    if (vivid_possible) {
        printf("Display possible!\n");
    } else {
        printf("Display impossible!\n");
    }

}

// vivid option 2. Prints out the rooms needed
// for a given display.
void vivid_option_2(
                    struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {
    int height, width;

    scanf(" %d %d\n", &height, &width);
    
    if (height > TOTAL_FLOORS ||
        width > ROOMS_PER_FLOOR ) {
        printf("Display impossible!\n");
        return;
    }

    char vivid_data[height][width];
    struct vivid_res
           vivid_res[TOTAL_FLOORS][ROOMS_PER_FLOOR];

    get_vivid_data(height, width, vivid_data);
    int row = 0;

    while (row < TOTAL_FLOORS) {
        int col = 0;
        while (col < ROOMS_PER_FLOOR) {
            vivid_res[row][col] = check_vivid_room
                                                (
                                                    hotel, 
                                                    row,
                                                    col, 
                                                    height, 
                                                    width, 
                                                    vivid_data
                                                );
            col++;
        }
        row++;
    }

    struct vivid_res 
           best_start_room = vivid_res[0][0];
    int best_start_room_floor = 0;
    int best_start_room_num = 0;
    row = 0;
    while (row < TOTAL_FLOORS) {
        int col = 0;
        while (col < ROOMS_PER_FLOOR) {
            if (vivid_res[row][col].guests_needed < 
                best_start_room.guests_needed ) {

                best_start_room = vivid_res[row][col];
                best_start_room_floor = row;
                best_start_room_num = col;

            }
            col++;
        }
        row++;
    }

    printf("%d guests needed for display starting at position (%d, %d).\n", 
            best_start_room.guests_needed, 
            best_start_room_floor, 
            best_start_room_num
        );

}
//////////////////////////////////////////////////////////////////////////////
////////////////////////////// UTILITY FUNCTIONS /////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// Checks if a given floor and corresponding room
// lies within the boundaries of the hotel,
// and returns it as a boolean value.
int validate_inputs(int floor, int room_on_floor) {
    return (0 <= floor && floor < TOTAL_FLOORS) && 
           (0 <= room_on_floor && room_on_floor < ROOMS_PER_FLOOR);
}

// finds the cheapest and lowest available floor for a group,
// then adds them to the hotel.
void cheapest_group_floor(
                            struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                            struct extra_data *extra_data, 
                            int number_of_guests, 
                            int booking_id
                        ) {
    int floor = TOTAL_FLOORS;
    int available_floor = NO_FLOOR_FOUND;
    while (floor > 0) {
        if (available_rooms_for_group(hotel, floor) 
            >= number_of_guests ) {

            if (available_floor == NO_FLOOR_FOUND) {
                available_floor = floor - 1;

            } else if ((*hotel)[floor-1][0].price < 
                       (*hotel)[available_floor][0].price
                      ) {

                available_floor =  floor - 1;
            }

        }
        floor--;
    }

    if (available_floor != NO_FLOOR_FOUND) {
        add_group_to_rooms(
                            hotel, 
                            number_of_guests, 
                            available_floor, 
                            booking_id
                        );
    } else {
        printf("No available floor for your group booking!\n");
    }

}

// returns the number of available rooms
// on a given floor.
int available_rooms_for_group(
                                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                                int floor
                            ) {
    int room = 0;
    int available_rooms = 0;
    while (room < ROOMS_PER_FLOOR) {
        if ((*hotel)[floor-1][room].booking_id ==
             NO_BOOKING) {
            available_rooms++;
        }
        room++;
    }

    return available_rooms;    
}

// returns the revenue of the hotel,
// which is simply the sum of
// the prices of all occupied rooms.
int get_revenue(
                    struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
                ) {
    int revenue = DEFAULT_REVENUE;
    int floor = 0;
    while (floor < TOTAL_FLOORS) {
        int room = 0;
        while (room < ROOMS_PER_FLOOR) {
            struct room current_room = 
                        (*hotel)[floor][room];
            if (current_room.booking_id != NO_BOOKING) {
                revenue += current_room.price;
            }
            room++;
        }
        floor++;
    }
    
    return revenue;
}

// actually adds the groups to the
// rooms within the hotel.
void add_group_to_rooms(
                            struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                            int number_of_guests, int floor, 
                            int booking_id
                        ) {
    int room = 0;
    while (room < ROOMS_PER_FLOOR && 
           number_of_guests > 0) {

        if ((*hotel)[floor][room].booking_id == 
            NO_BOOKING) {

            (*hotel)[floor][room].booking_id = 
                                            booking_id;
            (*hotel)[floor][room].is_group = 
                                            TRUE;
            number_of_guests--;
        }
        room++;
    }

}

// finds the highest possible room,
// prioristing the leftmost side.
int best_room(
                struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                int booking_id
    ) {
    int found_room = FALSE;
    int floor = 0;
    int room;
    while (floor < TOTAL_FLOORS && !found_room) {
        room = 0;
        while (room < ROOMS_PER_FLOOR && !found_room) {
            if ((*hotel)[floor][room].booking_id == 
                NO_BOOKING) {

                found_room = TRUE;
            } else {
                room++;
            }
        }

        if (!found_room) {
            floor++;
        }
    }

    if (found_room) {
        (*hotel)[floor][room].booking_id = 
                                           booking_id;
    } else {
        printf("The hotel is full!\n");
    }
    
    return found_room;
}

// removes a group when a royal
// decides to occupy a room.
int royal_remove_group(
                            struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR],
                            int booking_id
    ) {
    int group_count = 0;
    int i = 0;
    while (i < TOTAL_FLOORS) {
        int j = 0;
        while (j < ROOMS_PER_FLOOR) {
            if ((*hotel)[i][j].booking_id == booking_id) {          
                struct room empty_room = {
                    .price = (*hotel)[i][j].price,
                    .booking_id = NO_BOOKING,
                    .is_group = FALSE,
                    .is_royal = FALSE
                };

                (*hotel)[i][j] = empty_room;

                group_count++;
            }
            j++;
        }
        i++;
    }

    return group_count;

}

// adds a royal to the room they desire.
void add_royal_to_room(
                        struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                        struct extra_data *extra_data,
                        int floor,
                        int room_on_floor
    ) {
    (*hotel)[floor][room_on_floor].booking_id = extra_data->highest_guest_id;
    (*hotel)[floor][room_on_floor].is_royal = TRUE;

}

// creates a node in a Linked List.
struct node *create_node(
                            struct burg_room data, 
                            struct node *address, 
                            struct LinkedList *LinkedList
    ) {
    struct node *new_node = 
                            malloc(sizeof(struct node));

    new_node->data = data;
    new_node->next = address;

    LinkedList->size++;

    return new_node;
}

// appends a node into a Linked List.
void append(
                struct LinkedList *LinkedList,
                struct burg_room data
    ) {
    if (LinkedList->size == 0) {
        LinkedList->head_ptr = create_node(
                                            data, 
                                            NULL, 
                                            LinkedList
                                        );
        return;
    }

    struct node *last_node = LinkedList->head_ptr;
    while (last_node->next != NULL) {
        last_node = last_node->next;

    }

    struct node *new_node = create_node(
                                            data, 
                                            NULL, 
                                            LinkedList
                                        );
    last_node->next = new_node;
}

// grabs the first element in the LinkedList, 
// then sets the first element to the
// next element.
struct node *first_out(
                        struct LinkedList *LinkedList
    ) {
    struct node *first_node = LinkedList->head_ptr;

    LinkedList->head_ptr = first_node->next;
    LinkedList->size--;

    return first_node;
}

// set up a 2D array to track the rooms
// a burglar has visited.
void init_visited(
                    int visited[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {
    int i = 0;
    while (i < TOTAL_FLOORS) {
        int j = 0;
        while (j < ROOMS_PER_FLOOR) {
            visited[i][j] = FALSE;
            j++;
        }
        i++;
    }

}

// finds the starting position
// for a potential burglar.
void set_first_room(
                        struct burg_room *first_room,
                        int found_bottom_room,
                        int room
    ) {
    if (found_bottom_room) {
        first_room->row = TOTAL_FLOORS - 1;
        first_room->col = room;
        first_room->valid = TRUE;
    } else {
        printf("Impossible for a burglar to reach the rooftop!\n");
        return;
    }

}

// visits a room, and checks the possible
// directions around it.
void visit(
            struct burg_room directions[MAX_BURG_MOVES], 
            struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
            int row, 
            int col
    ) {

    struct burg_room left, up, right;
    left.row = row;
    left.col = col - 1;

    if (col - 1 >= 0) {
        if ((*hotel)[row][col - 1].booking_id == NO_BOOKING) {
            left.valid = TRUE;
        } else {
            left.valid = FALSE;
        }
    } else {
        left.valid = FALSE;
    }

    up.row = row - 1;
    up.col = col;

    if (row - 1 >= 0) {
        if ((*hotel)[row - 1][col].booking_id == NO_BOOKING) {
            up.valid = TRUE;
        } else {
            up.valid = FALSE;
        }
    } else {
        up.valid = FALSE;
    }
    
    right.row = row;
    right.col = col + 1;

    if (col + 1 < ROOMS_PER_FLOOR) {
        if ((*hotel)[row][col + 1].booking_id == NO_BOOKING) {
            right.valid = TRUE;
        } else {
            right.valid = FALSE;
        }
    } else {
        right.valid = FALSE;
    }

    directions[0] = left;
    directions[1] = up;
    directions[2] = right;
}

// determines if a burglar can reach the rooftop.
// based on Breadth First Search Algorithm.
int burglar_possible(
                struct room(*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR]
    ) {
    int visited [TOTAL_FLOORS][ROOMS_PER_FLOOR];
    init_visited(visited);

    int found_bottom_room = FALSE;
    int i = 0;
    while (i < ROOMS_PER_FLOOR && !found_bottom_room) {
        if ((*hotel)[TOTAL_FLOORS-1][i].booking_id == NO_BOOKING) {
            found_bottom_room = TRUE;
        }
        if (!found_bottom_room) {
            i++;
        }
    }

    struct burg_room first_room;
    set_first_room(&first_room, found_bottom_room, i);

    struct LinkedList queue = {
        .head_ptr = NULL,
        .size = 0
    };

    append(&queue, first_room);
    int found_top = FALSE;

    while (queue.size > 0 && !found_top) {
        struct node *check = first_out(&queue);
        struct burg_room data = check->data;
        free(check);

        if (!visited[data.row][data.col]) {
            struct burg_room directions[MAX_BURG_MOVES] = {};
            visit(directions, hotel, data.row, data.col);
            visited[data.row][data.col] = TRUE;

            if (data.row == 0) {
                found_top = TRUE;
            } else {
                int array_count = 0;
                while (array_count < 3) {
                    struct burg_room room_visit = directions[array_count];
                    if (room_visit.valid && !visited[room_visit.row][room_visit.col]) {
                        append(&queue, room_visit);    
                    }
                    array_count++;
                }
            }
        }
    }

    return found_top;
}

// gets the raw string data from the
// console and converts it
// to a processable 2D Array.
void get_vivid_data(
                        int height, 
                        int width, 
                        char vivid_data[height][width]
    ) {
    char string_data[height][2 * width + 1];
    int i = 0;
    while (i < height) {
        fgets(string_data[i], width * 2 + 1, stdin);
        i++;
    }

    i = 0;
    while (i < height) {
        int j = 0;
        while (j < width * 2 - 1) {
            if (j % 2 == 0) {
                vivid_data[i][j / 2] = string_data[i][j];
            }
            j++;
        }
        i++;
    }
}

// returns a struct, vivid_res 
// which details the necessary information
// to determine the vivid commands.
struct vivid_res check_vivid_room(
                    struct room (*hotel)[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                    int floor,
                    int room_on_floor,
                    int height, 
                    int width, 
                    char vivid_data[height][width]
    ) {
    struct vivid_res vivid_r = {
        .is_possible = TRUE,
        .guests_needed = 0
    };

    if (floor + height > TOTAL_FLOORS || 
        room_on_floor + width > ROOMS_PER_FLOOR) {
        vivid_r.is_possible = FALSE;
        vivid_r.guests_needed = (TOTAL_FLOORS * ROOMS_PER_FLOOR) + 1;
        return vivid_r;
    }
    
    char segmented_hotel[height][width];

    int i = 0;
    int floor_count = floor;
    while (floor_count < floor + height) {
        int room_count = room_on_floor;
        int j = 0;
        while (room_count < room_on_floor + width) {
            struct room room = 
                               (*hotel)[floor_count][room_count];
            if (room.booking_id != NO_BOOKING) {
                segmented_hotel[i][j] = '#';
            } else {
                segmented_hotel[i][j] = '.';
            }
            j++;
            room_count++;
        }
        i++;
        floor_count++;
    }

    i = 0;
    while (i < height) {
        int j = 0;
        while (j < width) {
            if (segmented_hotel[i][j] == '.' && 
                vivid_data[i][j] == '#') {

                vivid_r.is_possible = FALSE;
                vivid_r.guests_needed++;
            }
            j++;
        }
        i++;
    }
    return vivid_r;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
/////////////////////////// (DO NOT EDIT BELOW HERE) ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided Function (you shouldn't need to edit this in stage 1 or 2)
// Initalises the booking id and price of each room in the hotel to be
// the default values.
void init_hotel(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    int row = 0;
    while (row < TOTAL_FLOORS) {
        int col = 0;
        while (col < ROOMS_PER_FLOOR) {
            hotel[row][col].booking_id = NO_BOOKING;
            hotel[row][col].price = INITIAL_PRICE;
            hotel[row][col].is_group = FALSE;
            hotel[row][col].is_royal = FALSE;
            col++;
        }
        row++;
    }
}

// Provided Function - DO NOT EDIT
// Prints out the hotel with the booking number of each room, or empty
// if there is no booking.
void print_hotel(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    printf(
        "\n"
        "         /--^--\\\n"
        "   _     |  O  |     _\n"
        " _/ \\___/_^___^_\\___/ \\_\n"
        "/                       \\\n");

    int row = 0;
    while (row < TOTAL_FLOORS) {
        int col = 0;
        printf("|--+--+--+--+--+--+--+--|\n");
        while (col < ROOMS_PER_FLOOR) {
            printf("|");
            if (hotel[row][col].booking_id == NO_BOOKING) {
                printf("  ");
            } else {
                printf("%02d", hotel[row][col].booking_id);
            }
            col++;
        }
        printf("|\n");
        row++;
    }
    printf(
        "|--+--+--+--+--+--+--+--|\n"
        "|         /^^^\\         |\n"
        "|_________|_\"_|_________|\n\n");
}

// Provided Function - DO NOT EDIT
// Prints out the hotel with the the price and booking number included.
void print_hotel_with_prices(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    printf(
        "\n"
        "             /--^--\\\n"
        "   _         |  O  |         _\n"
        " _/ \\_______/_^___^_\\_______/ \\_\n"
        "/                               \\\n");

    int row = 0;
    while (row < TOTAL_FLOORS) {
        int col = 0;
        printf("|---+---+---+---+---+---+---+---|\n");
        while (col < ROOMS_PER_FLOOR) {
            printf("|");
            if (hotel[row][col].booking_id == NO_BOOKING) {
                printf("   ");
            } else {
#ifndef NO_COLORS
                printf("\033[1;35m");
#endif
                printf("%03d", hotel[row][col].booking_id);
#ifndef NO_COLORS
                printf("\033[0m");
#endif
            }
            col++;
        }
        printf("|\n");
        col = 0;
        while (col < ROOMS_PER_FLOOR) {
            printf("|");
#ifndef NO_COLORS
            printf("\033[1;32m");
#endif
            printf("%03d", hotel[row][col].price);
#ifndef NO_COLORS
            printf("\033[0m");
#endif
            col++;
        }
        printf("|\n");
        row++;
    }
    printf(
        "|---+---+---+---+---+---+---+---|\n"
        "|             /^^^\\             |\n"
        "|_____________|_\"_|_____________|\n\n");
}