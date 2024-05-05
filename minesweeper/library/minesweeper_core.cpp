#include "minesweeper_core.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

// Generates a minefield with mines given the size and percentage of mines
minefield generateMinefield(int width, int height, float percentage) {
    minefield field;
    field.width = width;
    field.height = height;
    field.grid = generateGrid(width, height);

    addPercentageOfMines(field, percentage);

    return field;
}

// Generates a grid of blank squares
int** generateGrid(int width, int height) {
    // Generate 2D array to represent the grid
    int** grid = new int*[width];
    for (int x = 0; x < width; x++) {
        // For each column, generate grid_size_y rows
        grid[x] = new int[height];

        // Make rows blank
        for (int y = 0; y < height; y++)
        {
            grid[x][y] = BLANK;
        }
    }
    
    return grid;
}

// Makes a certain percentage of the board to mines. The percentage must be greater than 0 abd less than 100.
void addPercentageOfMines(minefield& field, float percentage) {
    // Validate percentage
    if (percentage <= 0 || percentage >= 100) {
        throw "Percentage of mines must be more than 0 and less than 100.";
    }

    // Calculate the number of mines needed
    int num_squares = field.width * field.height;
    int num_mines = num_squares * (percentage / 100);
    
    addMinesToGrid(field, num_mines);
}

// Adds a certain number of mines to a minefield. The number of mines must not be more than the number of squares.
void addMinesToGrid(minefield& field, int num_mines) {
    // Validate number of mines
    int num_squares = field.width * field.height;
    if (num_mines > num_squares) {
        throw "More mines than squares.";
    }

    srand((unsigned)time(NULL));
    for (int i = 0; i < num_mines; i++)
    {
        // Set a random x and y coordinate to be a MINE
        int random_x = rand() % field.width;
        int random_y = rand() % field.height;
        int* square = &field.grid[random_x][random_y];
        if (*square != MINE) {
            *square = MINE;// to test
        }
        else {
            i--; // Loop again
        }
    }
}

// Toggles a flag of a square in the grid
void addFlag(int** grid, int x, int y) {
    int* target_address = &(grid[x][y]);
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

// Unfinished
// Checks the square of the grid at the coordinates provided
void checkSquare(minefield& field, int x, int y) {
    int* target_address = &(field.grid[x][y]);

    if (*target_address == BLANK) {
        *target_address = countMines(field, x, y);
    }
}

// Count the mines around some square given by the coordinates x and y. The parameters x and y should not be 0 indexed.
int countMines(minefield& field, int x, int y) {
    // Use nested for loop to create offsets from -1 to 1 on both axis
    int count = 0;
    int offset_x;
    int offset_y;
    for (int i = -1; i < 1; i++)
    {
        offset_x = x + i;
        for (int j = -1; j < 1; j++)
        {
            offset_y = y + j;
            // Check offset coordinate is valid, and then if the square has a mine
            if (offset_x >= 1 && offset_x <= field.width &&
                    offset_y >= 1 && offset_y <= field.height &&
                    isSquareMine(field.grid[offset_x - 1][offset_y - 1])) {
                // If a valid set of offset coordinates, 
                count++;
            }
        }
    }

    return count;
}

// Returns true if the value provided is MINE or FLAGGED_MINE
bool isSquareMine(int square_value) {
    return square_value == MINE || square_value == FLAGGED_MINE;
}

// Unfinished
// Deletes the grid of a minefield
void deleteGrid(minefield& field) {

}