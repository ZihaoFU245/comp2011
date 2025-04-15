#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

int main()
{
    // Demo with int
    int arr[] = {1, 3, 5, 7, 9};
    LinkedList<int> list(arr, 5);
    list.print();

    list.popAt(3);
    list.print();

    int a = list.getAt(3);
    cout << "Element at index 3: " << a << endl;

    // Iterator demo (range-based for loop)
    cout << "Iterating with range-based for loop: ";
    for (auto& val : list) {
        cout << val << ' ';
    }
    cout << endl;

    // Demo with std::string
    LinkedList<string> strList = {"hello", "world", "linked", "list"};
    strList.print();
    cout << "First element: " << strList.getAt(0) << endl;
    cout << "Iterating string list: ";
    for (auto& s : strList) {
        cout << s << ' ';
    }
    cout << endl;
}