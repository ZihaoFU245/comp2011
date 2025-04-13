#include <iomanip>
#include <iostream>
#include <cmath>

#include "evaluator.cpp"
#include "limits"

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

    test_evaluate(" 3 + 2 * sqrt abs -3" , 6.46);
    return 0;
}
