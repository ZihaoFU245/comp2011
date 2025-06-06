#include "twod_array.hpp"

#include <cinttypes>
#include <cstddef>
#include <iostream>
#include <limits>

/**
 * @brief Read a 2D array from an input.
 *
 * @param os Output to print prompt messages.
 * @param is Input to read a 2D array from.
 * @param dest 2D array to store the read input.
 * @param dest_height Reference to a `double` to store the 2D array height.
 * @param dest_width Reference to a `double` to store the 2D array width.
 */
void read_2d_array(std::ostream &os, std::istream &is,
                   double dest[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY], int &dest_height, int &dest_width)
{
    dest_height = TWOD_ARRAY_INVALID_SIZE;
    do
    {
        os << "2D array height: ";
        is >> dest_height;
        if (TWOD_ARRAY_INVALID_SIZE == dest_height || dest_height > TWOD_ARRAY_CAPACITY)
        {
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            os << "Invalid input!\n";
            continue;
        }
        break;
    } while (true);

    dest_width = TWOD_ARRAY_INVALID_SIZE;
    do
    {
        os << "2D array width: ";
        is >> dest_width;
        if (TWOD_ARRAY_INVALID_SIZE == dest_width || dest_width > TWOD_ARRAY_CAPACITY)
        {
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            os << "Invalid input!\n";
            continue;
        }
        break;
    } while (true);

    int data_size{dest_height * dest_width};
    bool success{};
    do
    {
        os << "2D array data (" << data_size << " numbers expected):\n";
        success = true;
        for (int idx{}; idx < data_size; ++idx)
        {
            std::imaxdiv_t coords{std::imaxdiv(idx, dest_width)};
            is >> dest[coords.quot][coords.rem];
            if (!is)
            {
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                os << "Invalid input!\n";
                success = false;
                break;
            }
        }
    } while (!success);
}

/**
 * @brief Copy a 2D array from another 2D array.
 *
 * @note Task 1: Implement this function.
 *
 * All 2D arrays are properly allocated and their sizes are valid.
 * The `src` 2D array contains initialized data within the specified height and width.
 * You do not need to set values of `dest` that are outside the specified height and width.
 *
 * To copy the 2D array, you can use two `for`-loops, the inner loop being inside the other loop.
 * The outer loop iterates through each row from 0 (inclusive) to height (exclusive).
 * The inner loop iterates through each cell in a row from 0 (inclusive) to width (exclusive)
 * and copies the value in that cell from `src` to `dest`.
 *
 * Remember that 2D arrays have row-major order, so you access a cell using `array[y][x]`.
 * Also remember to copy the 2D array height and width as well.
 *
 * @param dest 2D array to be copied to.
 * @param dest_height Reference to a variable to store the 2D array height.
 * @param dest_width Reference to a variable to store the 2D array width.
 * @param src 2D array to be copied from.
 * @param src_height Height of the 2D array to be copied from.
 * @param src_width Width of the 2D array to be copied from.
 */
void copy_2d_array(double dest[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY], int &dest_height, int &dest_width,
                   double const src[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY], int src_height, int src_width)
{
    // TODO: Task 1
    for (int row = 0; row < src_height; row++)
    {
        for (int col = 0; col < src_width; col++)
        {
            dest[row][col] = src[row][col];
        }
    }
    dest_height = src_height;
    dest_width = src_width;
}

/**
 * @brief Print a 2D array to `std::cout`.
 *
 * @param src 2D array to be printed.
 * @param src_height Height of the 2D array to be printed.
 * @param src_width Width of the 2D array to be printed.
 */
void print_2d_array(double const src[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY], int src_height, int src_width)
{
    // Do NOT change the code below!
    if (src_height == TWOD_ARRAY_INVALID_SIZE || src_width == TWOD_ARRAY_INVALID_SIZE)
    {
        std::cout << "Invalid array!\n";
        return;
    }

    std::cout << '[';
    for (int yy{}; yy < src_height; ++yy)
    {
        std::cout << (yy > 0 ? " [" : "[");
        for (int xx{}; xx < src_width; ++xx)
        {
            if (xx > 0)
                std::cout << ' ';
            std::cout << src[yy][xx];
        }
        std::cout << (yy + 1 < src_height ? "]\n" : "]");
    }
    std::cout << "]\n";
}

/**
 * @brief Broadcast two sizes from two 2D arrays in the same dimension.
 *
 * @note Task 2: Implement this function.
 *
 * All sizes are valid. That means you do not need to handle invalid sizes.
 *
 * To broadcast two sizes in the same dimension,
 * first check if the two sizes are the same. If so, that is the broadcasted size.
 * Otherwise, check if one of the sizes is 1. If so, the other size is the broadcasted size.
 * (What if both sizes are 1?)
 * Otherwise, these two sizes cannot be broadcasted. Return `TWOD_ARRAY_INVALID_SIZE`.
 * (Another thing to consider: What if one of the sizes is 0? Or both are 0?)
 *
 * @param left Size in a dimension of the left 2D array.
 * @param right Size in the same dimension of the right 2D array.
 * @return int Broadcasted size for the two 2D arrays in that dimension.
 *
 * If they cannot be broadcasted, `TWOD_ARRAY_INVALID_SIZE` is returned.
 */
int broadcast_size(int left, int right)
{
    // TODO: Task 2
    if (left == right)
        return left;

    if (left == 1 || right == 1)
        return left == 1 ? right : left;

    return TWOD_ARRAY_INVALID_SIZE;
}

/**
 * @brief Broadcast two 2D arrays and get its resulting size. Also checks if the two 2D arrays can be broadcasted.
 *
 * @note Task 3: Implement this function.
 *
 * All 2D array sizes are valid. That means you do not need to handle invalid sizes.abort
 *
 * For two 2D array to be broadcastable, all of their dimensions, i.e. height and width, are broadcastable.
 * If the two 2D arrays are broadcastable, write the broadcasted 2D array size to `dest_height` and `dest_width`.
 * Otherwise, write `TWOD_ARRAY_INVALID_SIZE` to both `dest_height` and `dest_width`.
 *
 * Remember to also return a `bool` representing if the two 2D arrays are broadcastable.
 *
 * You are recommended to use `broadcast_size` to implement this function.
 *
 * @param dest_height Reference to a variable to store the 2D array height.
 * @param dest_width Reference to a variable to store the 2D array width.
 * @param src_left_height Height of the left 2D array.
 * @param src_left_width Width of the left 2D array.
 * @param src_right_height Height of the right 2D array.
 * @param src_right_width Width of the right 2D array.
 * @return true If the two 2D arrays can be broadcasted.
 * @return false If the two 2D arrays cannot be broadcasted.
 */
bool broadcast_2d_size(int &dest_height, int &dest_width,
                       int src_left_height, int src_left_width,
                       int src_right_height, int src_right_width)
{
    // check condition first
    int left_size = broadcast_size(src_left_height, src_right_height);
    int right_size = broadcast_size(src_left_width, src_right_width);

    if (left_size != TWOD_ARRAY_INVALID_SIZE && right_size != TWOD_ARRAY_INVALID_SIZE)
    {
        // copy to dest and return true
        dest_height = left_size;
        dest_width = right_size;
        return true;
    }
    dest_height = dest_width = TWOD_ARRAY_INVALID_SIZE;

    return false;
}

/**
 * @brief Perform an arithmetic operation on two 2D arrays element-wise. The two 2D arrays are broadcasted if possible.
 *
 * @note Task 4: Implement this function.
 *
 * Do not be overwhelmed by the number of parameters!
 * Try to group a 2D array and its sizes as a single parameter in your mind,
 * e.g. consider `dest`, `dest_height`, `dest_width` as a single parameter.
 * Later, when you learn structs, you can understand how structs
 * can group parameters together to make the function more readable.
 *
 * All 2D arrays are properly allocated and their sizes are valid.
 * The `src_left` and `src_right` 2D arrays contain initialized data within the specified height and width.
 * You do not need to set values of `dest` that are outside the specified height and width.
 *
 * To implement this function, check if the two 2D arrays can be broadcasted.
 * If not, write `TWOD_ARRAY_INVALID_SIZE` to both `dest_height` and `dest_width`,
 * and return `false`. You are recommended to use `broadcast_2d_size`.
 *
 * Otherwise, perform the arithmetic operation specified by `op` element-wise,
 * broadcasting as needed. The lab introduction should give you an idea how broadcasting works.
 * A hint for calculating the indices when implementing broadcasting:
 * Consider iterating through each cell of `dest` first, using two nested loops.
 * You should know the height and width of `dest` fromm `broadcast_2d_size`.
 * Then, consider the current coordinate `dest[y][x]` of `dest`.
 * You can calculate the two corresponding coordinates in `src_left` and `src_right`
 * from the current coordinate in `dest`. Make use of the fact that broadcasting is
 * only relevant when the size of a dimension in one of the two 2D arrays is 1.
 * After calculating the two correspondng coordinates,
 * simply perform the requested arithmetic operation using the three coordinates above.
 *
 * The arithmetic operations are to be performed as follows:
 *
 * - `ADD` (+): `dest = left + right`
 *
 * - `SUBTRACT` (-): `dest = left - right`
 *
 * - `MULTIPLY` (*): `dest = left * right`
 *
 * - `DIVIDE` (/): If `right` is 0, `dest = 0`. Otherwise, `dest = left / right`.
 *
 * Remember that 2D arrays have row-major order, so you access a cell using `array[y][x]`.
 * Also remember to set the result 2D array height and width as well.
 *
 * Finally, return `true` to indicate that broadcasting and
 * the above element-wise arithmetic operation is successful.
 *
 * @param op Arithmetic operation to be performed on two 2D arrays.
 * @param dest 2D array to store the calculation result.
 * @param dest_height Reference to a variable to store the 2D array height.
 * @param dest_width Reference to a variable to store the 2D array width.
 * @param src_left 2D array on the left of the arithmetic operation.
 * @param src_left_height Height of the left 2D array.
 * @param src_left_width Width of the left 2D array.
 * @param src_right 2D array on the right of the arithmetic operation.
 * @param src_right_height Height of the right 2D array.
 * @param src_right_width Width of the right 2D array.
 * @return true If the two 2D arrays can be broadcasted and the arithmetic operation succeeded.
 * @return false If the two 2D arrays cannot be broadcasted.
 */
