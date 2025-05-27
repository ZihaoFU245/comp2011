#ifndef NOTE_IO_H_
#define NOTE_IO_H_

#include <iostream>

#include "note.h"

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
bool read_notes(Notes &dest);

/**
 * @brief Write notes to an output.
 *
 * @param src An initialized `Notes` object.
 * @param os The output to write to.
 */
void write_notes(const Notes &src);

#endif // NOTE_IO_H_
