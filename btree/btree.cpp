#include "btree.h"
#include <iostream>
#include <string>
using namespace std;

btree_node *get_new_node(int value = 0)
{
    btree_node *node = new btree_node;
    node->data = value;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

void btree_insert(btree_node *&head, int value)
{
    // for head == nullptr case
    if (head == nullptr)
    {
        head = get_new_node(value);
        return;
    }

    if (value <= head->data)
    {
        if (head->left == nullptr)
        {
            head->left = get_new_node(value);
            return;
        }
        btree_insert(head->left, value);
    }
    else
    {
        if (head->right == nullptr)
        {
            head->right = get_new_node(value);
            return;
        }
        btree_insert(head->right, value);
    }
}

bool search_value(const btree_node *head, int value)
{
    if (head == nullptr)
        return false;

    if (value == head->data)
    {
        return true;
    }

    if (value > head->data)
    {
        return search_value(head->right, value);
    }
    else
    {
        return search_value(head->left, value);
    }
}

void pretty_print(const btree_node *node,
                  const std::string &prefix = "",
                  bool isLeft = false)
{
    if (!node)
        return;

    std::cout << prefix;
    std::cout << (isLeft ? "├── " : "└── ");
    std::cout << node->data << "\n";

    // extend prefix for children
    std::string childPrefix = prefix + (isLeft ? "│   " : "    ");
    pretty_print(node->left, childPrefix, true);
    pretty_print(node->right, childPrefix, false);
}