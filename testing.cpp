#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

bool is_numeric(const char *str)
{
    while (*str)
    {
        if (!(isdigit(*str)))
        {
            return false;
        }
        str++;
    }
    return true;
}

const char *my_strstr(const char *haystack, const char *needle)
{
}

void test_my_strstr()
{
    // Test cases
    const char *text1 = "hello world";
    const char *pattern1 = "world";

    const char *text2 = "abcdef";
    const char *pattern2 = "cd";

    const char *text3 = "abcdef";
    const char *pattern3 = "gh"; // Not present

    const char *text4 = "aaaaaa";
    const char *pattern4 = "aaa"; // Multiple occurrences

    const char *text5 = "abc";
    const char *pattern5 = ""; // Empty pattern

    // Debugging output
    std::cout << "Test 1: " << (my_strstr(text1, pattern1) ? my_strstr(text1, pattern1) : "Not Found") << std::endl;
    std::cout << "Test 2: " << (my_strstr(text2, pattern2) ? my_strstr(text2, pattern2) : "Not Found") << std::endl;
    std::cout << "Test 3: " << (my_strstr(text3, pattern3) ? my_strstr(text3, pattern3) : "Not Found") << std::endl;
    std::cout << "Test 4: " << (my_strstr(text4, pattern4) ? my_strstr(text4, pattern4) : "Not Found") << std::endl;
    std::cout << "Test 5: " << (my_strstr(text5, pattern5) ? my_strstr(text5, pattern5) : "Not Found") << std::endl;
}

void find_all_occurrences(const char *text, const char *pattern)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        // go through each element
        // match pattern
        bool this_index = true;
        for (int j = 0; pattern[j] != '\0'; j++)
        {
            // verify remaining num letters
            if (text[i + j] == '\0')
            {
                this_index = false;
                break;
            }
            // start matching
            if (text[i + j] != pattern[j])
            {
                this_index = false;
            }
        }
        // cout
        if (this_index)
        {
            cout << i << endl;
        }
    }
}

void test_find_all_occurrences()
{
    char a[] = "ababab";
    char apa[] = "ab";

    char b[] = "hello";
    char bpa[] = "ll";

    char f[] = "no way";
    char fpa[] = "yes";

    find_all_occurrences(a, apa);
    cout << endl;
    find_all_occurrences(b, bpa);
    cout << endl;
    find_all_occurrences(f, fpa);
}

bool wildcard_match(const char *str, const char *pattern)
{
    int start_index = 0;
    char pattern_char, next_char;

    for (int i = 0; pattern[i] != '\0'; i++)
    {
        pattern_char = pattern[i];
        next_char = (pattern[i + 1] == '\0') ? '\0' : pattern[i + 1];

        // If next char is '\0' and pattern_char is '*', it can match the rest
        if (pattern_char == '*' && next_char == '\0')
            return true;

        switch (pattern_char)
        {
        case '?':
            // Check boundary
            if (str[start_index] == '\0')
                return false;
            start_index++;
            break;

        case '*':
        {
            // If '*' is followed by '\0', it matches everything
            if (next_char == '\0')
                return true;

            bool found = false;
            for (int j = start_index; str[j] != '\0'; j++)
            {
                if (str[j] == next_char)
                {
                    start_index = j;
                    found = true;
                    break;
                }
            }
            if (!found)
                return false;
            break;
        }

        default:
            // Regular character
            if (str[start_index] == '\0' || str[start_index] != pattern_char)
                return false;
            start_index++;
            break;
        }
    }
    // Return true only if we didn't leave unmatched characters in 'str'
    return (str[start_index] == '\0');
}

void reverse_words(char *str)
{
    if (*str == '\0')
        return;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ' || str[i + 1] == '\0')
        {
            // recursion here
            reverse_words(str + i + 1);
            // out put the first word here
            for (int j = 0; j <= i; j++)
            {
                cout << str[j];
            }
            cout << ' ';
            break;
        }
    }
}

void run_length_encoding(const char *str, char *result)
{
    if (*str == '\0')
    {
        *result = '\0';
        return;
    }

    int count = 0;
    char this_char = *str;

    const char *ptr = str;
    while (*ptr == this_char && *ptr != '\0')
    {
        count++;
        ptr++;
    }

    result[0] = this_char;
    result[1] = '0' + count;

    run_length_encoding(ptr, result + 2);
}

long long to_any_base(int num, int base)
{
    // find out nearest 10 to base
    int n = pow(10, (base / 10 + 1));
    long long value;
    // stop condition
    if (num < base)
        return num;

    // recursion step
    int last_digit = num % base;
    value = to_any_base(num / base, base);

    return value * n + last_digit;
}

void my_itoa(int num, char *buffer, int base)
{
    long long buffer_num = to_any_base(num, base);
    int index = 0;

    if (base == 16)
    {
        sprintf(buffer, "%llX", buffer_num);
        return;
    }

    while (buffer_num > 0)
    {
        int digit = buffer_num % 10;
        buffer[index++] = '0' + digit;
        buffer_num /= 10;
    }

    buffer[index] = '\0';

    // Reverse the buffer to get the correct order
    int start = 0;
    int end = index - 1;
    while (start < end)
    {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}

int main()
{
    char a[100];
    my_itoa(43775 , a , 16);
    cout << a;
}