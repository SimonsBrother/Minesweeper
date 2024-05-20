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

    // The starting coorinates are important for adding mines, as mines should not be at the starting square.
    // The reason this is in the minefield structure is to minimise the need for parameters.
    int starting_x;
    int starting_y;
};

minefield generateMinefield(int width, int height, float percentage, int starting_x, int starting_y);
int** generateBlankGrid(int width, int height);
void addPercentageOfMines(minefield& field, float percentage);
void addMinesToGrid(minefield& field, int num_mines);
void addFlag(minefield field, int x, int y);
bool checkSquare(minefield& field, int x, int y);
int countSurroundingMines(minefield& field, int x, int y);
bool isSquareValid(minefield& field, int x, int y);
bool isSquareMine(int square_value);
void deleteGrid(minefield& field);

#endif
