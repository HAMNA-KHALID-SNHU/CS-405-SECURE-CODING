// Hamna Khalid
// Student ID : 2902671
// hamna.khalid@snhu.edu
// CS-405: Secure Coding
//BS Computer Science : Software Engineering
//Southern New Hampshire University
// 
// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>

using namespace std;

// =========================
// Custom Exception Class
// =========================
class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom exception occurred in application logic.";
    }
};

// =========================
// Function 1
// =========================
bool do_even_more_custom_application_logic()
{
    cout << "Running Even More Custom Application Logic." << endl;

    // Throw a standard exception
    throw runtime_error("Error inside even more custom logic");

    return true;
}

// =========================
// Function 2
// =========================
void do_custom_application_logic()
{
    cout << "Running Custom Application Logic." << endl;

    try
    {
        if (do_even_more_custom_application_logic())
        {
            cout << "Even More Custom Application Logic Succeeded." << endl;
        }
    }
    catch (const std::exception& e)
    {
        // Catch standard exception and continue
        cout << "Caught exception in custom logic: " << e.what() << endl;
    }

    // Throw custom exception
    throw CustomException();

    cout << "Leaving Custom Application Logic." << endl;
}

// =========================
// Division Function
// =========================
float divide(float num, float den)
{
    // Handle divide by zero
    if (den == 0)
    {
        throw invalid_argument("Division by zero error");
    }

    return (num / den);
}

// =========================
// Division Wrapper
// =========================
void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0;

    try
    {
        auto result = divide(numerator, denominator);
        cout << "divide(" << numerator << ", " << denominator << ") = " << result << endl;
    }
    catch (const std::invalid_argument& e)
    {
        // Catch ONLY divide exception
        cout << "Division error: " << e.what() << endl;
    }
}

// =========================
// MAIN FUNCTION
// =========================
int main()
{
    cout << "Exceptions Tests!" << endl;

    try
    {
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomException& e)
    {
        cout << "Custom Exception caught: " << e.what() << endl;
    }
    catch (const std::exception& e)
    {
        cout << "Standard Exception caught: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown exception caught." << endl;
    }

    return 0;
}s