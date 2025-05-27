#include <iostream>
#include <cassert>
using namespace std;

bool validCharacters(const char address[], int index);
bool validNumber(const char address[], int index, int result);


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

bool validNumber(const char address[], int index, int result)
{
    // ** Your TODO: Implement this function. **
    if (address[index] == '\0')
    {
        return true;
    }
    if (address[index] == '.')
    {
        return validNumber(address, index + 1, result);
    }
    else
    {
        result = static_cast<int>(address[index]) - static_cast<int>('0');
        if (result < 0 || result > 255)
        {
            return false;
        }
        else
        {
            return validNumber(address, index + 1, result);
        }
    }
}


void test_validCharacters() {
    assert(validCharacters("192.168.1.1", 0) == true);
    assert(validCharacters("255.255.255.255", 0) == true);
    assert(validCharacters("192.168.1.a", 0) == false);
    assert(validCharacters("192.168.1.256", 0) == true); // validCharacters only checks for valid characters, not range
    assert(validCharacters("", 0) == true);
    assert(validCharacters("192.168.1.1.1", 0) == true);
}

void test_validNumber() {
    assert(validNumber("192.168.1.1", 0, 0) == true);
    assert(validNumber("255.255.255.255", 0, 0) == true);
    assert(validNumber("192.168.1.256", 0, 0) == false);
    assert(validNumber("0.0.0.0", 0, 0) == true);
    assert(validNumber("192.168.1.-1", 0, 0) == false);
}

int main() {
    test_validCharacters();
    test_validNumber();
    cout << "All tests passed!" << endl;
    return 0;
}