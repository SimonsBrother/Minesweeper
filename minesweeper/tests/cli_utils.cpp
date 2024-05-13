#include <iostream>
#include "../library/cli_utils.h"

using namespace std;

void runPrintGridTests();
int** generateGrid(int width, int height);
void runCountDigitsTests();
void runParseCommandTests();
void testParseCommand(string test_data, bool expect_null=true);
void runValidateCommandTests();
void testValidateCommand(string command, bool expect_valid);

int main()
{
    //runPrintGridTests();
    //runCountDigitsTests();
    //runParseCommandTests();
    //runValidateCommandTests();
}

void runPrintGridTests() {
    // Even grid
    minefield field;
    field.width = 5;
    field.height = 5;
    field.grid = generateGrid(5, 5);
    field.grid[0] = new int[5]{1, 2, 3, 4, 5};
    field.grid[1] = new int[5]{6, 7, 8, 9, 0};
    field.grid[2] = new int[5]{MINE, BLANK, MINE, BLANK, MINE};
    field.grid[3] = new int[5]{FLAGGED_BLANK, FLAGGED_MINE, 0, 1, 2};
    field.grid[4] = new int[5]{1, 2, 3, 4, 5};

    cout << "\nEven grid showing mines\n";
    cout << "EXPECTED:\n";
    cout << "  1 2 3 4 5\n";
    cout << "1 1 6 x f 1\n";
    cout << "2 2 7 . X 2\n";
    cout << "3 3 8 x 0 3\n";
    cout << "4 4 9 . 1 4\n";
    cout << "5 5 0 x 2 5\n";

    cout << "\nOUTPUT=============\n";
    printGrid(field, true);

    cout << "\nEven grid hiding mines\n";
    cout << "EXPECTED:\n";
    cout << "  1 2 3 4 5\n";
    cout << "1 1 6 ? f 1\n";
    cout << "2 2 7 ? f 2\n";
    cout << "3 3 8 ? 0 3\n";
    cout << "4 4 9 ? 1 4\n";
    cout << "5 5 0 ? 2 5\n";

    cout << "\nOUTPUT=============\n";
    printGrid(field, false);


    cout << "\nTall grid\n";
    field.width = 2;
    field.height = 4;
    field.grid = generateGrid(2, 4);
    field.grid[0] = new int[4]{1, 2, 3, 4};
    field.grid[1] = new int[4]{5, 6, 7, 8};

    cout << "EXPECTED:\n";
    cout << "  1 2\n";
    cout << "1 1 5\n";
    cout << "2 2 6\n";
    cout << "3 3 7\n";
    cout << "4 4 8\n";

    cout << "\nOUTPUT=============\n";
    printGrid(field, true);


    cout << "\nWide grid\n";
    field.width = 5;
    field.height = 2;
    field.grid = generateGrid(5, 2);
    field.grid[0] = new int[2]{1, 2};
    field.grid[1] = new int[2]{3, 4};
    field.grid[2] = new int[2]{5, 6};
    field.grid[3] = new int[2]{7, 8};
    field.grid[4] = new int[2]{9, 0};

    cout << "EXPECTED:\n";
    cout << "  1 2 3 4 5\n";
    cout << "1 1 3 5 7 9\n";
    cout << "2 2 4 6 8 0\n";

    cout << "\nOUTPUT=============\n";
    printGrid(field, true);


    // Large grid
    cout << "\nLarge grid\n";
    field.width = 10;
    field.height = 10;
    field.grid = generateGrid(10, 10);
    field.grid[0] = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    field.grid[1] = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    field.grid[2] = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    field.grid[3] = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    field.grid[4] = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    field.grid[5] = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    field.grid[6] = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    field.grid[7] = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    field.grid[8] = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    field.grid[9] = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    // Showing mines
    cout << "EXPECTED:\n";
    cout << "    1  2  3  4  5  6  7  8  9 10\n";
    cout << " 1  1  1  1  1  1  1  1  1  1  1\n";
    cout << " 2  2  2  2  2  2  2  2  2  2  2...\n";
    cout << "10  0  0  0  0  0  0  0  0  0  0\n";

    cout << "\nOUTPUT=============\n";
    printGrid(field, true);
}

// Generates a 2D array "grid"
int** generateGrid(int width, int height) {
    // Generate 2D array to represent the grid
    int** grid = new int*[width];
    
    // For each column, generate grid_size_y rows
    for (int x = 0; x < width; x++) {
        grid[x] = new int[height];
    }
    
    return grid;
}

void runCountDigitsTests() {
    cout << "Testing count digits\n--------------------------------\n";
    // Valid usage
    cout << countDigits(5) << " (expect 1) \n";
    cout << countDigits(10) << " (expect 2) \n";
    cout << countDigits(999) << " (expect 3) \n";
    cout << countDigits(5000) << " (expect 4) \n";
    // Questionable but not invalid numbers
    cout << countDigits(-5) << " (expect 1) \n";
    cout << countDigits(-99) << " (expect 2) \n";
    cout << countDigits(0) << " (expect 1) \n";
}

void runParseCommandTests() {
    cout << "Testing parse command\n--------------------------------\n";
    // Parse valid usage
    testParseCommand("1 2 f", false);
    testParseCommand("10 22 c", false);
    testParseCommand("1 25 c", false);
    testParseCommand("10 2 c", false);
    testParseCommand("1 500 c", false);
    // Parse invalid usage
    testParseCommand("1 2 ");
    testParseCommand("1 2");
    testParseCommand("1 2f");
    testParseCommand(" ");
    testParseCommand("  ");
    testParseCommand("a 1 f");
    testParseCommand("1 a f");
    testParseCommand("1 1 a");
    testParseCommand("1 1 aa");
    testParseCommand("1 500 5");
    testParseCommand("1 500 52");
}

// Helper function for testing parseCommand
void testParseCommand(string test_data, bool expect_null) {
    int* result = parseCommand(test_data);
    cout << "Test data " << test_data << ": ";
    if (expect_null) {
        cout << result << " (expect null)\n";
    }
    else {
        cout << result[0] << ' ' << result[1] << ' ' << (char)result[2] << " (expect " << test_data << ")\n";
    }

    delete result;
}

void runValidateCommandTests() {
    cout << "Testing validate command\n--------------------------------\n";
    
    // Test valid use
    testValidateCommand("3 3 f", true);
    testValidateCommand("2 4 f", true);

    // Test valid coordinate boundaries
    testValidateCommand("1 5 c", true);
    testValidateCommand("5 1 c", true);
    testValidateCommand("1 1 c", true);
    testValidateCommand("5 5 c", true);

    // Test lower than coordinate bounds
    testValidateCommand("0 1 c", false);
    testValidateCommand("1 0 c", false);
    testValidateCommand("0 0 c", false);

    // Test greater than coordinate bounds
    testValidateCommand("6 1 c", false);
    testValidateCommand("1 6 c", false);
    testValidateCommand("6 6 c", false);

    // Test invalid action
    testValidateCommand("3 5 a", false);
    testValidateCommand("3 4 b", false);
}

// Helper function for testing validateCommand
void testValidateCommand(string command, bool expect_valid) {
    cout << command << ": " << validateCommand(parseCommand(command), 5, 5) << " (expect " << expect_valid << ")\n";
}
