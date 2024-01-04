#include <iostream>
#include "../library/cli_utils.h"

using namespace std;

void testCountDigits();
void parseCommandTests();
void testParseCommand(string test_data, bool expect_null=true);
void validateCommandTests();
void testValidateCommand(string command, bool expect_valid);

int main()
{
    //testCountDigits();
    //parseCommandTests();
    validateCommandTests();
}

void testCountDigits() {
    cout << "Testing count digits\n--------------------------------\n";
    cout << countDigits(5) << " (expect 1) \n";
    cout << countDigits(-5) << " (expect 1) \n";
    cout << countDigits(10) << " (expect 2) \n";
    cout << countDigits(255) << " (expect 3) \n";
    cout << countDigits(5000) << " (expect 4) \n";
    cout << countDigits(0) << " (expect 1) \n";
}

void parseCommandTests() {
    cout << "Testing parse command\n--------------------------------\n";
    
    testParseCommand("1 2 f", false);
    testParseCommand("10 22 c", false);
    testParseCommand("1 25 c", false);
    testParseCommand("10 2 c", false);
    testParseCommand("1 500 c", false);

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

void validateCommandTests() {
    cout << "Testing validate command\n--------------------------------\n";
    
    testValidateCommand("1, 1, f", true);

    testValidateCommand("1, 5, c", true);
    testValidateCommand("5, 1, c", true);

    testValidateCommand("0, 1, c", false);
    testValidateCommand("1, 0, c", false);

    testValidateCommand("6, 1, c", false);
    testValidateCommand("1, 6, c", false);

    testValidateCommand("1, 1, a", false);
    testValidateCommand("1, 1, b", false);
}

void testValidateCommand(string command, bool expect_valid) {
    cout << command << ": " << validateCommand(parseCommand(command), 5, 5) << " expect " << expect_valid << "\n";
}
