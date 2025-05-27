#include "note.h"

#include <cstddef>
#include <cstring>
#include <iostream>

using namespace std;

/**
 * @brief Initialize an *uninitialized* `Note` object.
 *
 * @note Task 1.1: Implement this function.
 *
 * Remember that in C++, (non-struct/class) data members are not initialized by default.
 * You need to initialize them, or else you may get garbage values.
 *
 * This function should properly initialize `Note` such that
 *
 * - `note.title` points to a null pointer
 *
 * - `note.content` points to a null pointer.
 *
 * After calling `init_note` on an `Note` object, the `Note` object is
 * considered *initialized*.
 *
 * This function is meant to be used by you in later tasks.
 *
 * @param note An *uninitialized* `Note` object.
 */
void init_note(Note &note)
{
    // TODO: Task 1.1
    note.content = nullptr;
    note.title = nullptr;
}

/**
 * @brief Initialize an *uninitialized* `Note` object with the given `title` and `content`.
 *
 * @note This task has been implemented for you.
 *
 * Similar to `init_note` in Task 1.1, but `note.title` and `note.content`
 * are initialized with the arguments `title` and `content`.
 * You will need to copy from the given C strings `title` and `content`.
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * After calling `init_note` on an `Note` object, the `Note` object is
 * considered *initialized*.
 *
 * This function is meant to be used by you in later tasks.
 *
 * @param note An *uninitialized* `Note` object.
 * @param title A C string to initialize `title` with.
 * @param content A C string to initialize `content` with.
 */
void init_note(Note &note, const char title[], const char content[])
{
    init_note(note);
    set_note_title(note, title);
    set_note_content(note, content);
}

/**
 * @brief Set the note title to the given `title`.
 *
 * @note Task 2.1: Implement this function.
 *
 * You will need to copy from the given C string `title`.
 * Remember to free up the dynamic memory pointed to by the old `note.title`.
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * This function is meant to be used by you in later tasks.
 *
 * @param note An *initialized* `Note` object.
 * @param title A C string to set `title` to. May be the same as `note.title`.
 */
void set_note_title(Note &note, const char title[])
{
    // TODO: Task 2.1
    delete[] note.title;
    note.title = nullptr;

    if (title)
    {
        note.title = new char[strlen(title) + 1];
        strcpy(note.title , title);
    }
}

/**
 * @brief Set the note content to the given `content`.
 *
 * @note Task 2.2: Implement this function.
 *
 * You will need to copy from the given C string `content`.
 * Remember to free up the dynamic memory pointed to by the old `note.content`.
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * This function is meant to be used by you in later tasks.
 *
 * @param note An *initialized* `Note` object.
 * @param content A C string to set `content` to. May be the same as `note.content`.
 */
void set_note_content(Note &note, const char content[])
{
    // TODO: Task 2.2
    delete[] note.content;
    note.content = nullptr;

    if (content)
    {
        note.content = new char[strlen(content) + 1];
        strcpy(note.content , content);
    }
}

/**
 * @brief Deinitialize an *initialized* `Note` object.
 *
 * @note Task 3: Implement this function.
 *
 * You will need to free up memory allocated for an *initialized* `Note` object.
 *
 * This function is meant to be used by you in later tasks.
 *
 * @param note An *initialized* `Note` object.
 */
void cleanup_note(Note &note)
{
    // TODO: Task 3
    delete[] note.title;
    delete[] note.content;

    note.title = nullptr;
    note.content = nullptr;
}

/**
 * @brief Initialize an *uninitialized* `Notes` object.
 * The resulting `Notes` object should contain no notes.
 *
 * @note This task has been implemented for you.
 *
 * Remember that in C++, (non-struct/class) data members are not initialized by default.
 * You need to initialize them, or else you may get garbage values.
 *
 * This function should properly initialize `Notes` such that
 *
 * - All `Note` objects in `note.note_array` are considered *uninitialized*
 * This is because `note.note_array_count` is 0. (Anything to do for this?)
 *
 * - `note.note_array_count` is 0, since the `Notes` object should contain
 * no notes right now.
 *
 * After calling `init_notes` on an `Notes` object, the `Notes` object is
 * considered *initialized*.
 *
 * @param notes An *uninitialized* `Notes` object.
 */
void init_notes(Notes &notes)
{
    /*
    No need to initialize the array of `Note`. Leave them uninitialized.
    We will initialize and clean up them on demand as `note_array_count` changes.
    */
    notes.note_array_count = 0;
}

