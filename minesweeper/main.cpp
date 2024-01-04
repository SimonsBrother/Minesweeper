#include <iostream>
#include "library/minesweeper_core.h"
#include "library/cli_utils.h"

using namespace std;

int main()
{
    unsigned short grid_size_x = 16;
    unsigned short grid_size_y = 16;

    // Create 2D grid
    int** grid = generateGrid(grid_size_x, grid_size_y, 10);
    printGrid(grid, grid_size_x, grid_size_y, false);

    // Main loop for user input
    bool won = false;
    while (true) {
        int* command = parseCommand(getCommandFromUser());
        if (command == NULL) {
            cout << "Invalid command.\n";
        }
        else if (validateCommand(command, grid_size_x, grid_size_y)) {
            
        }
    }

    // Display board

    if (won) {
        cout << "You won!\n";
    }
    else {
        cout << "You lost.\n";
    }
}
