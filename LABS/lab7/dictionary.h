#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <cstddef>
#include <iostream>

/**
 * @brief Maximum word length. Includes the null terminator.
 */
const unsigned int MAXIMUM_WORD_LENGTH = 64;
/**
 * @brief Maximum definition length. Includes the null terminator.
 */
const unsigned int MAXIMUM_DEFINITION_LENGTH = 256;

struct dictionary_entry; // Forward declaration. Required if you want a struct to have a pointer pointing to itself.
/**
 * @brief A dictionary entry, consisting of the word and its definition.
 *
 * The dictionary is stored using a (forward) linked list of `dictionary_entry`,
 * which is implemented using the struct member `next`.
 *
 * In a dictionary, a word appears at most once. That is,
 * the linked list of dictionary entries can never have two or more
 * `dictionary_entry` with the same `word`.
 * This will affect how you implement inserting new dictionary entries,
 * which is mentioned in the lab introduction and will be described
 * again in the task description below.
 *
 * @note In fact, such a linked list is called an *association list*,
 * where `word` is the key and `definition` is the value.
 * The lab introduction should have briefly introduced it.
 */
struct dictionary_entry
{
    /**
     * @brief The next dictionary entry in the linked list.
     * It is `nullptr` if this is the last dictionary entry or
     * is not in a dictionary (linked list) yet.
     */
    dictionary_entry *next;

    /**
     * @brief A C string representing the word for this dictionary entry.
     * It must be unique in a dictionary.
     *
     * The maximum length of a word, including the null terminator,
     * is `MAXIMUM_WORD_LENGTH`, which is 64.
     */
    char word[MAXIMUM_WORD_LENGTH];

    /**
     * @brief A C string representing the definition of the word for this dictionary entry.
     * It not need be unique, i.e. two different words can have the same definition.
     *
     * The maximum length of a definition, including the null terminator,
     * is `MAXIMUM_DEFINITION_LENGTH`, which is 256.
     */
    char definition[MAXIMUM_DEFINITION_LENGTH];
};

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
void dictionary_entry_init(dictionary_entry &instance, const char *word, const char *definition);

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
 * dictionary_entry *dictionary = nullptr; // This is used as a dictionary (linked list), not a dictionary entry.
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
bool dictionary_delete_entry(dictionary_entry *&dictionary, const char *word);

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
void dictionary_add_entry(dictionary_entry *&dictionary, dictionary_entry *entry);

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
void dictionary_clear(dictionary_entry *&dictionary);

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
 * @param os The output to print the dictionary to.
 * @param dictionary A reference to a variable storing a pointer to the first entry (if any) of a dictionary.
 */
void dictionary_print(const dictionary_entry *dictionary);

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
 * @param os The output to print the dictionary to.
 * @param dictionary A reference to a variable storing a pointer to the first entry (if any) of a dictionary.
 * @param query
 */
void dictionary_query(const dictionary_entry *dictionary, const char *query);

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
void dictionary_sort(dictionary_entry *&dictionary);

#endif // DICTIONARY_H_
