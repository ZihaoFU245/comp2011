#ifndef PARENTHESIZER_CPP
#define PARENTHESIZER_CPP

#include <cstring>

#include "string_utils.cpp"

// remove this later
#include <iostream>

/*
You can use for or while loop to complete TASK 4, but it is highly recommended to use recursion.
strlen , strcpy , strcat
*/

void parenthesize(const char raw_expression[], char destination[])
{
    char expression[MAX_LEN];
    trim(raw_expression, expression);

    static int recursionDepth = 0;
    if (recursionDepth == 0)
    {
        destination[0] = '\0';
    }
    recursionDepth++;

    if (is_number(expression))
    {
        strcat(destination, expression);
        recursionDepth--;
        return;
    }
    if (are_equal(expression , "e"))
    {
        strcat(destination , expression);
        recursionDepth--;
        return;
    }
    if (are_equal(expression , "pi"))
    {
        strcat(destination , expression);
        recursionDepth--;
        return;
    }

    int index{};
    char lhs[MAX_LEN]{};
    char rhs[MAX_LEN]{};
    
    // implement + - case
    if ((index = max(last_index_of(expression , " + ") , last_index_of(expression , " - "))) > 0)
    {
        substring(expression, 0, index, lhs);
        substring(expression, index + 3, strlen(expression), rhs);

        strcat(destination, "(");
        parenthesize(lhs, destination);
        strcat(destination, expression[index + 1] == '+' ? " + " : " - ");
        parenthesize(rhs, destination);
        strcat(destination, ")");
        recursionDepth--;
        return;
    }
    // implement * / case
    if ((index = max(last_index_of(expression , " * ") , last_index_of(expression , " / "))) > 0)
    {        
        substring(expression, 0, index, lhs);
        substring(expression, index + 3, strlen(expression), rhs);

        strcat(destination, "(");
        parenthesize(lhs, destination);
        strcat(destination, expression[index + 1] == '*' ? " * " : " / ");
        parenthesize(rhs, destination);
        strcat(destination, ")");
        recursionDepth--;
        return;
    }
    // implement ^ case
    if ((index = index_of(expression, " ^ ")) > 0)
    {
        substring(expression, 0, index, lhs);
        substring(expression, index + 3, strlen(expression), rhs);

        strcat(destination, "(");
        parenthesize(lhs, destination);
        strcat(destination, " ^ ");
        parenthesize(rhs, destination);
        strcat(destination, ")");
        recursionDepth--;
        return;
    }
    // implement sqrt and abs
    if ((index = index_of(expression, "sqrt")) >= 0 &&
        (index_of(expression, "abs") < 0 || index <= index_of(expression, "abs")))
    {
        substring(expression, index + 4, strlen(expression), rhs);

        strcat(destination, "(");
        strcat(destination, "sqrt ");
        parenthesize(rhs, destination);
        strcat(destination, ")");
        recursionDepth--;
        return;
    }
    else if ((index = index_of(expression, "abs")) >= 0)
    {
        substring(expression, index + 3, strlen(expression), rhs);

        strcat(destination, "(");
        strcat(destination, "abs ");
        parenthesize(rhs, destination);
        strcat(destination, ")");
        recursionDepth--;
        return;
    }
    // implement negation
    if (expression[0] == '-')
    {
        substring(expression, 1, strlen(expression), rhs);

        strcat(destination, "(");
        strcat(destination, "-");
        parenthesize(rhs, destination);
        strcat(destination, ")");
        recursionDepth--;
        return;
    }
    // implement !
    if ((index = last_index_of(expression , "!")) > 0)
    {
        substring(expression , 0 , index , lhs);
        substring(expression , index + 1 , strlen(expression) , rhs);

        strcat(destination , "(");
        parenthesize(lhs , destination);
        strcat(destination , "!)");
        recursionDepth--;
        return;
    }


    // Only invalid expressions should reach this point
    // because your code should have parenthesized and returned all valid expression forms.
    // If this point is reached, it means the expression
    // is invalid OR there is a bug in your code.
    // This is only for debugging purposes, and we won't test the behavior
    // of your code for invalid expressions.
    std::cerr << "Invalid expression: '" << expression << "'" << std::endl;
}

#endif // PARENTHESIZER_CPP
