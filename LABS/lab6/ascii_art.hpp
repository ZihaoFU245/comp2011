#ifndef ASCII_ART_HPP
#define ASCII_ART_HPP

#include "twod_array.hpp"

/**
 * @brief Print a 2D array as ASCII art.
 *
 * @param os Output stream to print to.
 * @param multiplier Multiplier to scale the values of the 2D array before printing.
 * @param src 2D array to print.
 * @param src_height Height of the 2D array to print.
 * @param src_width Width of the 2D array to print.
 */
void print_twod_array_ascii_art(std::ostream &os, double multiplier,
                                double const src[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY], int src_height, int src_width);

#endif // ASCII_ART_HPP
