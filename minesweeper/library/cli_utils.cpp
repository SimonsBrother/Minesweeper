#include "cli_utils.h"
#include <iostream>

using namespace std;

// Displays the grid
void printGrid(minefield field, bool reveal_mines, bool use_square_for_blanks) {
    int grid_size_x_digit_count = countDigits(field.width);
    int grid_size_y_digit_count = countDigits(field.height);
    
    printGridHeader(field, grid_size_x_digit_count, grid_size_y_digit_count);

    // For each row
    for (int y = 0; y < field.height; y++)
    {
        // Print row number
        printChar(' ', grid_size_y_digit_count - countDigits(y + 1)); // Spacing before row number
        cout << y + 1;
        
        // For each column
        for (int x = 0; x < field.width; x++)
        {
            // Print spacing between columns
            printChar(' ', grid_size_x_digit_count);
            printGridSquare(field.grid[x][y], reveal_mines, use_square_for_blanks);
        }
        cout << '\n';
    }
}

// Print numbered header of the grid of a minefield
void printGridHeader(minefield field, int grid_size_x_digit_count, int grid_size_y_digit_count) {
    // Print numbered header
    printChar(' ', grid_size_y_digit_count); // Add blank area for the numbered rows
    cout << ' '; // Gap between numbered rows and values
    for (int i = 1; i <= field.width; i++)
    {
        printChar(' ', grid_size_x_digit_count - countDigits(i)); // Spacing
        cout << i << ' '; // Print number and a gap
    }
    cout << '\n';
}

// Print the value of some square, with different symbols.
void printGridSquare(int square_value, bool show_mines, bool use_square_for_blanks) {
    switch (square_value) {
        case MINE:
            // If meant to show mines, display the mine and break
            if (show_mines) {
                cout << 'x';
                break;
            }
            // If not meant to show mines, show blank via not breaking, and fall through to blank case

        case BLANK:
            if (show_mines) {
                cout << "."; // Show full stop for showing results for clarity
            }
            else if (use_square_for_blanks) {
                // Print a square rather than a question mark (only supported on some terminals)
                cout << "\u25A0";
            }
            else {
                cout << '?';
            }
            break;

        case FLAGGED_MINE:
            // If meant to show mines, display the mine and break
            if (show_mines) {
                cout << 'X'; // Uppercase to indicate found mine
                break;
            }
            // If not, don't break, to fall through to flag

        case FLAGGED_BLANK:
            cout << "f";
            break;

        default:
            // At this point the value will be a discovered square with the number of mines around it
            cout << square_value;
    }
}

// Calculates how many decimal digits are needed for the number provided
int countDigits(int number) {
    // Handle corner case that doesn't work with the method below
    if (number == 0) {
        return 1;
    }

    // Integer division by 10 as many times as needed to get number to 0
    int count = 0;
    while (number != 0) {
        number /= 10;    
        count++;
    }

    return count;
}

// Prints character 'ch' 'count' times. Does not print a newline.
void printChar(char ch, unsigned int count) {
    for (int i = 0; i < count; i++)
    {
        cout << ch;
    }
}

// Gets a command from the user
string getCommandFromUser() {
    string input;
    cout << ">>> ";
    getline(cin, input);

    return input;
}

// Splits a string into an array of three parts; the first two parts are numbers and the third is a character
int* parseCommand(string command) {
    int* command_parts = new int[3];

    // Get index of first space; return null if not found
    int first_space_i = command.find(" ");
    if (first_space_i == string::npos) {
        return NULL;
    }

    // Repeat for second space
    int second_space_i = command.find(" ", first_space_i + 1);
    if (second_space_i == string::npos) {
        return NULL;
    }
    
    // Check that there is a character after second space, by returning if the space is the last index
    if (command.size() - 1 == second_space_i) {
        return NULL;
    }

    // Get the option and validate it
    char option = command[second_space_i + 1];
    if (option != 'c' && option != 'f') {
        return NULL;
    }
    
    // Attempt to parse command; extract each part using the indexes of spaces
    try {
        command_parts[0] = stoi(command.substr(0, first_space_i));
        command_parts[1] = stoi(command.substr(first_space_i + 1, second_space_i - first_space_i));
        command_parts[2] = (int) command.at(second_space_i + 1); // Last part should be a character
    }
    catch (...) {
        return NULL;
    }

    return command_parts;
}

// Ensures a command has coordinates within the grid, and either a command to flag (f) or check (c)
bool validateCommand(int* command_parts, int grid_size_x, int grid_size_y) {
    return command_parts != NULL && 
                (command_parts[0] > 0 && command_parts[0] <= grid_size_x &&
                command_parts[1] > 0 && command_parts[1] <= grid_size_y &&
                (command_parts[2] == 'f' || command_parts[2] == 'c'));
}
