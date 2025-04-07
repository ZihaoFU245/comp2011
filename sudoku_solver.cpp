#include <vector>
#include <iostream>
#include <limits>
using namespace std;

vector<vector<int>> get_unsolved_sudoku()
{
    vector<vector<int>> sudoku(9, vector<int>(9, 0));

    int t;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << "input the number at " << i + 1 << " " << j + 1 << endl;
            while (!(cin >> t) || t < 0 || t > 9)
            {
                cin.clear();                                         // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please enter a number between 0 and 9." << endl;
            }
            sudoku[i][j] = t;
        }
    }

    return sudoku;
}

bool is_valid(vector<vector<int>>& board, int row, int col, int num)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[row][i] == num || board[i][col] == num || board[row - row % 3 + i / 3][col - col % 3 + i % 3] == num)
        {
            return false;
        }
    }
    return true;
}

bool solve_sudoku(vector<vector<int>>& board)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (board[row][col] == 0)
            {
                for (int num = 1; num <= 9; num++)
                {
                    if (is_valid(board, row, col, num))
                    {
                        board[row][col] = num;
                        if (solve_sudoku(board))
                        {
                            return true;
                        }
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main()
{
    vector<vector<int>> sudoku = get_unsolved_sudoku();
    if (solve_sudoku(sudoku))
    {
        cout << "Solved Sudoku:" << endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cout << sudoku[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "No solution exists." << endl;
    }
    return 0;
}