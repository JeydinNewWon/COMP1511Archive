// Prints out a checkerboard based on user input.
// By Jayden Nguyen z5362408
// 29/06/2022

#include <stdio.h>
#include <assert.h>

#define BOARD_LENGTH 8
#define PIECE_RED 'R'
#define PIECE_BLACK 'B'
#define PIECE_EMPTY ' '
#define TYPE_KING 1
#define TYPE_NORMAL 0
struct board_square {
    int type;
    char piece_color;
};

// Prints out a checkerboard using the provided 2D array as reference.
void print_checkerboard(struct board_square board[BOARD_LENGTH][BOARD_LENGTH]);

int main(void) {
    // TODO: Declare a 2D struct board_square array representing your
    //       checkerboard, using the given struct board_square defined above as
    //       the array element type.
    //       Your checkerboard array size should be 8x8; BOARD_LENGTH has been
    //       defined above for you to accomplish this. Your checkerboard should
    //       not be an 2D int array.
    struct board_square board[BOARD_LENGTH][BOARD_LENGTH];


    // TODO: Initialize each member variable of each struct board_square in
    //       your checkerboard 2D array with:
    //          1. piece_color: A value of PIECE_EMPTY (i.e. it is empty)
    //          2. type:        A value of TYPE_NORMAL (i.e. no piece starts as king!)
    // HINT: How do you change elements of a 2D array? What about structs?
    int row = 0;
    while (row < BOARD_LENGTH) {
        int col = 0;
        while (col < BOARD_LENGTH) {
            board[row][col].piece_color = PIECE_EMPTY;
            board[row][col].type = TYPE_NORMAL;
            col++;
        }
        row++;
    }
   

    // TODO: Scan in instructions from the user for filling the checkerboard
    //       until Ctrl+D is entered
    // HINT: How do you continuously scan for user input?
    printf("Please enter pieces:\n");
    
    int col;
    char piece_color;
    int is_king; 


    
    while (scanf("%d %d %c %d", &row, &col, &piece_color, &is_king) == 4) {
        board[row][col].piece_color = piece_color;
        board[row][col].type = is_king;
    }
   

    // TODO: Pass your checkerboard 2D array to this function call!
    //       Refer to how the function is implemented below for more information
    //       on how the checkerboard is printed.
    // HINT: You need to change REPLACE_ME to your checkerboard 2D array. How do
    //       you pass whole arrays as function arguments?
    print_checkerboard(board);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////////////////// DO NOT EDIT THE CODE BELOW THIS LINE! ////////////////////
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// print_checkerboard(): Prints out a checkerboard using the provided 2D array
//                       as reference.
//
// Takes in:
// - `board[BOARD_LENGTH][BOARD_LENGTH]` -- The 2D array containing a
//                                          representation of the checkerboard
//
// Returns: nothing.
void print_checkerboard(struct board_square board[BOARD_LENGTH][BOARD_LENGTH]) {
    int row_index = 0;
    while (row_index < BOARD_LENGTH) {

        // NOTE: Print row dividers of checkerboard
        printf("+-----+-----+-----+-----+-----+-----+-----+-----+\n");
        printf("|");
        
        int column_index = 0;
        while (column_index < BOARD_LENGTH) {
            
            // NOTE: Check that all struct values contain valid input.
            assert(
                board[row_index][column_index].piece_color == PIECE_RED ||
                board[row_index][column_index].piece_color == PIECE_BLACK ||
                board[row_index][column_index].piece_color == PIECE_EMPTY
            );
   
            assert(
                board[row_index][column_index].type == TYPE_KING || 
                board[row_index][column_index].type == TYPE_NORMAL
            );
            
            // NOTE: Print column dividers of checkerboard
            if (board[row_index][column_index].type == TYPE_KING) {
                printf(" %c-K |", board[row_index][column_index].piece_color);
            } else {
                printf("  %c  |", board[row_index][column_index].piece_color);

            }
            
            column_index++;
        }
        
        printf("\n");
        row_index++;
    }
    // NOTE: Print final row divider of checkerboard
    printf("+-----+-----+-----+-----+-----+-----+-----+-----+\n");

    return;
}
