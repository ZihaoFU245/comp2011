#ifndef STRING_UTILS_CPP
#define STRING_UTILS_CPP

#include <cstring>

#include "definitions.cpp"
#include "math_utils.cpp"

/*
You MUST use recursion to complete TASK 2. You are NOT allowed to use any for or while loop.
*/

/**
 * Indicates whether the string 'a' represents the same string value as 'b'.
 * @return true if the values are the same; false otherwise.
 */
bool are_equal(const char a[], const char b[])
{
	if (*a == '\0' && *b == '\0')
		return true;
	if (*a != *b)
		return false;

	return are_equal(a + 1, b + 1);
}

/**
 * Returns the index of the *first* character of the *first* pattern occurrence in the string.
 *
 * E.g. str = "This is the pattern 1 and pattern 2", pattern = "pattern"
 * index_of should return 12 (... pattern 1 and pattern 2)
 *                                ^
 */
int index_of(const char str[], const char pattern[])
{
	if (*str == '\0')
		return -1;

	int len_pattern = strlen(pattern);

	char buffer[MAX_LEN]{};
	substring(str , 0 , len_pattern , buffer);

	if (are_equal(buffer , pattern))
		return 0;
	else
	{
		int result = index_of(str + 1 , pattern);
		return (result < 0) ? -1 : (result + 1);
	}
}

/**
 * Returns the index of the *first* character of the *last* pattern occurrence in the string.
 *
 * E.g. str = "This is the pattern 1 and pattern 2", pattern = "pattern"
 * index_of should return 26 (... pattern 1 and pattern 2)   ==> different from index_of
 *                                              ^
 */
int last_index_of(const char str[], const char pattern[])
{
	static int index = 0;
	static int result = -1;

	int len_pattern = strlen(pattern);
	static char buffer[MAX_LEN]{};

	if (*str == '\0')
	{
		int final_ = result;
		index = 0;
		result = -1;
		return final_;
	}

	substring(str , 0 , len_pattern , buffer);
	
	if (are_equal(buffer, pattern))
		result = index;

	index++;
	return last_index_of(str + 1, pattern);
}

/**
 * Indicates if the character 'c' is a digit.
 *
 * If 'c' is one of the characters '0', '1', ..., '9', then it is a digit; and
 * this function returns true; otherwise, it returns false.
 */
bool is_digit(const char c) { return c >= '0' && c <= '9'; }

/**
 * Returns the integer value of the digit character 'c'.
 *
 * If 'c' is one of the characters '0', '1', ..., '9', then it returns the
 * corresponding integer value of the digit, i.e., 0, 1, ..., 9.
 */
int parse_digit(const char c) { return c - '0'; }

/**
 * Indicates if the string 'str' represents a number.
 */
bool is_number(const char str[])
{
	static int index = 0;
	static bool has_decimal = false;

	if (*str == '\0')
	{
		bool result = (index > 0) && (str[-1] != '.');
		index = 0;
		return result;
	}

	if (index == 0 && *str == '.')
	{
		index = 0;
		has_decimal = false;
		return false;
	}

	if (*str == '.')
	{
		if (has_decimal)
		{
			index = 0;
			has_decimal = false;
			return false;
		}

		has_decimal = true;
	}
	else if (!(is_digit(*str)))
	{
		index = 0;
		has_decimal = false;
		return false;
	}

	index++;
	return is_number(str + 1);
}

/**
 * Returns the value of the number represented by the string 'str'.
 */
double parse_number(const char str[])
{
	static bool is_decimal = false;
	static int decimal_point = 0;
	static double integer_part = 0;
	
	if (*str == '\0')
	{
		double result = integer_part;
		integer_part = 0;
		is_decimal = false;
		decimal_point = 0;
		return result;
	}

	if (*str == '.')
	{
		is_decimal = true;
		decimal_point = 1;
		return parse_number(str + 1);
	}

	int this_digit = parse_digit(*str);

	if (is_decimal)
	{
		double result = this_digit / power(10, decimal_point);
		decimal_point++;
		return result + parse_number(str + 1);
	}
	else
	{
		integer_part = integer_part * 10 + this_digit;
		return parse_number(str + 1);
	}
}

/**
 * Remove all leading and trailing whitespaces from the string 'str', and store
 * the result in 'destination'.
 */
void trim(const char str[], char destination[])
{
	static int from = -1;
	static int end = -1;
	static int index = 0;
	// stop condition
	if (str[index] == '\0')
	{
		if (from == -1)
		{
			destination[0] = '\0';
		}
		else
		{
			substring(str, from , end + 1 , destination);
		}
		from = -1;
		end = -1;
		index = 0;
		return;
	}
	// iteration
	if (from == -1 && str[index] != ' ')
	{
		from = index;
	}

	if (str[index] != ' ')
	{
		end = index;
	}

	index++;
	trim(str, destination);
}

#endif // STRING_UTILS_CPP