/**
 * @brief Add a new note with the given title and content after the last existing note.
 * A new note will not be created and this function will return `false`
 * if there are too many notes (`MAX_NOTES` is reached)
 * or there is already a note with the same title.
 *
 * @note This task has been implemented for you.
 *
 * First, remember to check two things before adding a new note:
 * the number of notes and existing note titles.
 * A certain C string function can be used to check if two C strings are the same.
 *
 * Second, after checking, since you are adding a new note,
 * you need to *initialize* a `Note` object in the static array `note_array`
 * using `init_note`. Remember to update `note_array_count`.
 * The new note should be added after the last existing note in the array `note_array`.
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * @param notes An *initialized* `Notes` object.
 * @param title A C string as the title of the new note.
 * @param content A C string as the content of the new note.
 * @return true If the note is created successfully.
 * @return false If the note cannot be created, due to there being too many notes,
 * or there is already a note with the same title.
 */
bool add_note(Notes &notes, const char title[], const char content[])
{
    if (notes.note_array_count >= MAX_NOTES)
    {
        return false;
    }

    for (unsigned int index = 0; index < notes.note_array_count; ++index)
    {
        if (strcmp(title, notes.note_array[index].title) == 0)
        {
            return false;
        }
    }

    init_note(notes.note_array[notes.note_array_count++], title, content);
    return true;
}

/**
 * @brief Remove an existing note with the given title.
 * Notes after the removed note are moved forward by 1 slot
 * to fill in the empty slot created by the removed note.
 *
 * If a note with the given title cannot be found, return `false`.
 *
 * @note Task 4: Implement this function.
 *
 * First, you need to find a `Note` with the given title.
 * Since there are no two or more notes that have the same title
 * in a `Notes` object, if you find a `Note` with the given title,
 * that `Note` is the only `Note` with the given title, and you
 * do not need to search further along the `note_array` array.
 * Also, a certain C string function can be used to check
 * if two C strings are the same. If you do not find a `Note`
 * with the given title, simply do nothing and return `false`.
 *
 * Second, if you do find a `Note` with the given title, you
 * need to remove it, and move the `Note`s behind it in the array
 * to the front by 1 slot to fill in the empty slot created by
 * the removed `Note`. You will need to use `init_note`,
 * `cleanup_note`, `set_note_title`, and `set_note_content`
 * appropriately, such that
 *
 * - `notes.note_array_count` is reduced by 1. (Obvious.)
 *
 * - Since `notes.note_array_count` is reduced by 1,
 * the number of *initialized* `Note` objects should be reduced by 1
 * when you return from this function. However, you are free
 * to initialize and clean up any and any number of `Note` objects
 * in the intermediate steps, as long as you do not touch any
 * uninitialized memory or leak any memory, and can achieve the functionality
 * of this function.
 *
 * A suggested way is to find the `Note` object to be removed, and then
 * use `set_note_title` and `set_note_content` to move the `Note` objects
 * after it to the front by 1 slot, covering the `Note` object to be removed.
 * Finally, clean up the last *initialized* `Note` object and update the
 * `note_array_count`. This uses the minimum number of `init_note` and `cleanup_note`,
 * but other ways that use more `init_note` and `cleanup_note` are also acceptable.
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * @param notes An *initialized* `Notes` object.
 * @param title A C string containing the title to be searched for and removed.
 * @return true If the note with the given title is found and removed successfully.
 * @return false If a note with the given title cannot be found.
 */
bool remove_note(Notes &notes, const char title[])
{
    // TODO: Task 4

    for (unsigned int i = 0 ; i < notes.note_array_count ; i++)
    {
        // go over the array of notes
        // find the note needs to be deleted
        if (strcmp(title , notes.note_array[i].title) == 0)
        {
            for (unsigned int j = i ; j < notes.note_array_count - 1; j++)
            {
                set_note_title(notes.note_array[j] , notes.note_array[j + 1].title);
                set_note_content(notes.note_array[j] , notes.note_array[j + 1].content);
            }
            cleanup_note(notes.note_array[notes.note_array_count - 1]);
            notes.note_array_count--;
            return true;
        }
    }

    return false;
}

