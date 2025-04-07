#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define DEBUG false

/**
 * The constant of value pi.
 */
const double PI = 3.14159265358979323846;

/**
 * The constant of value e.
 */
const double E = 2.71828182845904523536;

/**
 * The maximum length of a string in this program.
 * All inputs are guaranteed to have a length less than this value.
 */
const int MAX_LEN = 256;

/**
 * Stores the substring of the string 'source' from index 'from' (inclusive) to
 * index 'to' (exclusive) into the string 'destination'.
 */
void substring(const char source[], const int from, const int to, char destination[])
{
    for (int i = from; i < to; i++)
    {
        destination[i - from] = source[i];
    }
    destination[to - from > 0 ? to - from : 0] = '\0';
}

/**
 * Returns the maximum of two integers.
 * Hint: this is useful for implementing the evaluator and the parenthesizer.
 */
int max(const int a, const int b) { return a > b ? a : b; }

#endif // DEFINITIONS_H
