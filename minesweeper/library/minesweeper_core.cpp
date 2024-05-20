#include "minesweeper_core.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

// Test validation
// Generates a minefield with mines given the size and percentage of mines, as well as the starting x and y coordinates (0-indexed).
minefield generateMinefield(int width, int height, float percentage, int starting_x, int starting_y) {
    // Validate starting square coordinates; width and height are validated in generateBlnkGrind and percentage is validated in addPercentageOfMines
    if (starting_x < 0 || starting_y < 0 || starting_x >= width || starting_y >= height) {
        throw "Starting square coordinates are invalid.";
    }

    minefield field;
    field.width = width;
    field.height = height;
    field.starting_x = starting_x;
    field.starting_y = starting_y;
    field.grid = generateBlankGrid(width, height);

    addPercentageOfMines(field, percentage);

    return field;
}

// Generates a 2D array "grid" of blank squares
int** generateBlankGrid(int width, int height) {
    if (width <= 0 || height <= 0) {
        throw "Invalid width or height.";
    }
    // Generate 2D array to represent the grid
    int** grid = new int*[width];
    
    // For each column, generate grid_size_y rows
    for (int x = 0; x < width; x++) {
        grid[x] = new int[height];

        // Go through each row...
        for (int y = 0; y < height; y++)
        {
            // ...and make each cell blank.
            grid[x][y] = BLANK;
        }
    }
    
    return grid;
}

// Makes a certain percentage of the board to mines. The percentage must be greater than 0 and less than 100.
void addPercentageOfMines(minefield& field, float percentage) {
    // Validate percentage
    if (percentage <= 0 || percentage >= 100) {
        throw "Percentage of mines must be more than 0 and less than 100.";
    }

    // Calculate the number of mines needed
    int num_squares = field.width * field.height;
    int num_mines = round(num_squares * (percentage / 100));
    
    addMinesToGrid(field, num_mines);
}

// Adds a certain number of mines to a minefield. The number of mines must not be more than the number of squares.
void addMinesToGrid(minefield& field, int num_mines) {
    // Validate number of mines
    int num_squares = field.width * field.height;
    if (num_mines >= num_squares) {
        throw "Too many mines (must be less than number of squares).";
    }

    srand((unsigned)time(NULL));
    for (int i = 0; i < num_mines; i++)
    {
        // Come up with a random x and y coordinate
        int random_x = rand() % field.width;
        int random_y = rand() % field.height;

        // Get the square in question, check if its blank or if its at the starting square; mines should never 
        // be placed at the starting square, nor should they replace an existing mine (because this would lead to the wrong number of mines being placed).
        int* square = &(field.grid[random_x][random_y]);
        bool square_is_blank = *square == BLANK;
        bool square_is_starting_square = random_x == field.starting_x && random_y == field.starting_y;

        if (square_is_blank && !square_is_starting_square) {
            *square = MINE;
        }
        else {
            i--; // Loop again
        }
    }
}

// Toggles a flag of a square in the grid - note this doesn't check if the square is valid.
void addFlag(minefield field, int x, int y) {
    if (x < 0 || x >= field.width || y < 0 || y >= field.height) {
        throw "Coordinates out of bounds.";
    }

    int* target_address = &(field.grid[x][y]);
    switch (*target_address) {
    case BLANK:
        *target_address = FLAGGED_BLANK;
        break;
    case FLAGGED_BLANK:
        *target_address = BLANK;
        break;
    case MINE:
        *target_address = FLAGGED_MINE;
        break;
    case FLAGGED_MINE:
        *target_address = MINE;
        break; // Not needed but there in case something's added and you forget to put this break in place
    }
}

// untested
// Checks the square of the grid at the coordinates; it is assumed the coordinates are 0 indexed provided. Returns true if it is safe.
bool checkSquare(minefield& field, int x, int y) {
    int* target_ptr = &(field.grid[x][y]);

    // User checked a mine, not safe, lost game
    if (*target_ptr == MINE) {
        return false;
    }

    // Check if the square is blank
    if (*target_ptr == BLANK) {
        *target_ptr = countSurroundingMines(field, x, y);

        // If there are no mines around the square, automatically check the squares around the initial square
        if (*target_ptr == 0) {
            int offset_x;
            int offset_y;
            for (int i = -1; i < 1; i++) {
                offset_x = x + i;
                for (int j = -1; j < 1; j++) {
                    offset_y = y + j;

                    // If the square is valid, check it
                    if (isSquareValid(field, offset_x, offset_y)) {
                        int num_mints = checkSquare(field, offset_x, offset_y);
                    }
                }
            }
        }        
    }

    // Flagged squares do nothing.
    return true;
}

// Count the mines around some square given by the coordinates x and y. The parameters x and y should be 0 indexed.
int countSurroundingMines(minefield& field, int x, int y) {
    // Use nested for loop to create offsets from -1 to 1 on both axis
    int mine_count = 0;
    int offset_x;
    int offset_y;
    for (int i = -1; i < 1; i++) {
        offset_x = x + i;
        for (int j = -1; j < 1; j++) {
            offset_y = y + j;

            // Check offset coordinate is valid, and then if the square has a mine. Check validity first, lazy evaluation will prevent error.
            if (isSquareValid(field, offset_x, offset_y) && isSquareMine(field.grid[offset_x][offset_y])) {
                mine_count++;
            }
        }
    }

    return mine_count;
}

// Returns true if the coordinates provided are valid. Coordinates must be 0 indexed.
bool isSquareValid(minefield& field, int x, int y) {
    return (x >= 0 && x < field.width) && (y >= 0 && y < field.height);
}

// Returns true if the value provided is MINE or FLAGGED_MINE
bool isSquareMine(int square_value) {
    return square_value == MINE || square_value == FLAGGED_MINE;
}
