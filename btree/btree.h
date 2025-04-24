#ifndef BTREE_H
#define BTREE_H

#include <iostream>
using namespace std;

struct btree_node
{
    int data;
    btree_node *left;
    btree_node *right;
};

#endif