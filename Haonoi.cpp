#include <iostream>
#include <fstream>
using namespace std;

ofstream out("solution.txt");

void hanoi(int num_disc, char rod_A, char rod_B, char rod_C)
{
    if (num_disc <= 0)
    {
        return;
    }
    hanoi(num_disc - 1, rod_A, rod_C, rod_B);
    out << "Move from "
        << rod_A << " to " << rod_C << endl;

    hanoi(num_disc - 1, rod_B, rod_A, rod_C);
}

int main()
{
    int n = 4;
    char A = 'A', B = 'B', C = 'C';
    hanoi(n, A, B, C);
    out.close();
    return 0;
}