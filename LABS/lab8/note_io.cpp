#include "note_io.h"

#include <cstring>
#include <iostream>
#include <limits>
#include <string>

#include "note.h"

using namespace std;

unsigned int get_intput_size()
{
  string cnt_str;
  getline(cin, cnt_str);

  unsigned int start = cnt_str.find_first_not_of(" \t\n\r");
  unsigned int end = cnt_str.find_last_not_of(" \t\n\r");
  cnt_str = cnt_str.substr(start, end - start + 1);

  return stoul(cnt_str);
}

string get_size_string(unsigned int size)
{
  string result;
  getline(cin, result);

  return result.substr(0, size);
}

/**
 * @brief Read notes from an input.
 *
 * If the input is in invalid format, `dest` is reset to empty, and `false` is returned.
 *
 * @param dest An initialized and empty `Notes` object.
 * @param is Input to read from.
 * @return true If the input can be read and parsed successfully, and result is written to `dest`.
 * @return false If the input cannot be read and parsed successfully, and `dest` is reset to empty.
 */
bool read_notes(Notes &dest)
{
  if (dest.note_array_count != 0)
  {
    // Requires initialized but empty `Notes`.
    return false;
  }

  unsigned int notes_count = get_intput_size();

  for (; dest.note_array_count < notes_count;)
  {
    unsigned int size = get_intput_size();
    string title = get_size_string(size);

    size = get_intput_size();
    string content = get_size_string(size);

    add_note(dest, title.c_str(), content.c_str());
  }

  return true;
}

/**
 * @brief Write notes to an output.
 *
 * @param src An initialized `Notes` object.
 * @param os The output to write to.
 */
void write_notes(const Notes &src)
{
  cout << src.note_array_count << '\n';
  for (unsigned int index = 0; index < src.note_array_count; ++index)
  {
    const Note &current_note = src.note_array[index];
    cout << strlen(current_note.title) << '\n'
         << current_note.title << '\n'
         << strlen(current_note.content) << '\n'
         << current_note.content << '\n';
  }
}
