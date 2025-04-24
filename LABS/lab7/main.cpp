#include <iostream>
#include <limits>
#include <string>
#include <cstring>

#include "dictionary.h"

using namespace std;

/**
 * @brief Get user option
 *
 */
int get_option()
{
    // This function is designed to get a 10-based option instead of
    // using `cin >> option`. Because it will cause errors align with
    // `getline` otherwise we need to use `cin.ignore` which is not
    // introduced in lectures.

    string opt_str;
    while (true)
    {
        getline(cin, opt_str);

        // If the string only contains white spaces including
        // " \t\n\r", then go and input the next line
        //
        // The `find` function returns `string::npos` if it
        // can not find the character in the specified string " \t\n\r"
        if (opt_str.find_first_not_of(" \t\n\r") == string::npos || opt_str.find_last_not_of(" \t\n\r") == string::npos)
            continue;

        unsigned int start = opt_str.find_first_not_of(" \t\n\r");
        unsigned int end = opt_str.find_last_not_of(" \t\n\r");

        opt_str = opt_str.substr(start, end - start + 1);
        if (opt_str.size() == 1 && opt_str[0] >= '0' && opt_str[0] <= '9')
        {
            return opt_str[0] - '0';
        }
        return -1;
    }
}

/**
 * @brief Create a new dictionary entry.
 *
 * @note Tests Task 1.
 */
void main_new_entry()
{
    string word, definition;

    cout << "Word: ";
    getline(cin, word);
    cout << "Definition: ";
    getline(cin, definition);

    dictionary_entry entry;
    entry.next = &entry;
    strcpy(entry.word, "\x01haha\0");
    strcpy(entry.definition, "\x02hehe\0");

    dictionary_entry_init(entry, word.data(), definition.data());

    cout << "`next`: " << (entry.next == nullptr ? "okay" : "garbage") << '\n';
    cout << "`word`: " << entry.word << '\n';
    cout << "`definition`: " << entry.definition << '\n';
}

/**
 * @brief Main program.
 *
 * @note Tests Task 1 to 7.
 *
 * @return int Always 0 (for grading purposes).
 */
int main()
{
    bool running = true;
    dictionary_entry *dictionary = nullptr;
    cout << "Welcome to dictionary editor!\n";

    while (running)
    {
        int option = -1;
        do
        {
            cout << "==========================================\n"
                    "0. Quit\n"
                    "1. Copy a new dictionary entry (but does not edit the dictionary)\n"
                    "2. Delete a dictionary entry\n"
                    "3. Add a dictionary entry\n"
                    "4. Clear the dictionary\n"
                    "5. Print the dictionary\n"
                    "6. Query the dictionary by partial word match (ignores definition)\n"
                    "7. Sort the dictionary\n"
                    "Option: ";

            option = get_option();
            if (option == -1)
            {
                cout << "Invalid input!\n";
                continue;
            }
            break;
        } while (true);

        switch (option)
        {
        case 0:
            cout << "Quitting!\n";
            running = false;
            break;
        case 1:
            main_new_entry();
            break;
        case 2:
        {
            string word;
            cout << "Word: ";
            getline(cin, word);

            if (dictionary_delete_entry(dictionary, word.c_str()))
            {
                cout << "Word deleted\n";
                break;
            }
            cout << "Word not found\n";
            break;
        }
        case 3:
        {
            string word, definition;
            cout << "Word: ";
            getline(cin, word);
            cout << "Definition: ";
            getline(cin, definition);

            dictionary_entry *entry = new dictionary_entry;
            dictionary_entry_init(*entry, word.c_str(), definition.c_str());

            dictionary_add_entry(dictionary, entry);
            cout << "Word added\n";
            break;
        }
        case 4:
            dictionary_clear(dictionary);
            cout << "Dictionary cleared\n";
            break;
        case 5:
            dictionary_print(dictionary);
            break;
        case 6:
        {
            string query;
            cout << "Query: ";
            getline(cin, query);

            dictionary_query(dictionary, query.c_str());
            break;
        }
        case 7:
            dictionary_sort(dictionary);
            cout << "Dictionary sorted\n";
            break;
        default:
            cout << "Unexpected code\n";
            running = false;
        }
    }

    dictionary_clear(dictionary);

    return 0;
}
