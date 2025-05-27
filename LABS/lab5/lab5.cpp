#include <iostream>

using namespace std;

const int MAX_ADDRESS_LENGTH = 20;

// This function checks if all characters in the string are valid (0-9 and dot).
//
// Input:
//  - address: a string to be validated.
//  - index: the index of the character to check.
// Output:
//  - true if all characters starting from the string index are valid (0-9 and dot), false otherwise.
//
// TODO 1
bool validCharacters(const char address[], int index)
{
    // ** Your TODO: Implement this function. **
    if (address[index] == '\0')
    {
        return true;
    }
    if ((address[index] < '0' || address[index] > '9') && address[index] != '.')
    {
        return false;
    }

    return validCharacters(address, index + 1);
}

// Function to check whether all numbers of the address are valid.
//
// Input:
// - address: the string containing numbers to be validated.
// - index: the current index in the string.
// - result: the accumulated result of the current number calculation.
//
// Functionality:
// 1. Checks whether the current character is a non-digit character.
//      - If it is a non-digit character, check the accumulated result.
// 2. Converts the current character to its corresponding digit.
// 3. Updates the result.
// 4. Recursively calls itself with the new index and result.
//
// Output:
// - true if all numbers in the string are valid (0-255), false otherwise.
//
// TODO 2
bool validNumber(const char address[], int index, int result)
{
    if (address[index] == '\0')
    {
        return result >= 0 && result <= 255;
    }

    if (address[index] == '.')
    {
        if (result < 0 || result > 255)
        {
            return false;
        }
        return validNumber(address , index + 1 , 0);
    }

    if (address[index] < '0' || address[index] > '9')
    {
        return false;
    }
    result = result * 10 + (static_cast<int>(address[index] - static_cast<int>('0')));
    if (result > 255)
    {
        return false;
    }
    return validNumber(address , index + 1 , result);
}

// Function to check whether the dot usage of the address is valid.
//
// Input:
// - address: the string using dots to be validated.
// - index: the current index in the string.
// - dotCount: the number of dots encountered so far.
//
// Functionality:
// 1. Checks if dotCount is equal to 3 when it reaches the end of the string.
//      - If dotCount is not equal to 3, return false.
// 2. Checks if the current character is a dot.
//      - If it is a dot, ensure it is not a leading dot, consecutive dot, or trailing dot, otherwise return false.
//
// Output:
// - true if the dot usage in the string is valid, false otherwise.
//
// TODO 3
bool validDotUsage(const char address[], int index, int dotCount)
{
    // ** Your TODO: Implement this function. **
    if (address[index] == '\0')
    {
        return (dotCount == 3);
    }

    if (address[index] == '.')
    {
        if (index == 0 || address[index + 1] == '.' || address[index + 1] == '\0')
        {
            return false;
        }
        dotCount++;
        return validDotUsage(address , index + 1 , dotCount);
    }
    return validDotUsage(address, index + 1, dotCount);
}

// Function to check whethre a IPv4 address is valid.
//
// Input:
// - address: the string containing the IPv4 address to be validated.
//
// Output:
// - Returns true if the IPv4 address is valid, otherwise returns false.
bool isValidIPv4(const char address[])
{
    return validCharacters(address, 0) && validNumber(address, 0, 0) && validDotUsage(address, 0, 0);
}

// Function to check if an address matches the given address.
//
// Input:
// - storedAddress: the string containing the stored address to match against.
// - address: the string containing the address to be checked.
// - index: the current index in the strings (default is 0).
//
// Functionality:
// 1. Checks if the end of both strings is reached (base case).
//      - If both strings end at the same time, return true.
// 2. Checks if the characters at the current index do not match.
//      - If the characters do not match, return false.
// 3. Recursively calls itself with the next index to check the next character.
//
// Output:
// - Returns true if the two addresses match, otherwise returns false.
//
// TODO 4
bool matchAddress(const char storedAddress[], const char address[], int index)
{
    // ** Your TODO: Implement this function. **
    if (storedAddress[index] == '\0' && address[index] == '\0')
    {
        return true;
    }

    if (storedAddress[index] != address[index])
    {
        return false;
    }
    return matchAddress(storedAddress, address, index + 1);
}

// Main function.
// Note: do not modify this function.
int main()
{
    int choice;
    char address1[MAX_ADDRESS_LENGTH];
    char address2[MAX_ADDRESS_LENGTH];

    cout << "Enter the first IPv4 address: ";
    cin.getline(address1, MAX_ADDRESS_LENGTH);
    cout << "Enter the second IPv4 address: ";
    cin.getline(address2, MAX_ADDRESS_LENGTH);

    // For case 2 of the following switch statement
    int index_1, index_2;

    while (true)
    {
        cout << "Enter which function to test (0: exit, 1: isValidCharacters, 2: isValidNumber, 3: isValidDotUsage, 4: matchAddress): ";
        cin >> choice;
        cout << endl;
        cin.ignore(); // Ignore newline character after choice input
        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
            if (validCharacters(address1, 0))
            {
                cout << "The characters of first address are all valid." << endl;
            }
            else
            {
                cout << "The first address contains invalid characters." << endl;
            }
            if (validCharacters(address2, 0))
            {
                cout << "The characters of second address are all valid." << endl;
            }
            else
            {
                cout << "The second address contains invalid characters." << endl;
            }
            break;
        case 2:
            if (validNumber(address1, 0, 0))
            {
                cout << "The numbers of first address are all valid." << endl;
            }
            else
            {
                cout << "The first address contains invalid numbers." << endl;
            }
            if (validNumber(address2, 0, 0))
            {
                cout << "The numbers of second address are all valid." << endl;
            }
            else
            {
                cout << "The second address contains invalid numbers." << endl;
            }
            break;
        case 3:
            if (validDotUsage(address1, 0, 0))
            {
                cout << "The dot usage of first address is valid." << endl;
            }
            else
            {
                cout << "The dot usage of first address is invalid." << endl;
            }
            if (validDotUsage(address2, 0, 0))
            {
                cout << "The dot usage of second address is valid." << endl;
            }
            else
            {
                cout << "The dot usage of second address is invalid." << endl;
            }
            break;
        case 4:
            if (isValidIPv4(address1) && isValidIPv4(address2))
            {
                if (matchAddress(address1, address2, 0))
                {
                    cout << "The two addresses match." << endl;
                }
                else
                {
                    cout << "The two addresses do not match." << endl;
                }
            }
            else
            {
                cout << "There are invalid addresses." << endl;
            }
            break;
        default:
            cout << "Invalid function selected." << endl;
        }
        cout << endl;
    }

    return 0;
}
