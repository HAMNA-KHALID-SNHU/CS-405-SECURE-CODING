// ======================================================
// Created By: Hamna Khalid
// Student ID: 2902671
// hamna.khalid@snhu.edu
// CS-405: Secure Coding
// BS Computer Science: Software Engineering
// Southern New Hampshire University
// ======================================================


#include <iostream>
#include <limits>
#include <cmath>
#include <type_traits>
#include <typeinfo>

using namespace std;

// ---------------- ADDITION ----------------

template <typename T>
bool add_numbers(T start, T increment, unsigned long steps, T& result)
{
    result = start;

    for (unsigned long i = 0; i < steps; ++i)
    {
        // FLOAT HANDLING
        if (is_floating_point<T>::value)
        {
            T temp = result + increment;

            if (isinf(temp))
            {
                cout << "Overflow detected (float)!" << endl;
                return false;
            }

            if (isnan(temp))
            {
                cout << "Invalid result (NaN)!" << endl;
                return false;
            }

            result = temp;
            continue;
        }

        // SIGNED TYPES
        if (is_signed<T>::value)
        {
            if (increment > 0 && result > numeric_limits<T>::max() - increment)
            {
                cout << "Overflow detected!" << endl;
                return false;
            }

            if (increment < 0 && result < numeric_limits<T>::lowest() - increment)
            {
                cout << "Underflow detected!" << endl;
                return false;
            }
        }
        else
        {
            // UNSIGNED TYPES
            if (result > numeric_limits<T>::max() - increment)
            {
                cout << "Overflow detected!" << endl;
                return false;
            }
        }

        result += increment;
    }

    return true;
}

// ---------------- SUBTRACTION ----------------

template <typename T>
bool subtract_numbers(T start, T decrement, unsigned long steps, T& result)
{
    result = start;

    for (unsigned long i = 0; i < steps; ++i)
    {
        // FLOAT HANDLING
        if (is_floating_point<T>::value)
        {
            T temp = result - decrement;

            if (isinf(temp))
            {
                cout << "Underflow detected (float)!" << endl;
                return false;
            }

            if (isnan(temp))
            {
                cout << "Invalid result (NaN)!" << endl;
                return false;
            }

            result = temp;
            continue;
        }

        // SIGNED TYPES
        if (is_signed<T>::value)
        {
            if (decrement > 0 && result < numeric_limits<T>::lowest() + decrement)
            {
                cout << "Underflow detected!" << endl;
                return false;
            }

            if (decrement < 0 && result > numeric_limits<T>::max() + decrement)
            {
                cout << "Overflow detected!" << endl;
                return false;
            }
        }
        else
        {
            // UNSIGNED TYPES
            if (result < decrement)
            {
                cout << "Underflow detected!" << endl;
                return false;
            }
        }

        result -= decrement;
    }

    return true;
}

// ---------------- TEST FUNCTIONS ----------------

template <typename T>
void test_overflow()
{
    const unsigned long steps = 5;
    const T increment = numeric_limits<T>::max() / steps;
    const T start = 0;

    T result;

    cout << "Overflow Test: " << typeid(T).name() << endl;

    bool status = add_numbers(start, increment, steps, result);
    if (status)
        cout << "\tSafe Result: " << +result << endl;

    status = add_numbers(start, increment, steps + 1, result);

    if (!status)
        cout << "\tOperation stopped due to overflow.\n";
}

// ---------------- UNDERFLOW ----------------

template <typename T>
void test_underflow()
{
    const unsigned long steps = 5;
    const T decrement = numeric_limits<T>::max() / steps;
    const T start = numeric_limits<T>::lowest();

    T result;

    cout << "Underflow Test: " << typeid(T).name() << endl;

    bool status = subtract_numbers(start, decrement, steps, result);
    cout << "\tSafe Result: " << +result << endl;

    status = subtract_numbers(start, decrement, steps + 1, result);

    if (!status)
        cout << "\tOperation stopped due to underflow.\n";
}

// ---------------- MAIN ----------------

int main()
{
    cout << "Starting Numeric Overflow / Underflow Tests!\n\n";

    test_overflow<int>();
    test_underflow<int>();

    test_overflow<long>();
    test_underflow<long>();

    test_overflow<unsigned int>();
    test_underflow<unsigned int>();

    test_overflow<float>();
    test_underflow<float>();

    cout << "\nAll Tests Complete!\n";
    return 0;
}