/**
 * @brief Rename a note with the given title to the given new title.
 * This returns `false` if the note with the given title cannot be found,
 * or the new title will clash with another existing note (including the
 * note to be renamed).
 *
 * @note Task 5: Implement this function.
 *
 * First, you need to check if the new title clashes with the title
 * of an existing note. A certain C string function can be used to check
 * if two C strings are the same. Note that you do not need to check
 * if the clashing note is the note we are trying to rename now,
 * since this happens only if `title` is equal to `new_title`, and we still
 * return `false` in this case because even if we can technically
 * rename it, the title is effectively unchanged.
 *
 * Second, rename the note. Make use of the functions you have implemented above.
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * @param notes An *initialized* `Notes` object.
 * @param title A C string containing the title to be searched for and renamed.
 * @param new_title A C string containing the new title.
 * @return true If the note with the given title is found and renamed successfully.
 * @return false If a note with the given title cannot be found,
 * or the new title clashes with the title of an existing note.
 */
bool rename_note(Notes &notes, const char title[], const char new_title[])
{
    // first check if the new name clashes
    bool found = false;
    for (unsigned int i = 0 ; i < notes.note_array_count ; i++)
    {
        if (strcmp(new_title , notes.note_array[i].title) == 0)
            return false;
        
        if (strcmp(title , notes.note_array[i].title) == 0)
        {
            found = true;
        }
    }
    if (!found)
        return false; // title can not be found
    // change title
    for (unsigned int j = 0 ; j < notes.note_array_count ; j++)
    {
        if (strcmp(title , notes.note_array[j].title) == 0)
        {
            set_note_title(notes.note_array[j] , new_title);
            return true;
        }
    }


    return false;
}

/**
 * @brief Replace the content of the note with the given title by the new content.
 * Returns `false` if a note with the given title cannot be found.
 *
 * @note Task 6: Implement this function.
 *
 * Find the note with the given title. A certain C string function can be used to check
 * if two C strings are the same. If you don't find it, do nothing and return `false`.
 * Otherwise, edit the note, using the functions you have implemented above.
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * @param notes An *initialized* `Notes` object.
 * @param title A C string containing the title to be searched for and edited.
 * @param new_content A C string containing new content to replace the old content of the note with.
 * @return true If the note with the given title can be found and edited.
 * @return false If a note with the given title cannot be found.
 */
bool edit_note(Notes &notes, const char title[], const char new_content[])
{
    // TODO: Task 6
    for (unsigned int i = 0 ; i < notes.note_array_count ; i++)
    {
        if (strcmp(title , notes.note_array[i].title) == 0)
        {
            set_note_content(notes.note_array[i] , new_content);
            return true;
        }
    }

    return false;
}

/**
 * @brief Add the given content after the content of the note with the given title.
 * Returns `false` if a note with the given title cannot be found.
 *
 * @note Task 7: Implement this function.
 *
 * Find the note with the given title. A certain C string function can be used to check
 * if two C strings are the same. If you don't find it, do nothing and return `false`.
 * Otherwise, add the new content after the existing content of the note,
 * using the functions you have implemented above. Another certain C string function
 * can be used to concatenate/join two or more C string functions together.
 *
 * You are recommended to use the C string functions introduced in the lab webpage.
 *
 * @param notes An *initialized* `Notes` object.
 * @param title A C string containing the title to be searched for and appended.
 * @param content_to_append A C string containing content to be added after old content of the note.
 * @return true If the note with the given title can be found and appended.
 * @return false If a note with the given title cannot be found.
 */
bool append_note_content(Notes &notes, const char title[], const char content_to_append[])
{
    // TODO: Task 7
    for (unsigned int i = 0 ; i < notes.note_array_count ; i++)
    {
        if (strcmp(title , notes.note_array[i].title) == 0)
        {
            int appended_len = strlen(notes.note_array[i].content) + strlen(content_to_append);

            char *arr = new char[appended_len + 1];
            
            strcpy(arr , notes.note_array[i].content);
            strcat(arr , content_to_append);
            
            set_note_content(notes.note_array[i] , arr);

            delete[] arr;

            return true;
        }
    }
    return false;
}

/**
 * @brief Search a note containing the given query string in its title or its content,
 * starting from the `start_index` (inclusive), and returns its index in `note_array`.
 * If such a note cannot be found, `INVALID_INDEX` is returned instead.
 *
 * @note This task has been implemented for you.
 *
 * For each note, starting from `start_index` (inclusive), check if the note
 * title contains the query and if the note content contains the query.
 * If at least one of the above contains the query, return the note index.
 * A certain C string function can be used to check if a string contains
 * another string (that is, checks if the latter string is a substring of
 * the former string). If no such note can be found, return `INVALID_INDEX`.
 *
 * @param notes An *initialized* `Notes` object.
 * @param query A C string containing the query to match in the notes' title and content.
 * @param start_index Index of the note in `note_array` to start the search with (inclusive).
 * @return unsigned int Index of the next note found containing the query.
 */
