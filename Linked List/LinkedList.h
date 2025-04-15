#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListNode.h"
#include <iostream>
#include <initializer_list>

template <typename T>
class LinkedList
{
private:
    ListNode<T> *head;
    int size;
    void copyFrom(const LinkedList<T> &other);

public:
    // Iterator class
    class Iterator
    {
    private:
        ListNode<T> *node;

    public:
        Iterator(ListNode<T> *n) : node(n) {}
        Iterator &operator++()
        {
            node = node ? node->next : nullptr;
            return *this;
        }
        T &operator*() const { return node->val; }
        bool operator!=(const Iterator &other) const { return node != other.node; }
    };

    // Constructors and Destructor
    LinkedList();
    LinkedList(std::initializer_list<T> values);
    LinkedList(const LinkedList<T> &other);
    LinkedList(const T arr[], const int length);
    ~LinkedList();

    // Operators
    LinkedList<T> &operator=(const LinkedList<T> &other);

    // Methods
    void insertFront(const T &value);
    void insertBack(const T &value);
    void removeFront();
    void removeBack();
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    void insertAt(const T &value, int position);
    void popAt(int position);
    T getAt(int position) const;
    void clear();
    void print() const;

    // Iterator support
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

#include "LinkedList.tpp"

#endif