#ifndef LISTNODE_H
#define LISTNODE_H

template <typename T>
struct ListNode
{
    T val;
    ListNode *next;

    // constructor
    ListNode(const T &x) : val(x), next(nullptr) {}
};

#endif // LISTNODE_H
