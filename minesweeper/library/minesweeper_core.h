// Constants (only need one ifndef because BLANK will only be defined with the other constants)
#ifndef MINESWEEPER_CORE
#define MINESWEEPER_CORE

#define BLANK -1
#define MINE -2
#define FLAGGED_MINE -3
#define FLAGGED_BLANK -4

struct minefield {
    int width;
    int height;
    int** grid;
};

minefield generateMinefield(int width, int height, float percentage);
int** generateGrid(int width, int height);
void addPercentageOfMines(minefield& field, float percentage);
void addMinesToGrid(minefield& field, int num_mines);
void addFlag(int** grid, int x, int y);
void checkSquare(minefield& field, int x, int y);
int countMines(minefield& field, int x, int y);
bool isSquareMine(int square_value);
void deleteGrid(minefield& field);

#endif