unsigned int search_note(const Notes &notes, const char query[], unsigned int start_index)
{
    for (unsigned int index = start_index; index < notes.note_array_count; ++index)
    {
        const Note &current_note = notes.note_array[index];
        if (strstr(current_note.title, query) || strstr(current_note.content, query))
        {
            return index;
        }
    }

    return INVALID_INDEX;
}

/**
 * @brief Free up the memory of an *initialized* `Notes` object.
 *
 * @note This task has been implemented for you.
 *
 * You will need to free up memory allocated for an *initialized* `Notes` object,
 * including its data members. That means you need to clean up the
 * *initialized* `Notes`. (But setting `note_array_count` is okay but not necessarily,
 * since in this lab, we will not reuse an `Notes` object.)
 *
 * After calling `cleanup_notes` on an `Notes` object, the `Notes` object is
 * considered *uninitialized*. Note that you do not need to intentionally
 * set `note_array` and `note_array_count` to garbage values, but you can consider
 * the resulting *uninitialized* `Notes` object as-if it is containing garbage
 * values.
 *
 * @param notes An *initialized* `Notes` object.
 */
void cleanup_notes(Notes &notes)
{
    /*
    // Below is the laziest way to do this task. But it is far from the most performant one.
    while (notes.note_array_count > 0)
    {
      remove_note(notes, notes.note_array[0].title);
      // No matter if you use `0` or `notes.note_array_count - 1`, you still need to iterate through all notes in `remove_note`, making it not performant.
    }
    */

    for (; notes.note_array_count > 0; --notes.note_array_count)
    {
        cleanup_note(notes.note_array[notes.note_array_count - 1]);
    }
}

// Functions that you do not need to implement

/**
 * @brief Get a note object with the given title, or `nullptr` if not found.
 *
 * @note This is the non-`const` overload.
 *
 * You do not need to use this function.
 *
 * @param notes An initialized `Notes` object.
 * @param title A C string containing the title to be searched for.
 * @return Note* The note with the given title, or `nullptr` if not found.
 */
Note *get_note(Notes &notes, const char title[])
{
    for (unsigned int index = 0; index < notes.note_array_count; ++index)
    {
        Note &current_note = notes.note_array[index];
        if (strcmp(title, current_note.title) == 0)
        {
            return &current_note;
        }
    }

    return nullptr;

    // return const_cast<Note *>(get_note(static_cast<Notes const &>(notes), title));
}

/**
 * @brief Get a note object with the given title, or `nullptr` if not found.

 * @note This is the `const` overload. (But in this lab, we do not have
 * any const `Note` objects, so this overload is not actually used.)
 *
 * You do not need to use this function.
 *
 * @param notes An initialized `Notes` object.
 * @param title A C string containing the title to be searched for.
 * @return Note* The note with the given title, or `nullptr` if not found.
 */
const Note *get_note(const Notes &notes, const char title[])
{
    for (unsigned int index = 0; index < notes.note_array_count; ++index)
    {
        const Note &current_note = notes.note_array[index];
        if (strcmp(title, current_note.title) == 0)
        {
            return &current_note;
        }
    }

    return nullptr;
}

/**
 * @brief Print the given note to the given output.
 * Note that a newline is printed after printing the note.
 *
 * @note You do not need to use this function.
 *
 * @param os Output to print to.
 * @param note Note to be printed.
 */
void print_note(const Note &note)
{
    cout << "Title: " << note.title << '\n'
         << "Content:\n"
         << note.content << '\n';
}

/**
 * @brief Max length of content in a note summary.
 */
const unsigned int SUMMARY_MAX_LEN = 100;

/**
 * @brief Print the given note, as a short one-liner, to the given output.
 * Note that no newline is printed after printing the note summary.
 *
 * @note You do not need to use this function.
 *
 * @param os Output to print to.
 * @param note Note to be printed.
 */
void print_note_summary(const Note &note)
{
    const char *truncate_pos = strstr(note.content, "\n");
    unsigned int summary_len = truncate_pos ? (truncate_pos - note.content) : SUMMARY_MAX_LEN;
    summary_len = summary_len > SUMMARY_MAX_LEN ? SUMMARY_MAX_LEN : SUMMARY_MAX_LEN;

    char *output_buffer = new char[summary_len + 1];
    strncpy(output_buffer, note.content, summary_len);
    output_buffer[summary_len] = '\0';

    cout << note.title << ": " << output_buffer;
    if (summary_len < strlen(note.content))
        cout << "...";

    delete[] output_buffer;
}
