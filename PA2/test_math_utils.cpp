#include <iomanip>
#include <iostream>
#include <cmath>

#include "math_utils.cpp"

using std::abs;
using std::cout;
using std::endl;

bool close_to(const double x, const double y)
{
  const double epsilon = 0.01;
  return abs(x - y) < epsilon; // The STL abs is used instead of your own absolute function
}

void test_absolute(const double x, const double expected)
{
  const double result = absolute(x);
  cout << "abs(" << x << ") = " << result << endl;
  if (close_to(result, expected))
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: " << expected << ")" << endl;
  }
}

void test_square_root(const double x, const double expected)
{
  const double result = square_root(x);
  cout << "sqrt(" << x << ") = " << result << endl;
  if (close_to(result, expected))
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: " << expected << ")" << endl;
  }
}

void test_power(const double base, const int exponent, const double expected)
{
  const double result = power(base, exponent);
  cout << "power(" << base << ", " << exponent << ") = " << result << endl;
  if (close_to(result, expected))
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: " << expected << ")" << endl;
  }
}

void test_factorial(const int n, const double expected)
{
  const int result = factorial(n);
  cout << "factorial(" << n << ") = " << result << endl;
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

  // absolute
  test_absolute(-3.14, 3.14);

  // square root
  test_square_root(8, 2.83);
  test_square_root(0, 0);

  // power
  test_power(-3, 3, -27);
  test_power(2, 0, 1);

  // factorial
  test_factorial(6, 720);
  test_factorial(0, 1);

  // You should add more test cases.
}
