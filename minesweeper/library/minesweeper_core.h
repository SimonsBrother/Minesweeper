// Constants (only need one ifndef because BLANK will only be defined with the other constants)
#ifndef BLANK

#define BLANK 0
#define MINE 1
#define FLAGGED_MINE 2
#define FLAGGED_BLANK 3

#endif

int** generateGrid(unsigned short grid_size_x, unsigned short grid_size_y, float percentage_mines);
