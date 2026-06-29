// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <string>

    // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
    //  even though it is a constant and the compiler buffer overflow checks are on.
    //  You need to modify this method to prevent buffer overflow without changing the account_number
    //  variable, and its position in the declaration. It must always be directly before the variable used for input.
    //  You must notify the user if they entered too much data.


// Function to detect buffer overflow
    bool isOverflow(const std::string & input, size_t bufferSize) {
        return input.length() >= bufferSize;
    }

    // Function to safely handle input
    bool handleInput(char* buffer, size_t bufferSize) {

        std::string input;
        std::cin >> input;

        // Detect overflow BEFORE copying
        if (isOverflow(input, bufferSize)) {
            std::cout << "Buffer Overflow Detected! Input Too Large." << std::endl;
            return false; // notify caller
        }

        // Safe copy
        strncpy(buffer, input.c_str(), bufferSize - 1);
        buffer[bufferSize - 1] = '\0';

        return true;
    }

    int main()
    {
        std::cout << "Buffer Overflow Example" << std::endl;

        const std::string account_number = "CharlieBrown42";
        char user_input[20];

        std::cout << "Enter a value: ";

        // Call safe function
        if (!handleInput(user_input, sizeof(user_input))) {
            return 0;
        }

        std::cout << "You entered: " << user_input << std::endl;
        std::cout << "Account Number = " << account_number << std::endl;

        return 0;
    }
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu