#include <iostream>

#include "parenthesizer.cpp"

using std::cout;
using std::endl;

void test_parenthesize(const char expression[], const char expected[])
{
    char parenthesized[MAX_LEN];
    parenthesize(expression, parenthesized);
    cout << "parenthesize(\"" << expression << "\") = " << parenthesized << endl;
    if (strcmp(parenthesized, expected) == 0)
    {
        cout << "  => OK" << endl;
    }
    else
    {
        cout << "  => FAIL; expected: " << expected << endl;
    }
}

int main()
{
    // addition & multiplication
    test_parenthesize("2 + 3 * 4", "(2 + (3 * 4))");

    // power (right associative)
    test_parenthesize("2 ^ 3 ^ 2", "(2 ^ (3 ^ 2))");

    // unary & constants
    test_parenthesize("e + sqrt pi", "(e + (sqrt pi))");

    // You should add more test cases.
    test_parenthesize("2 + 3 * 2 ^ 4 ! + 23 ^ 3 * 2 - -12", "(((2 + (3 * (2 ^ (4!)))) + ((23 ^ 3) * 2)) - (-12))");

    test_parenthesize("sqrt abs -3" , "(sqrt (abs (-3)))");
}
