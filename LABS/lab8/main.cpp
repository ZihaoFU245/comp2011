#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#include "note_io.h"
#include "note.h"

using namespace std;

enum Option
{
    QUIT = 0,
    LIST_NOTES = 1,
    PRINT_A_NOTE = 2,
    ADD_A_NOTE = 3,
    REMOVE_A_NOTE = 4,
    RENAME_A_NOTE = 5,
    EDIT_A_NOTE = 6,
    APPEND_TO_A_NOTE = 7,
    SEARCH_NOTES = 8,
};

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
 * @brief Program portion that reads notes from a file or stdin.
 *
 * @param notes An initialized and empty `Notes` object.
 */
void main_read_notes(Notes &notes)
{
    do
    {
        cout << "Read notes from (empty to skip, '-' for stdin): ";

        string filename;
        getline(cin, filename);

        if (filename.empty())
        {
            cout << "Skipped reading notes\n";
            return;
        }
        else if (filename == "-")
        {
            cout << "Input:\n";
            if (!read_notes(notes))
            {
                cin.clear();
                cout << "Invalid input!\n";
                continue;
            }
            cout << "Notes read\n";
            return;
        }
        else
        {
            cout << "Invalid option!\n";
            continue;
        }

    } while (true);
}

/**
 * @brief Program portion that writes notes to a file or stdout.
 *
 * @param notes An initialized `Notes` object.
 */
void main_write_notes(const Notes &notes)
{
    do
    {
        cout << "==========================================\n"
                "File to write notes to (empty to skip, '-' for stdout): ";

        string filename;
        getline(cin, filename);

        if (filename.empty())
        {
            cout << "Skipped writing notes\n";
            return;
        }
        else if (filename == "-")
        {
            write_notes(notes);
            cout << "Notes written\n";
            break;
        }
        else
        {
            cout << "Invalid option!\n";
            continue;
        }
    } while (true);
}

/**
 * @brief Program loop that allows user to edit notes.
 *
 * @param notes An initialized `Notes` instance.
 */
void main_edit_notes(Notes &notes)
{
    bool running = true;
    int option_raw = -1;
    Option option;

    while (running)
    {

        do
        {
            cout << "==========================================\n"
                    "0. Quit\n"
                    "1. List notes\n"
                    "2. Print a note\n"
                    "3. Add a note\n"
                    "4. Remove a note\n"
                    "5. Rename a note\n"
                    "6. Edit a note\n"
                    "7. Append to a note\n"
                    "8. Search notes\n"
                    "Option: ";
            option_raw = get_option();
            if (option_raw < 0 || option_raw > 8)
            {
                cout << "Invalid input!\n";
                continue;
            }
            option = (Option)option_raw;
            break;
        } while (true);

        switch (option)
        {
        case QUIT:
            cout << "Quitting!\n";
            running = false;
            break;
        case LIST_NOTES:
            cout << "There are " << notes.note_array_count << " note(s)\n";
            for (unsigned int index = 0; index < notes.note_array_count; ++index)
            {
                cout << index + 1 << ". ";
                print_note_summary(notes.note_array[index]);
                cout << '\n';
            }
            break;
        case PRINT_A_NOTE:
        {
            string title;
            cout << "Title: ";
            getline(cin, title);

            const Note *note = get_note(notes, title.c_str());
            if (note)
            {
                print_note(*note);
                break;
            }
            cout << "Note not found\n";
            break;
        }
        case ADD_A_NOTE:
        {
            string title, content;
            cout << "Title: ";
            getline(cin, title);
            cout << "Content: ";
            getline(cin, content);

            if (!add_note(notes, title.c_str(), content.c_str()))
            {
                cout << "Note title already exists or too many notes\n";
                break;
            }
            cout << "Note added\n";
            break;
        }
        case REMOVE_A_NOTE:
        {
            string title;
            cout << "Title: ";
            getline(cin, title);

            if (!remove_note(notes, title.c_str()))
            {
                cout << "Note not found\n";
                break;
            }
            cout << "Note removed\n";
            break;
        }
        case RENAME_A_NOTE:
        {
            string title, new_title;
            cout << "Title: ";
            getline(cin, title);
            cout << "New title: ";
            getline(cin, new_title);

            if (!rename_note(notes, title.c_str(), new_title.c_str()))
            {
                cout << "Note not found or new note title already exists\n";
                break;
            }
            cout << "Note renamed\n";
            break;
        }
        case EDIT_A_NOTE:
        {
            string title, new_content;
            cout << "Title: ";
            getline(cin, title);
            cout << "New content: ";
            getline(cin, new_content);

            if (!edit_note(notes, title.c_str(), new_content.c_str()))
            {
                cout << "Note not found\n";
                break;
            }
            cout << "Note edited\n";
            break;
        }
        case APPEND_TO_A_NOTE:
        {
            string title, content_to_append;
            cout << "Title: ";
            getline(cin, title);
            cout << "Content to append: ";
            getline(cin, content_to_append);

            if (!append_note_content(notes, title.c_str(), content_to_append.c_str()))
            {
                cout << "Note not found\n";
                break;
            }
            cout << "Note appended\n";
            break;
        }
        case SEARCH_NOTES:
        {
            string query;
            cout << "Query: ";
            getline(cin, query);

            unsigned int index = INVALID_INDEX, count = 0;
            do
            {
                index = search_note(notes, query.c_str(), ++index);
                if (index == INVALID_INDEX)
                {
                    break;
                }

                cout << index + 1 << ". ";
                print_note_summary(notes.note_array[index]);
                cout << '\n';

                ++count;
            } while (true);

            cout << "Found " << count << " note(s)\n";
            break;
        }
        default:
            cout << "Unexpected code\n";
            running = false;
        }
    }
}

/**
 * @brief Main program.
 *
 * @return int Always 0 (for grading purposes).
 */
int main()
{
    cout << "Welcome to note-taking system!\n";

    Notes notes;
    notes.note_array_count = -1;

    cout << "Initializing...\n";
    init_notes(notes);

    main_read_notes(notes);
    main_edit_notes(notes);
    main_write_notes(notes);

    cout << "Cleaning up...\n";
    cleanup_notes(notes);

    cout << "See you!\n";

    return 0;
}
