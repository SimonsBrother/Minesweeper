#include "../library/minesweeper_core.h"
#include <iostream>

using namespace std;
void runGenerateMinefieldTests();
void testInvalidGenerateMinefield(int width, int height, float percentage, int starting_x, int starting_y);
void testGenerateMinefield(int width, int height, float percentage, int starting_x, int starting_y);
int countMines(minefield field);
void runAddFlagTests();
void testValidAddFlag(minefield field, int x, int y);
void testInvalidAddFlag(minefield field, int x, int y);
void runCountSurroundingMinesTests();
void testCountSurroundingMines(minefield field, int x, int y, int expected_count);
void setGridForCheckSquareTests(int** grid);
void runCheckSquareTests();

int main(int argc, char** argv) {
    cout << "generateMinefield tests\n";
    runGenerateMinefieldTests();
    cout << "\n\naddFlag tests\n";
    runAddFlagTests();
    cout << "\n\ncountSurroundingMines tests\n";
    runCountSurroundingMinesTests();

    runCheckSquareTests();
}

// Tests generateMinefield and indirectly tests generateBlankGrid, addPercentageOfMines, addMinesToGrid
void runGenerateMinefieldTests() {
    minefield field;

    // Valid tests
    // Test valid sizes
    testGenerateMinefield(10, 10, 50, 4, 4);
    testGenerateMinefield(500, 10, 50, 4, 4);
    testGenerateMinefield(10, 500, 50, 4, 4);
    testGenerateMinefield(2, 2, 50, 0, 0);
    testGenerateMinefield(1, 20, 50, 0, 0);
    testGenerateMinefield(20, 1, 50, 0, 0);

    // Test valid percentages of mines
    testGenerateMinefield(10, 10, 99, 4, 4);
    testGenerateMinefield(10, 10, 1, 4, 4);
    testGenerateMinefield(10, 10, 50, 4, 4);

    // Test valid starting square
    testGenerateMinefield(10, 10, 10, 0, 0);
    testGenerateMinefield(10, 10, 10, 9, 0);
    testGenerateMinefield(10, 10, 10, 0, 9);
    testGenerateMinefield(10, 10, 10, 9, 9);

    // Erroneous tests
    // Invalid width
    testInvalidGenerateMinefield(0, 5, 5, 0, 3);
    testInvalidGenerateMinefield(-1, 5, 5, 0, 3);

    // Invalid height
    testInvalidGenerateMinefield(5, 0, 5, 3, 0);
    testInvalidGenerateMinefield(5, -1, 5, 3, 0);

    // Invalid percentage
    testInvalidGenerateMinefield(10, 10, 0, 4, 4);
    testInvalidGenerateMinefield(10, 10, -1, 4, 4);
    testInvalidGenerateMinefield(10, 10, 100, 4, 4);
    testInvalidGenerateMinefield(10, 10, 101, 4, 4);

    // Invalid starting coordinates
    testInvalidGenerateMinefield(10, 10, 10, -1, 4); // Minimum below min coordinates
    testInvalidGenerateMinefield(10, 10, 10, 4, -1);
    testInvalidGenerateMinefield(10, 10, 10, -1, -1);
    testInvalidGenerateMinefield(10, 10, 10, 10, 4); // Minimum above max coordinates
    testInvalidGenerateMinefield(10, 10, 10, 4, 10);
    testInvalidGenerateMinefield(10, 10, 10, 10, 10);
}

// Attempts to generate a minefield, expecting it to fail. Prints whether an error was raised and the params used.
void testInvalidGenerateMinefield(int width, int height, float percentage, int starting_x, int starting_y) {
    try {
        minefield field = generateMinefield(width, height, percentage, starting_x, starting_y);
        printf("FAIL: exception expected, for width %i height %i percentage %f starting_x %i starting_y %i\n", width, height, percentage, starting_x, starting_y);
    }
    catch (char const* exception) {
        printf("PASS: Caught exception as expected (%s), for width %i height %i percentage %f starting_x %i starting_y %i\n", exception, width, height, percentage, starting_x, starting_y);
    }
}

// Generates a minefield, and checks it has the right number of mines, that each cell is accessible, and that the starting coordinates aren't a mine.
void testGenerateMinefield(int width, int height, float percentage, int starting_x, int starting_y) {
    minefield field = generateMinefield(width, height, percentage, starting_x, starting_y);
    
    // Test correct mine count
    int expected_mines_count = round(width * height * (percentage/100));
    bool correct_mine_count = countMines(field) == expected_mines_count;

    // Test starting cell is blank
    bool starting_blank = field.grid[starting_x][starting_y] == BLANK;

    // Results
    if (correct_mine_count && starting_blank) {
        printf("PASS: width %i height %i percentage %f starting_x %i starting_y %i\n", width, height, percentage, starting_x, starting_y);
    }
    else {
        printf("FAIL, mine count: %s, starting blank: %s - width %i height %i percentage %f starting_x %i starting_y %i\n", 
               correct_mine_count ? "true" : "false", starting_blank ? "true" : "false", width, height, percentage, starting_x, starting_y);
    }
}

// Counts the number of mines in the minefield, and also implicitly tests each cell of the grid can be accessed.
int countMines(minefield field) {
    int count = 0;
    for (int x = 0; x < field.width; x++)
    {
        for (int y = 0; y < field.height; y++)
        {
            if (field.grid[x][y] == MINE) {
                count++;
            }
        }
    }
    return count;
}

