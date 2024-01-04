#include "minesweeper_core.h"
#include <stdlib.h>
#include <time.h>


int** generateGrid(unsigned short grid_size_x, unsigned short grid_size_y, float percentage_mines) {
    // Generate 2D array to represent the grid
    int** grid = new int*[grid_size_x];
    for (int x = 0; x < grid_size_x; x++) {
        // For each column, generate grid_size_y rows
        grid[x] = new int[grid_size_y];

        // Make rows blank
        int y = 0; // Placed here to make IDE happy
        for (; y < grid_size_y; y++) {}
        {
            grid[x][y] = MINE;
        }
        
    }

    // Generate mines
	srand((unsigned) time(NULL));
    int num_squares = grid_size_x * grid_size_y;
    int num_mines = num_squares * (percentage_mines / 100);

    for (int i = 0; i < num_mines; i++)
    {
        // Set a random x and y coordinate to be a MINE
        unsigned short random_x = rand() % grid_size_x;
        unsigned short random_y = rand() % grid_size_y;
        if (grid[random_x][random_y] == BLANK) {
            grid[random_x][random_y] = MINE;
        }
        else {
            i--; // Loop again
        }
    }

    return grid;
}