bool op_2d_array(twod_array_ops op,
                 double dest[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY], int &dest_height, int &dest_width,
                 double const src_left[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY], int src_left_height, int src_left_width,
                 double const src_right[TWOD_ARRAY_CAPACITY][TWOD_ARRAY_CAPACITY], int src_right_height, int src_right_width)
{
    // TODO: Task 4
    // Task 1 : check if can be broadcasted
    bool IsBroadcatable = broadcast_2d_size(dest_height,
                                            dest_width,
                                            src_left_height,
                                            src_left_width,
                                            src_right_height,
                                            src_right_width);

    if (IsBroadcatable == true)
    {
        // task2 : operations
        switch (op)
        {
        case ADD:
            for (int row = 0; row < dest_height; row++)
            {
                for (int col = 0; col < dest_width; col++)
                {
                    // calc the index
                    int left_row = (src_left_height == 1) ? 0 : row;
                    int left_col = (src_left_width == 1) ? 0 : col;
                    int right_row = (src_right_height == 1) ? 0 : row;
                    int right_col = (src_right_width == 1) ? 0 : col;

                    dest[row][col] = src_left[left_row][left_col] + src_right[right_row][right_col];
                }
            }
            break;
        case SUBTRACT:
            for (int row = 0; row < dest_height; row++)
            {
                for (int col = 0; col < dest_width; col++)
                {
                    // calc the index
                    int left_row = (src_left_height == 1) ? 0 : row;
                    int left_col = (src_left_width == 1) ? 0 : col;
                    int right_row = (src_right_height == 1) ? 0 : row;
                    int right_col = (src_right_width == 1) ? 0 : col;

                    dest[row][col] = src_left[left_row][left_col] - src_right[right_row][right_col];
                }
            }
            break;
        case MULTIPLY:
            // TODO
            for (int row = 0; row < dest_height; row++)
            {
                for (int col = 0; col < dest_width; col++)
                {
                    // calc the index
                    int left_row = (src_left_height == 1) ? 0 : row;
                    int left_col = (src_left_width == 1) ? 0 : col;
                    int right_row = (src_right_height == 1) ? 0 : row;
                    int right_col = (src_right_width == 1) ? 0 : col;

                    dest[row][col] = src_left[left_row][left_col] * src_right[right_row][right_col];
                }
            }
            break;
        case DIVIDE:
            // TODO
            for (int row = 0; row < dest_height; row++)
            {
                for (int col = 0; col < dest_width; col++)
                {
                    // calc the index
                    int left_row = (src_left_height == 1) ? 0 : row;
                    int left_col = (src_left_width == 1) ? 0 : col;
                    int right_row = (src_right_height == 1) ? 0 : row;
                    int right_col = (src_right_width == 1) ? 0 : col;

                    // If `right` is 0, `dest = 0`. Otherwise, `dest = left / right`.
                    if (src_right[right_row][right_col] == 0)
                    {
                        dest[row][col] = 0;
                        continue;
                    }
                    dest[row][col] = src_left[left_row][left_col] / src_right[right_row][right_col];
                }
            }
            break;
        default:
            break;
        }

        return true;
    }

    return false;
}
