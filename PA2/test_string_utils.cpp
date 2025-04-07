#include <iomanip>
#include <iostream>
#include <cstring>
#include <cmath>

#include "string_utils.cpp"

using std::cin;
using std::cout;
using std::abs;
using std::endl;

bool close_to(const double x, const double y)
{
  const double epsilon = 0.01;
  return abs(x - y) < epsilon; // The STL abs is used instead of your own absolute function
}

void test_substring(const char source[], const int from, const int to,
                    const char expected[])
{
  char destination[MAX_LEN];
  substring(source, from, to, destination);
  cout << "substring(\"" << source << "\", " << from << ", " << to << ") = \""
       << destination << "\"" << endl;
  if (strcmp(destination, expected) == 0)
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: \"" << expected << "\")" << endl;
  }
}

void test_are_equal(const char str[], const char pattern[], const bool expected)
{
  const bool result = are_equal(str, pattern);
  cout << "are_equal(\"" << str << "\", \"" << pattern << "\") = " << result
       << endl;
  if (result == expected)
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: " << expected << ")" << endl;
  }
}

void test_index_of(const char str[], const char pattern[], const int expected)
{
  const int result = index_of(str, pattern);
  cout << "index_of(\"" << str << "\", \"" << pattern << "\") = " << result
       << endl;
  if (result == expected)
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: " << expected << ")" << endl;
  }
}

void test_last_index_of(const char str[], const char pattern[], const int expected)
{
  const int result = last_index_of(str, pattern);
  cout << "last_index_of(\"" << str << "\", \"" << pattern << "\") = " << result
       << endl;
  if (result == expected)
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: " << expected << ")" << endl;
  }
}

void test_parse_digit(const char c, const int expected)
{
  const int result = parse_digit(c);
  cout << "parse_digit('" << c << "') = " << result << endl;
  if (result == expected)
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: " << expected << ")" << endl;
  }
}

void test_parse_number(const char str[], const double expected)
{
  const double result = parse_number(str);
  cout << "parse_number(\"" << str << "\") = " << result << endl;
  if (close_to(result, expected))
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: " << expected << ")" << endl;
  }
}

void test_is_digit(const char c, const bool expected)
{
  const bool result = is_digit(c);
  cout << "is_digit('" << c << "') = " << result << endl;
  if (result == expected)
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: " << expected << ")" << endl;
  }
}

void test_is_number(const char str[], const bool expected)
{
  const bool result = is_number(str);
  cout << "is_number(\"" << str << "\") = " << result << endl;
  if (result == expected)
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: " << expected << ")" << endl;
  }
}

void test_trim(const char str[], const char expected[])
{
  char result[MAX_LEN];
  trim(str, result);
  cout << "trim(\"" << str << "\") = \"" << result << "\"" << endl;
  if (strcmp(result, expected) == 0)
  {
    cout << "  => OK" << endl;
  }
  else
  {
    cout << "  => FAIL (expected: \"" << expected << "\")" << endl;
  }
}

int main()
{
  cout << std::fixed << std::setprecision(2) << std::boolalpha;

  // substring (provided)
  test_substring("COMP 2011", 0, 4, "COMP");
  test_substring("COMP 2011", 5, 9, "2011");
  test_substring("COMP 2011", 0, 9, "COMP 2011");

  // are_equal
  test_are_equal("I love COMP2011 TAs", "I love COMP2011 TAs", true);
  test_are_equal("COMP 2011", "COMP 2012", false);

  // index_of
  test_index_of("PA2 is very interesting", "very", 7);
  test_index_of("COMP 2011", ".", -1);

  // last_index_of
  test_last_index_of("PA2 is very very interesting", "very", 12);
  test_last_index_of("Arrrrrrrrrrrrrrrrrrrrr!!!!!!!!!!", "You can't find the index haha", -1);

  // // is_digit (provided)
  // for (int i = 0; i < 10; i++)
  // {
  //   test_is_digit('0' + i, true);
  // }

  // // parse_digit (provided)
  // for (int i = 0; i < 10; i++)
  // {
  //   test_parse_digit('0' + i, i);
  // }

  // is_number
  test_is_number("3.14", true);
  test_is_number(".3", false);

  // parse_number
  test_parse_number("3.14", 3.14);
  test_parse_number("3.0", 3);

  // trim
  test_trim("  PA2 is very interesting  ", "PA2 is very interesting");
  test_trim("COMP 2011", "COMP 2011");

  // You should add more test cases.
}
