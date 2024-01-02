#include <iostream>

using namespace std;

#define MINE 1
#define BLANK 0

int main()
{
    unsigned short grid_size_x = 10;
    unsigned short grid_size_y = 10;

    // Create 2D grid
    int** grid = generateGrid(grid_size_x, grid_size_y, 50);

    
}

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

	srand((unsigned) time(NULL));
    // Generate mines
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
    }

    return grid;
}