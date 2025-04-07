#ifndef MATH_UTILS_CPP
#define MATH_UTILS_CPP

#include "definitions.cpp"

/*
You MUST use recursion to complete TASK 1. You are NOT allowed to use any for or while loop.
*/

/**
 * Returns the absolute value of x.
 */
double absolute(const double x)
{
    // TODO Task 1.1 BEGIN
    if (x < 0)
    {
        return -x;
    }
    return x;
    // TODO Task 1.1 END
}

/**
 * Indicates if a result from an iterative algorithm is accurate enough.
 * We define "accurate enough" as the difference between the previous and
 * current results to be less than 0.001.
 */
bool is_accurate_enough(const double previous, const double current)
{
    return absolute(previous - current) < 0.001;
}

/**
 * Returns the square root of x.
 */
double square_root(const double x)
{
    if (x == 1 || x == 0)
        return x;

    static double guess = x;

    double next_x = 0.5 * (guess + x / guess);

    if (is_accurate_enough(guess, next_x))
        return next_x;

    guess = next_x;
    return square_root(x);
}

/**
 * Returns the value of base raised to the exponent power.
 */
double power(const double base, const int exponent)
{
    if (exponent == 0)
        return 1;

    return base * power(base, exponent - 1);
}

/**
 * Returns the factorial of n.
 */
double factorial(const int n)
{
    if (n <= 0) return 1;

    return n * factorial(n - 1);
}

#endif // MATH_UTILS_CPP
