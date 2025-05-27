#include "ascii_art.hpp"

#include <cinttypes>
#include <cstddef>
#include <iostream>

/**
 * @brief ASCII art characters, in order of ascending "brightness".
 *
 * @note Credits to https://stackoverflow.com/a/74186686.
 */
char const ASCII_ART_CHARACTERS[]{" `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@"};
/**
 * @brief Number of ASCII art characters.
 */
int const ASCII_ART_CHARACTER_COUNT{sizeof(ASCII_ART_CHARACTERS) / sizeof(*ASCII_ART_CHARACTERS) - 1};
/**
 * @brief ASCII art character "brightness".
 *
 * @note Credits to https://stackoverflow.com/a/74186686.
 */
double const ASCII_ART_CHARACTER_THRESHOLDS[ASCII_ART_CHARACTER_COUNT]{0, 0.0751, 0.0829, 0.0848, 0.1227, 0.1403, 0.1559, 0.185, 0.2183, 0.2417, 0.2571, 0.2852, 0.2902, 0.2919, 0.3099, 0.3192, 0.3232, 0.3294, 0.3384, 0.3609, 0.3619, 0.3667, 0.3737, 0.3747, 0.3838, 0.3921, 0.396, 0.3984, 0.3993, 0.4075, 0.4091, 0.4101, 0.42, 0.423, 0.4247, 0.4274, 0.4293, 0.4328, 0.4382, 0.4385, 0.442, 0.4473, 0.4477, 0.4503, 0.4562, 0.458, 0.461, 0.4638, 0.4667, 0.4686, 0.4693, 0.4703, 0.4833, 0.4881, 0.4944, 0.4953, 0.4992, 0.5509, 0.5567, 0.5569, 0.5591, 0.5602, 0.5602, 0.565, 0.5776, 0.5777, 0.5818, 0.587, 0.5972, 0.5999, 0.6043, 0.6049, 0.6093, 0.6099, 0.6465, 0.6561, 0.6595, 0.6631, 0.6714, 0.6759, 0.6809, 0.6816, 0.6925, 0.7039, 0.7086, 0.7235, 0.7302, 0.7332, 0.7602, 0.7834, 0.8037, 0.9999};

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
                                double const src[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY], int src_height, int src_width)
{
  int data_size{src_height * src_width};
  for (int idx{}; idx < data_size; ++idx)
  {
    std::imaxdiv_t coords{std::imaxdiv(idx, src_width)};
    double value{multiplier * src[coords.quot][coords.rem]};

    int char_idx{1};
    for (; char_idx < ASCII_ART_CHARACTER_COUNT; ++char_idx)
    {
      if (value < ASCII_ART_CHARACTER_THRESHOLDS[char_idx])
      {
        break;
      }
    }
    char value_char{ASCII_ART_CHARACTERS[char_idx - 1]};
    os << value_char << value_char;

    if (static_cast<decltype(src_width)>(coords.rem) + 1 == src_width)
    {
      os << '\n';
    }
  }
}
