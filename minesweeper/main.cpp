#include <iostream>
#include "library/minesweeper_core.h"
#include "library/cli_utils.h"

using namespace std;

int main()
{
    int grid_size_x = 3;
    int grid_size_y = 3;
    int starting_x = 1;
    int starting_y = 1;

    // Create 2D grid
    minefield field = generateMinefield(grid_size_x, grid_size_y, 50, starting_x, starting_y);
    printGrid(field, false);

    // Main loop for user input
    bool won = false;
    while (true) {
        int* command = parseCommand(getCommandFromUser());
        // Validate command
        if (validateCommand(command, grid_size_x, grid_size_y)) {
            int x = command[0];
            int y = command[1];
            char option = command[2];
            if (command[2] == 'f') {
                // Flag coordinates
                addFlag(field.grid, x, y);
            }
            else {
                // Check coordinates
                checkSquare(field, x, y);
            }
        }
        else {
            cout << "Invalid command.\n";
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
