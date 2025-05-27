#include "dictionary.h"

#include <cstring>
#include <iostream>

using namespace std;

/**
 * @brief Initialize data members of the provided `dictionary_entry`.
 *
 * @note Task 1: Implement this function.
 *
 * Remember that in C++, (non-struct/class) data members are not initialized by default.
 * You need to initialize them, or else you may get garbage values.
 *
 * This function should properly initialize `next`, `word`, and `definition` such that
 *
 * - There is no next `dictionary_entry`, as `instance` is not yet in a dictionary (linked list) yet.
 *
 * - `instance.word` is a C string that is copy of `word`,
 * truncated to the first `MAXIMUM_WORD_LENGTH` (64) characters,
 * including the null terminator.
 *
 * - `instance.definition` is a C string that is a copy of `definition`,
 * truncated to the first `MAXIMUM_DEFINITION_LENGTH` (256) characters,
 * including the null terminator.
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * @param instance The `dictionary_entry` to be initialized.
 * @param word The word for the dictionary entry.
 * @param definition The definition of the word for the dictionary entry.
 */
void dictionary_entry_init(dictionary_entry &instance, const char *word, const char *definition)
{
    instance.next = nullptr;
    // ensure no allocation out of bound
    if (strlen(word) > MAXIMUM_WORD_LENGTH)
    {
        strncpy(instance.word, word, MAXIMUM_WORD_LENGTH - 1);
        instance.word[MAXIMUM_WORD_LENGTH - 1] = '\0';
    }
    else
    {
        strcpy(instance.word, word);
    }

    if (strlen(definition) > MAXIMUM_DEFINITION_LENGTH)
    {
        strncpy(instance.definition, definition, MAXIMUM_DEFINITION_LENGTH - 1);
        instance.definition[MAXIMUM_DEFINITION_LENGTH - 1] = '\0';
    }
    else
    {
        strcpy(instance.definition, definition);
    }
}

/**
 * @brief Delete a dictionary entry from a dictionary.
 * Returns a `bool` indicating if the word can be found and deleted from the dictionary.
 *
 * @note Task 2: Implement this function.
 *
 * It may seem odd to implement delete first, but you will see you can
 * reuse this function in later tasks.
 *
 * `dictionary` is a reference to a variable storing a pointer to the first entry of a dictionary.
 * The variable stores `nullptr` if the dictionary is empty. It is very important
 * for you to understand why this is a reference to a pointer, since the rest
 * of the tasks will need to make use of `dictionary`.
 * Consider the following example of using `dictionary`:
 *
 * ```C++
 * // This creates two new dictionary entries.
 * dictionary_entry *new_entry = new dictionary_entry; // This is used as a dictionary entry.
 * dictionary_entry_init(*new_entry, "haha", "hehe");
 *
 * dictionary_entry *new_entry2 = new dictionary_entry; // This is used as a dictionary entry.
 * dictionary_entry_init(*new_entry2, "word", "def");
 *
 * dictionary_entry *dictionary{nullptr}; // This is used as a dictionary (linked list), not a dictionary entry.
 * // Now `dictionary == nullptr`, since the dictionary is empty, so there is no first entry.
 *
 * dictionary_add_entry(dictionary, new_entry); // Insert an entry to the dictionary at the start.
 * // Now `dictionary == new_entry`, since `new_entry` is the first (and only) entry.
 *
 * dictionary_add_entry(dictionary, new_entry2); // Insert an entry to the dictionary at the start.
 * // Now `dictionary == new_entry2`, since `new_entry2` is the first entry. `new_entry` is the second entry.
 *
 * dictionary_delete_entry(dictionary, "haha"); // Remove the entry with the word `haha` from the dictionary.
 * // Now `dictionary == new_entry`, since `new_entry2` has been removed, and `new_entry` is again the first (and only) entry.
 *
 * dictionary_delete_entry(dictionary, "word"); // Remove the entry with the word `word` from the dictionary.
 * // Now `dictionary == nullptr`, since `new_entry` has been removed, and the dictionary is empty again.
 *
 * // There is no need to `delete`, since `dictionary_delete_entry` already deletes the dynamic memory storing the entries.
 * ```
 *
 * To implement this function, iterate through the dictionary (linked list),
 * and find an entry with the specified word. Note, since a word can appear
 * at most once in the dictionary, there will not be any more entries with
 * the specified `word` if you have found the first one with the specified word.
 *
 * If you find an entry with the word, remove the entry from the linked list
 * as taught in the lectures. Take care of the case when the entry to be removed
 * is the first entry of the dictionary. Return `true` to indicate you have
 * found and removed an entry. Remember to `delete` the entry so that it
 * does not cause an memory leak.
 *
 * Otherwise, return `false` to indicate you have not found an entry
 * with the specified word to delete.
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * @param dictionary A reference to a variable storing a pointer to the first entry (if any) of a dictionary.
 * @param word The word specifying the entry (if in the dictionary) to remove.
 * @return true If an entry with the word is found and removed.
 * @return false If an entry with the word is not found.
 */
bool dictionary_delete_entry(dictionary_entry *&dictionary, const char *word)
{
    if (dictionary == nullptr)
        return false;

    // start case, special handle
    if (strcmp(dictionary->word, word) == 0)
    {
        dictionary_entry *temp = dictionary;
        dictionary = dictionary->next;
        delete temp;
        return true;
    }
    // other case , not the first one
    for (dictionary_entry *current = dictionary; current->next != nullptr; current = current->next)
    {
        if (strcmp(current->next->word, word) == 0)
        {
            dictionary_entry *temp = current->next;
            current->next = current->next->next;
            delete temp;
            return true;
        }
    }
    // otherwise
    return false;
}

