// ============================================================
// CS-405 Secure Coding
// Module Five - Encryption Activity
// XOR Encryption Implementation
//
// Submitted By: HAMNA KHALID
// Student ID: 2902671
// Email: hamna.khalid@snhu.edu
// Course: CS-405 Secure Coding
// Southern New Hampshire University
// ============================================================

// Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

/// <summary>
/// Encrypt or decrypt a source string using XOR and a key
/// </summary>
std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
    const auto key_length = key.length();
    const auto source_length = source.length();

    // Ensure valid input
    assert(key_length > 0);
    assert(source_length > 0);

    std::string output = source;

    // XOR each character with repeating key
    for (size_t i = 0; i < source_length; ++i)
    {
        output[i] = source[i] ^ key[i % key_length]; // XOR logic
    }

    assert(output.length() == source_length);

    return output;
}

/// <summary>
/// Read entire file into a string
/// </summary>
std::string read_file(const std::string& filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;

    if (file)
    {
        buffer << file.rdbuf(); // Read full file
    }
    else
    {
        std::cout << "Error opening file: " << filename << std::endl;
    }

    return buffer.str();
}

/// <summary>
/// Extract student name (first line)
/// </summary>
std::string get_student_name(const std::string& string_data)
{
    std::string student_name;

    size_t pos = string_data.find('\n');
    if (pos != std::string::npos)
    {
        student_name = string_data.substr(0, pos);
    }

    return student_name;
}

/// <summary>
/// Save data to file in required format
/// </summary>
void save_data_file(const std::string& filename, const std::string& student_name, const std::string& key, const std::string& data)
{
    std::ofstream file(filename);

    if (file)
    {
        // Get current date
        std::time_t now = std::time(nullptr);
        std::tm* local_time = std::localtime(&now);

        // Required format
        file << student_name << "\n";                                // Line 1
        file << std::put_time(local_time, "%Y-%m-%d") << "\n";        // Line 2
        file << key << "\n";                                         // Line 3
        file << data;                                                // Line 4+
    }
    else
    {
        std::cout << "Error saving file: " << filename << std::endl;
    }
}

int main()
{
    std::cout << "Encryption Decryption Test!" << std::endl;

    const std::string file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrytpteddatafile.txt";

    const std::string source_string = read_file(file_name);
    const std::string key = "password";

    // Extract student name from file
    const std::string student_name = get_student_name(source_string);

    // Encrypt data
    const std::string encrypted_string = encrypt_decrypt(source_string, key);

    // Save encrypted file
    save_data_file(encrypted_file_name, student_name, key, encrypted_string);

    // Decrypt data
    const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);

    // Save decrypted file
    save_data_file(decrypted_file_name, student_name, key, decrypted_string);

    std::cout << "Read File: " << file_name
        << " - Encrypted To: " << encrypted_file_name
        << " - Decrypted To: " << decrypted_file_name << std::endl;

    return 0;
}
 // students submit input file, encrypted file, decrypted file, source code file, and key used
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu