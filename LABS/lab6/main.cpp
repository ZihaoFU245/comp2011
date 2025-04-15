#include <cinttypes>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>

#include "ascii_art.hpp"
#include "twod_array.hpp"

/**
 * @brief Number to represent a garbage value for a 2D array size.
 */
int const TWOD_ARRAY_GARBAGE_SIZE{2011};

/**
 * @brief Read a 2D array and copy it.
 *
 * This tests Task 1.
 */
void main_copy_twod_array()
{
  std::cout << "Input a 2D array:\n";
  double src[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY];
  int src_height, src_width;
  read_2d_array(std::cout, std::cin, src, src_height, src_width);

  std::cout << "Copying the 2D array...\n";
  double dest[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY];
  int dest_height{TWOD_ARRAY_GARBAGE_SIZE}, dest_width{TWOD_ARRAY_GARBAGE_SIZE};
  copy_2d_array(dest, dest_height, dest_width, src, src_height, src_width);

  if (dest_height == TWOD_ARRAY_GARBAGE_SIZE || dest_width == TWOD_ARRAY_GARBAGE_SIZE)
  {
    std::cout << "Bad resulting 2D array size\n";
  }
  std::cout << (src_height == dest_height ? "Heights are the same\n" : "Heights are NOT the same\n")
            << (src_width == dest_width ? "Widths are the same\n" : "Widths are NOT the same\n");
  if (src_height != dest_height || src_width != dest_width)
  {
    std::cout << "Arrays are NOT the same\n";
    return;
  }

  bool same_array{true};
  int data_size{src_height * src_width};
  for (int idx{}; idx < data_size; ++idx)
  {
    std::imaxdiv_t coords{std::imaxdiv(idx, src_width)};
    if (src[coords.quot][coords.rem] != dest[coords.quot][coords.rem])
    {
      same_array = false;
      break;
    }
  }
  std::cout << (same_array ? "Arrays are the same\n" : "Arrays are NOT the same\n");
}

/**
 * @brief Read a 2D array and print it.
 *
 * This tests Task 2.
 */
void main_print_twod_array()
{
  std::cout << "Input a 2D array:\n";
  double array[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY];
  int height, width;
  read_2d_array(std::cout, std::cin, array, height, width);

  std::cout << "Formatted 2D array:\n";
  // print_2d_array(std::cout, array, height, width);
  print_2d_array(array, height, width);
}

/**
 * @brief Read two sizes of two 2D arrays in the same dimension and broadcast them.
 *
 * This tests Task 2.
 */
void main_broadcast_size()
{
  int left_size{};
  do
  {
    std::cout << "Left size in a dimension: ";
    std::cin >> left_size;
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input!\n";
      continue;
    }
    break;
  } while (true);

  int right_size{};
  do
  {
    std::cout << "Right size in the same dimension: ";
    std::cin >> right_size;
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input!\n";
      continue;
    }
    break;
  } while (true);

  int size{broadcast_size(left_size, right_size)};
  std::cout << "Broadcasted 2D array size in the same dimension: " << size << '\n'
            << (size == TWOD_ARRAY_INVALID_SIZE ? "The two sizes in the same dimension are NOT broadcastable\n" : "The two sizes in the same dimension are broadcastable\n");
}

/**
 * @brief Read two sizes of two 2D arrays and broadcast them.
 *
 * This tests Task 3.
 */
void main_broadcast_twod_size()
{
  int left_height{};
  do
  {
    std::cout << "Left height: ";
    std::cin >> left_height;
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input!\n";
      continue;
    }
    break;
  } while (true);
  int left_width{};
  do
  {
    std::cout << "Left width: ";
    std::cin >> left_width;
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input!\n";
      continue;
    }
    break;
  } while (true);

  int right_height{};
  do
  {
    std::cout << "Right height: ";
    std::cin >> right_height;
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input!\n";
      continue;
    }
    break;
  } while (true);
  int right_width{};
  do
  {
    std::cout << "Right width: ";
    std::cin >> right_width;
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input!\n";
      continue;
    }
    break;
  } while (true);

  int dest_height{TWOD_ARRAY_GARBAGE_SIZE}, dest_width{TWOD_ARRAY_GARBAGE_SIZE};
  bool broadcastable{broadcast_2d_size(dest_height, dest_width, left_height, left_width, right_height, right_width)};

  if (dest_height == TWOD_ARRAY_GARBAGE_SIZE || dest_width == TWOD_ARRAY_GARBAGE_SIZE)
  {
    std::cout << "Bad resulting 2D array size\n";
    broadcastable = false;
  }
  std::cout << "Broadcasted 2D array size: (" << dest_height << ", " << dest_width << ")\n"
            << (broadcastable ? "The two 2D arrays are broadcastable\n" : "The two 2D arrays are NOT broadcastable\n");
}

/**
 * @brief Read two 2D arrays and perform a specified arithmetic operation on them element-wise.
 * Optionally, it can also print out ASCII arts of the 2D arrays.
 *
 * This tests Task 4.
 */
void main_op_twod_array()
{
  char op_raw{};
  twod_array_ops op{};
  do
  {
    std::cout << "Input the arithmetic operation as one character (+-*/): ";
    std::cin >> op_raw;
    switch (op_raw)
    {
    case '+':
      op = twod_array_ops::ADD;
      break;
    case '-':
      op = twod_array_ops::SUBTRACT;
      break;
    case '*':
      op = twod_array_ops::MULTIPLY;
      break;
    case '/':
      op = twod_array_ops::DIVIDE;
      break;
    default:
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input!\n";
      continue;
    }
    break;
  } while (true);

  std::cout << "Input the left 2D array:\n";
  double left[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY];
  int left_height, left_width;
  read_2d_array(std::cout, std::cin, left, left_height, left_width);

  std::cout << "Input the right 2D array:\n";
  double right[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY];
  int right_height, right_width;
  read_2d_array(std::cout, std::cin, right, right_height, right_width);

  std::cout << "Calculating...\n";
  double dest[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY];
  int dest_height{TWOD_ARRAY_GARBAGE_SIZE}, dest_width{TWOD_ARRAY_GARBAGE_SIZE};
  bool broadcastable{op_2d_array(op, dest, dest_height, dest_width, left, left_height, left_width, right, right_height, right_width)};

  std::cout << "Resulting 2D array:\n";
  if (dest_height == TWOD_ARRAY_GARBAGE_SIZE || dest_width == TWOD_ARRAY_GARBAGE_SIZE)
  {
    std::cout << "Bad resulting 2D array size\n";
    broadcastable = false;
  }
  if (!broadcastable)
  {
    std::cout << "The two 2D arrays are NOT broadcastable\n";
    return;
  }
  // print_2d_array(std::cout, dest, dest_height, dest_width);
  print_2d_array(dest, dest_height, dest_width);

  char view_as_ascii_art{};
  do
  {
    std::cout << "Do you want to view the 2D arrays as ASCII arts? (n: no/y: 0-1/z: 0-255): ";
    std::cin >> view_as_ascii_art;
    switch (view_as_ascii_art)
    {
    case 'n':
    case 'N':
      view_as_ascii_art = 'n';
      break;
    case 'y':
    case 'Y':
      view_as_ascii_art = 'y';
      break;
    case 'z':
    case 'Z':
      view_as_ascii_art = 'z';
      break;
    default:
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input!\n";
      continue;
    }
    break;
  } while (true);

  if (view_as_ascii_art == 'n')
  {
    return;
  }

  double multiplier{view_as_ascii_art == 'z' ? (1. / 255.) : 1};
  std::cout << "Left 2D array:\n";
  print_twod_array_ascii_art(std::cout, multiplier, left, left_height, left_width);
  std::cout << "Right 2D array:\n";
  print_twod_array_ascii_art(std::cout, multiplier, right, right_height, right_width);
  std::cout << "Resulting 2D array:\n";
  print_twod_array_ascii_art(std::cout, multiplier, dest, dest_height, dest_width);
}

/**
 * @brief Main program.
 *
 * @return int Always 0 for grading purposes.
 */
int main()
{
  std::cout << std::fixed << std::showpoint << std::setprecision(6); // Always show 6 decimal places.

  int option{};
  do
  {
    std::cout << "Welcome to 2D array calculator! Choose an option from below:\n"
                 "1. Copy a 2D array\n"
                 "2. Print a 2D array\n"
                 "3. Broadcast two sizes in the same dimension\n"
                 "4. Broadcast two 2D arrays and get the resulting 2D array size\n"
                 "5. Perform arithmetic operations on two 2D arrays (and view them as ASCII arts)\n"
                 "Your option: ";
    std::cin >> option;
    if (!std::cin || option < 1 || option > 5)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input!\n";
      continue;
    }
    break;
  } while (true);

  switch (option)
  {
  case 1:
    main_copy_twod_array();
    break;
  case 2:
    main_print_twod_array();
    break;
  case 3:
    main_broadcast_size();
    break;
  case 4:
    main_broadcast_twod_size();
    break;
  case 5:
    main_op_twod_array();
    break;
  default:
    std::cout << "Unexpected code\n";
  }

  return 0;
}
