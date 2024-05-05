#ifndef CLI_UTILS
#define CLI_UTILS

#include <string>
#include "minesweeper_core.h"

int countDigits(int number);
void printGrid(minefield field, bool reveal_mines);
void printChar(char ch, unsigned int count);
std::string getCommandFromUser();
int* parseCommand(std::string command);
bool validateCommand(int* command_parts, int grid_size_x, int grid_size_y);

#endif