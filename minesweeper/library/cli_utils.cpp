#include "cli_utils.h"
#include <iostream>

using namespace std;

// Displays the grid
void printGrid(int** grid, unsigned short grid_size_x, unsigned short grid_size_y, bool reveal_mines) {
    unsigned short grid_size_x_digit_count = countDigits(grid_size_x);
    unsigned short grid_size_y_digit_count = countDigits(grid_size_y);
    
    // Print numbered header
    printChar(' ', grid_size_y_digit_count);
    cout << ' '; // Gap
    for (int i = 1; i <= grid_size_x; i++)
    {
        printChar(' ', grid_size_x_digit_count - countDigits(i));
        cout << i << ' '; // Print number and a gap
    }
    cout << '\n';

    // Print rows
    for (int y = 1; y <= grid_size_y; y++)
    {
        // Print row number
        printChar(' ', grid_size_y_digit_count - countDigits(y));
        cout << y;
        
        // Print each square
        for (int x = 0; x < grid_size_x; x++)
        {
            // Spacing
            printChar(' ', grid_size_x_digit_count);
            if (grid[x][y] == 1) {
                cout << 'x';
            }
            else {
                cout << "\u25A0";
            }
        }
        cout << '\n';
    }
}

// Calculates how many decimal digits are needed for the number provided
int countDigits(int number) {
    // Handle corner case that doesn't work with the method below
    if (number == 0) {
        return 1;
    }

    // Integer division by 10 as many times as needed to get number to 0
    unsigned short count = 0;
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
bool validateCommand(int* command_parts, unsigned short grid_size_x, unsigned short grid_size_y) {
    return command_parts != NULL && 
                (command_parts[0] > 0 && command_parts[0] <= grid_size_x &&
                command_parts[1] > 0 && command_parts[1] <= grid_size_y &&
                (command_parts[2] == 'f' || command_parts[2] == 'c'));
}