// Tests addFlag and indirectly tests isSquareValid
void runAddFlagTests() {
    // Test valid use
    minefield field = generateMinefield(10, 10, 50, 4, 4);
    int** grid = field.grid;
    grid[2][2] = MINE;
    grid[2][3] = BLANK;

    // Flagging mine and blank
    addFlag(field, 2, 2);
    addFlag(field, 2, 3);
    if (grid[2][2] == FLAGGED_MINE && grid[2][3] == FLAGGED_BLANK) {
        cout << "Correctly flagged mine and blank.\n";
    }

    // Unflagging
    addFlag(field, 2, 2);
    addFlag(field, 2, 3);
    if (grid[2][2] == MINE && grid[2][3] == BLANK) {
        cout << "Correctly unflagged flagged mine and flagged blank.\n";
    }

    // Test corners
    testValidAddFlag(field, 2, 0); // Lower bound of coordinates
    testValidAddFlag(field, 0, 2);
    testValidAddFlag(field, 0, 0);
    testValidAddFlag(field, 9, 0); // Upper bound of coordinates
    testValidAddFlag(field, 0, 9);
    testValidAddFlag(field, 9, 9);

    // Invalid usage
    testInvalidAddFlag(field, -1, 4); // Lower bound of coordinates
    testInvalidAddFlag(field, 4, -1);
    testInvalidAddFlag(field, -1, -1);
    testInvalidAddFlag(field, 10, 4); // Upper bound of coordinates
    testInvalidAddFlag(field, 4, 10); // Upper bound of coordinates
    testInvalidAddFlag(field, 10, 10); // Upper bound of coordinates
}

// Adds a flag. Prints whether an error was raised and the params used.
void testValidAddFlag(minefield field, int x, int y) {
    try {
        addFlag(field, x, y);
        printf("PASS for x %i y %i\n", x, y);
    }
    catch (char const* exception) {
        printf("FAIL: %s, for x %i y %i\n", exception, x, y);
    }
}

// Attempts to add a flag, expecting it to fail. Prints whether an error was raised and the params used.
void testInvalidAddFlag(minefield field, int x, int y) {
    try {
        addFlag(field, x, y);
        printf("FAIL: exception expected, for x %i y %i\n", x, y);
    }
    catch (char const* exception) {
        printf("PASS: Caught exception as expected (%s), for x %i y %i\n", exception, x, y);
    }
}

// Tests countSurroundingMines and indirectly tests isSquareValid (again) and also isSquareMine
void runCountSurroundingMinesTests() {
    minefield field = generateMinefield(6, 6, 1, 1, 1);
    field.grid[0] = new int[6]{MINE, MINE, MINE, BLANK, BLANK, BLANK};  // xxx...
    field.grid[1] = new int[6]{MINE, BLANK, MINE, BLANK, BLANK, BLANK}; // x.x...
    field.grid[2] = new int[6]{MINE, MINE, MINE, BLANK, BLANK, BLANK};  // xxx...
    field.grid[3] = new int[6]{FLAGGED_MINE, FLAGGED_MINE, FLAGGED_MINE, FLAGGED_BLANK, FLAGGED_BLANK, FLAGGED_BLANK}; // Repeated pattern but flagged versions
    field.grid[4] = new int[6]{FLAGGED_MINE, FLAGGED_BLANK, FLAGGED_MINE, FLAGGED_BLANK, FLAGGED_BLANK, FLAGGED_BLANK};
    field.grid[5] = new int[6]{FLAGGED_MINE, FLAGGED_MINE, FLAGGED_MINE, FLAGGED_BLANK, FLAGGED_BLANK, FLAGGED_BLANK};

    // Test some mines
    testCountSurroundingMines(field, 1, 3, 3);
    
    // Test no mines
    testCountSurroundingMines(field, 1, 4, 0);

    // Test max mines
    testCountSurroundingMines(field, 1, 1, 8);

    // Some flagged some blank
    testCountSurroundingMines(field, 2, 4, 0);

    // Some flagged mines, some mines, some flagged blank, some blank
    testCountSurroundingMines(field, 2, 3, 3);

    // Test corners
    testCountSurroundingMines(field, 0, 0, 2);
    testCountSurroundingMines(field, 5, 0, 2);
    testCountSurroundingMines(field, 0, 5, 0);
    testCountSurroundingMines(field, 5, 5, 0);
}

void testCountSurroundingMines(minefield field, int x, int y, int expected_count) {
    int actual_count = countSurroundingMines(field, x, y);
    if (actual_count == expected_count) {
        printf("PASS - x: %i, y: %i - EXPECTED: %i\n", x, y, expected_count);
    }
    else {
        printf("FAIL - x: %i, y: %i - EXPECTED: %i, ACTUAL: %i\n", x, y, expected_count, actual_count);
    }
}

// Tests checkSquare
void runCheckSquareTests() {
    minefield field = generateMinefield(6, 6, 1, 1, 1);

    // Check correctly identified unsafe
    setGridForCheckSquareTests(field.grid);

    // Check correctly identified safe

    // Test recursively checks correctly (adjacent 0-nearby-mines squares are auto checked)
    // Check single square

    // Check large even area, which is also a cornered area

    // Check large uneven area

    // Test checking already checked square does nothing

}

void setGridForCheckSquareTests(int** grid) {
    grid = new int*[6]{new int[6]{BLANK, MINE, MINE, MINE, BLANK, BLANK},
                       new int[6]{BLANK, MINE, BLANK, MINE, MINE, MINE},
                       new int[6]{BLANK, MINE, MINE, MINE, BLANK, MINE},
                       new int[6]{BLANK, MINE, BLANK, MINE, BLANK, MINE},
                       new int[6]{BLANK, MINE, BLANK, BLANK, BLANK, MINE},
                       new int[6]{BLANK, MINE, MINE, MINE, MINE, MINE}};
}