/**
 * @brief Add a dictionary entry to a dictionary *at the start*,
 * replacing an old entry with the same word if it exists (but the new entry
 * is still added at the start).
 *
 * @note Task 3: Implement this function.
 *
 * See Task 2 for a detailed explanation of `dictionary`.
 *
 * For replacing the old entry, there is a very easy way to
 * ensure the old entry is removed...
 *
 * As for adding the new entry, since it is inserted at the start,
 * you do not need to iterate through the dictionary to find its end
 * to insert the new entry.
 *
 * As a reference, the solution code for this task is very simple.
 *
 * @param dictionary A reference to a variable storing a pointer to the first entry (if any) of a dictionary.
 * @param entry The entry to be added, replacing an old entry with the same word if it exists.
 */
void dictionary_add_entry(dictionary_entry *&dictionary, dictionary_entry *entry)
{
    dictionary_delete_entry(dictionary, entry->word);
    entry->next = dictionary;
    dictionary = entry;
}

/**
 * @brief Clear a dictionary, freeing up allocated dynamic memory.
 *
 * @note Task 4: Implement this function.
 *
 * See Task 2 for a detailed explanation of `dictionary`.
 *
 * Ensure there are no memory leaks.
 *
 * There is also a very easy way to implement this function...
 * As a reference, the solution code for this task is very simple, even simpler than task 3.
 *
 * @param dictionary A reference to a variable storing a pointer to the first entry (if any) of a dictionary.
 */
void dictionary_clear(dictionary_entry *&dictionary)
{
    // TODO: Task 4
    while (dictionary)
    {
        dictionary_entry *temp = dictionary;
        dictionary = dictionary->next;
        delete temp;
    }
}

/**
 * @brief Print a dictionary.
 *
 * @note Task 5: Implement this function.
 *
 * See Task 2 for a detailed explanation of `dictionary`.
 *
 * The starting output line is provided to you. Then, for each entry in the dictionary (in order),
 * print `(word): (definition)` (note the space after the colon), and then a newline.
 * Finally, print `Number of words: (number of words in the dictionary)`, and then a newline.
 * (If there is any discrepancy, the provided testcase outputs take priority over this description.)
 *
 * @param dictionary A reference to a variable storing a pointer to the first entry (if any) of a dictionary.
 */
void dictionary_print(const dictionary_entry *dictionary)
{
    cout << "Printing dictionary\n";
    // iterate throught the entire dict
    int n = 0;
    for (const dictionary_entry *current = dictionary; current != nullptr; current = current->next)
    {
        cout << current->word << ": " << current->definition << '\n';
        n++;
    }
    cout << "Number of words: " << n << endl;
}

/**
 * @brief Print entries of the dictionary for which its word contains the query string as a substring.
 *
 * @note Task 6: Implement this function.
 *
 * See Task 2 for a detailed explanation of `dictionary`.
 *
 * The starting output line is provided to you. Then, for each entry in the dictionary (in order),
 * check if the word (but not the definition) contains the query string. If yes,
 * print `(word): (definition)` (note the space after the colon), and then a newline.
 * Otherwise, do not print anything (not even the newline).
 * Finally, print `Number of words found: (number of words matching the query)`, and then a newline.
 * (If there is any discrepancy, the provided testcase outputs take priority over this description.)
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * @param dictionary A reference to a variable storing a pointer to the first entry (if any) of a dictionary.
 * @param query
 */
void dictionary_query(const dictionary_entry *dictionary, const char *query)
{
    cout << "Querying dictionary with word: " << query << '\n';
    // begin
    int n_found = 0;
    for (const dictionary_entry *current = dictionary; current != nullptr ; current = current->next)
    {
        if (strstr(current->word , query))
        {
            cout << current->word << ": " << current->definition << endl;
            n_found++;
        }
    }
    cout << "Number of words found: " << n_found << endl;
}

/**
 * @brief Sort the dictionary by lexicographical order.
 *
 * @note Task 7 (optional): Implement this function. This task is optional, i.e. ungraded.
 *
 * Feel free to use any sorting function you know. If you do not know any,
 * here is a simple sorting algorithm (but not practical in the real world):
 *
 * 1. Create a new empty dictionary.
 *
 * 2. Find the lexicographically largest word in the provided dictionary.
 *
 * 3. Copy the corresponding dictionary entry and insert it to the new dictionary at the start.
 *
 * 4. Delete the corresponding dictionary entry from the provided dictionary.
 *
 * 5. Repeat until the provided dictionary is empty.
 *
 * 6. Assign the new dictionary to `dictionary` (since `dictionary` is a reference).
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * Testcases for this optional task are named `testcase/input9X.txt` and `testcase/output9X.txt`.
 *
 * @param dictionary A reference to a variable storing a pointer to the first entry (if any) of a dictionary.
 */
void dictionary_sort(dictionary_entry *&dictionary)
{
    dictionary_entry *ret = nullptr;

    while (dictionary)
    {
        dictionary_entry *max = dictionary;
        dictionary_entry *max_prev = nullptr;
        dictionary_entry *prev = nullptr;

        for (dictionary_entry *current = dictionary; current; prev = current, current = current->next)
        {
            if (strcmp(current->word , max->word) > 0)
            {
                max = current;
                max_prev = prev;
            }
        }
        // find the max word now
        // append to ret & remove from dict

        // detach max from dictionary
        if (max_prev)
            max_prev->next = max->next;
        else
            dictionary = max->next;

        dictionary_add_entry(ret , max);
    }    

    dictionary = ret;
}
