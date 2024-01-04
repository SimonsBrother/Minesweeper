#ifndef CLI_UTILS
#define CLI_UTILS
#include <string>

int countDigits(int number);
void printGrid(int** grid, unsigned short grid_size_x, unsigned short grid_size_y, bool reveal_mines);
void printChar(char ch, unsigned int count);
std::string getCommandFromUser();
int* parseCommand(std::string command);
bool validateCommand(int* command_parts, unsigned short grid_size_x, unsigned short grid_size_y);

#endif