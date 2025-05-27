#include<iostream>
#include "btree.h"
#include "btree.cpp"
#include<ctime>
using namespace std;

int main()
{
    srand(time(0));

    btree_node *head = nullptr;
    for (int i = 0 ; i < 10 ; i++)
    {
        btree_insert(head , rand());
    }
    pretty_print(head);
}

