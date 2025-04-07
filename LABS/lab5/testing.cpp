#include <iostream>
using namespace std;

bool validCharacters(const char address[], int index)
{
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

bool validNumber(const char address[], int index, int result)
{
    if (address[index] == '\0' || address[index] == '.')
    {
        return result >= 0 && result <= 255;
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

bool validDotUsage(const char address[], int index, int dotCount)
{
    // ** Your TODO: Implement this function. **
    if (address[index] == '\0' && dotCount == 3)
    {
        return true;
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

bool isValidIPv4(const char address[])
{
    return validCharacters(address, 0) && validNumber(address, 0, 0) && validDotUsage(address, 0, 0);
}

bool matchAddress(const char storedAddress[], const char address[], int index)
{
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

const int MAX_ADDRESS_LENGTH = 20;

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



