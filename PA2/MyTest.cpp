#include <iostream>
using namespace std;
#include <cstring>
#include "string_utils.cpp"
#include "math_utils.cpp"
#include "evaluator.cpp"
#include "parenthesizer.cpp"

int min(const int a, const int b) { return a > b ? b : a; }

void add_brackets(const char raw[], char destination[])
{
    char expression[MAX_LEN];
    trim(raw, expression);

    if (is_number(expression))
    {
        strcat(destination, expression);
        return;
    }

    int index{};
    char lhs[MAX_LEN];
    char rhs[MAX_LEN];

    // try left-associativity
    if ((index = max(
            last_index_of(expression, " + ") >= 0 ? last_index_of(expression, " + ") : -1,
            last_index_of(expression, " - ") >= 0 ? last_index_of(expression, " - ") : -1)) >= 0)
    {
        substring(expression, 0, index, lhs);
        substring(expression, index + 3, strlen(expression), rhs);

        strcat(destination, "(");
        add_brackets(lhs, destination);
        strcat(destination, expression[index+1] == '+' ? " + " : " - ");
        add_brackets(rhs, destination);
        strcat(destination, ")");

        return;
    }
    // for mul and div , * /
    if ((index = max(
            last_index_of(expression, " * ") >= 0 ? last_index_of(expression, " * ") : -1,
            last_index_of(expression, " / ") >= 0 ? last_index_of(expression, " / ") : -1)) >= 0)
    {
        substring(expression, 0, index, lhs);
        substring(expression, index + 3, strlen(expression), rhs);

        strcat(destination, "(");
        add_brackets(lhs, destination);
        strcat(destination, expression[index+1] == '*' ? " * " : " / ");
        add_brackets(rhs, destination);
        strcat(destination, ")");

        return;
    }

    // If no operator found, just add the expression as is
    strcat(destination, expression);
}

int main()
{
    char src[] = " sqrt pi * e * e ^ pi";
    char t[MAX_LEN] = {};
    char dest[MAX_LEN]{};
    parenthesize(src, dest);
    cout << dest << endl;

    dest[0] = '\0';
    add_brackets(src , dest);
    cout << dest << endl;
}
