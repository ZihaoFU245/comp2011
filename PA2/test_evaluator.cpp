#include <iomanip>
#include <iostream>
#include <cmath>

#include "evaluator.cpp"

using std::abs;
using std::cout;
using std::endl;

bool close_to(const double x, const double y)
{
    const double epsilon = 0.01;
    return abs(x - y) < epsilon; // The STL abs is used instead of your own absolute function
}

void test_evaluate(const char expression[], const double expected)
{
    const double result = evaluate(expression);
    cout << "evaluate(\"" << expression << "\") = " << result << endl;
    if (close_to(result, expected))
    {
        cout << "  => OK" << endl;
    }
    else
    {
        cout << "  => FAIL (expected: " << expected << ")" << endl;
    }
}

int main()
{
    cout << std::fixed << std::setprecision(2) << std::boolalpha;

    // Basic arithmetic
    test_evaluate("2 + 3 * 4", 14); // Multiplication precedence
    test_evaluate("10 - 5 / 5", 9); // Division precedence
    test_evaluate("8 / 2 * 2", 8);  // Left-to-right precedence for *, /
    test_evaluate("5 - 3 + 2", 4);  // Left-to-right precedence for +, -

    // Power operator
    test_evaluate("2 ^ 3", 8);      // Simple power
    test_evaluate("2 ^ 3 ^ 2", 512); // Right-associative power

    // Unary operators
    test_evaluate("-5 + 10", 5);    // Negative numbers
    test_evaluate("abs -5", 5);     // Absolute value
    test_evaluate("sqrt 16", 4);    // Square root
    test_evaluate("-sqrt 9", -3);   // Negative square root

    // Factorial
    test_evaluate("3!", 6);         // Factorial of 3
    test_evaluate("5!", 120);       // Factorial of 5
    test_evaluate("0!", 1);         // Factorial of 0 (edge case)

    // Constants
    test_evaluate("pi", 3.14);      // Pi constant
    test_evaluate("e", 2.71);       // E constant
    test_evaluate("pi + e", 5.85);  // Combination of constants

    // Combined operations
    test_evaluate("2 + 3 * sqrt 16", 14); // Mixed operations
    test_evaluate("abs -10 + 5", 15);     // Absolute value with addition
    test_evaluate("2 ^ 3 + 4!", 32);      // Power and factorial
    test_evaluate("sqrt 25 + 5!", 125);   // Square root and factorial

    // Edge cases
    test_evaluate("0", 0);                // Single number
    test_evaluate("-0", 0);               // Negative zero
    test_evaluate("abs 0", 0);            // Absolute of zero
    test_evaluate("sqrt 0", 0);           // Square root of zero
    test_evaluate("10 / 0", NAN);         // Division by zero (should handle gracefully)

    return 0;
}
