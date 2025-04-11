#include <iostream>
#include <memory>
using namespace std;


struct Point
{
    /* data */
    float x, y;
    Point(float x, float y) : x(x), y(y) {}
};


int main()
{
    Point p1(1.0, 2.0);
    cout << p1.x << ' ' << p1.y << endl;
    Point *ptr = &p1;
    ptr -> x = 3.0;
    ptr -> y = 4.0;
    cout << p1.x << ' ' << p1.y << endl;
}

