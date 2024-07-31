#ifndef CLI_UTILS
#define CLI_UTILS

#include <string>
#include "minesweeper_core.h"

int countDigits(int number);
void printGrid(minefield field, bool reveal_mines, bool use_square_for_blanks = false);
void printGridHeader(minefield field, int grid_size_x_digit_count, int grid_size_y_digit_count);
void printGridSquare(int square_value, bool show_mines, bool use_square_for_blanks);
void printChar(char ch, unsigned int count);
std::string getCommandFromUser();
vector<int> parseCommand(std::string command);
bool validateCommand(int* command_parts, int grid_size_x, int grid_size_y);

#endif