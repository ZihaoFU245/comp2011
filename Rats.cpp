#include <iostream>
#include <string>
using namespace std;

class RATS
{
private:
    int size;
    const string unit = "*";

public:
    RATS(int s = 7) : size(s) {} // constructor

    void change_size(int i)
    {
        size = i;
    }

    void FAT_RAT()
    {
        string line = "";
        if (size < 1)
        {
            return;
        }
        int layer = 1;
        do
        {
            line += unit;
            cout << line << endl;
            layer++;
        } while (layer <= size);
    }

    void HOLLOW_RAT()
    {
        string line = "";
        if (size < 1)
        {
            return;
        }
        int layer = 1;
        do
        {
            line += unit;
            if (line.size() >= 2)
            {
                int size = line.size();
                string replace = "";
                for (int i = 0; i <= size - 2; ++i)
                {
                    replace.append(" ");
                }
                line.replace(1, line.size() - 2, replace);
            }
            cout << line << endl;
            layer++;
        } while (layer <= size);
    }

    void UPSIDE_DOWN_RAT()
    {
        string line = "";
        for (int i = 0; i < size; ++i)
        {
            line.append(unit);
        }
        int layer = size;
        while(layer >= 0) {
            cout << line << endl;
            line.pop_back();
            --layer;
        }
    }
};

int main()
{
    RATS sth = RATS();
    sth.FAT_RAT();
    cout << '\n';
    sth.HOLLOW_RAT();
    cout << '\n';
    sth.UPSIDE_DOWN_RAT();
    return 0;
}
