#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

int get_input()
{
    int input;
    cout << "Enter your gusses, between 1 and 100 : " << endl;
    while (!(cin >> input) || input < 1 || input > 100)
    {
        cout << "Invalid input: " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}

int generate_num()
{
    int num;
    srand(time(0));
    num = rand() % 100 + 1;
    return num;
}

void main_logic()
{
    int num, input, steps = 0;

    num = generate_num();
    cout << num << endl;
    do
    {
        input = get_input();
        if (num == input)
        {
            cout << "You get the correct number! :)" << endl;
            return;
        }
        else if (num < input)
        {
            cout << "Your number is bigger than than it(:" << endl;
        }
        else
        {
            cout << "Your number is less than the number(:" << endl;
        }
        ++steps;
    } while (steps < 4);

    cout << "No! You loose, try again!" << endl;
}

int main()
{
    main_logic();
    return 0;
}