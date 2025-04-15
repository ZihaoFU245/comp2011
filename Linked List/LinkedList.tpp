#include "LinkedList.h"
#include <iostream>
using namespace std;

// Constructors and Destructor
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> values) : head(nullptr), size(0)
{
    for (const T &value : values)
    {
        insertBack(value);
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other) : head(nullptr), size(0)
{
    copyFrom(other);
}

template <typename T>
LinkedList<T>::LinkedList(const T arr[], const int length) : head(nullptr), size(0)
{
    for (int i = 0; i < length; i++)
    {
        insertBack(arr[i]);
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    ListNode<T> *current = head;
    while (current != nullptr)
    {
        ListNode<T> *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
}

// Operators
template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (this != &other)
    {
        while (head != nullptr)
        {
            ListNode<T> *next = head->next;
            delete head;
            head = next;
        }
        size = 0;
        copyFrom(other);
    }
    return *this;
}

// Methods
template <typename T>
void LinkedList<T>::copyFrom(const LinkedList<T> &other)
{
    for (ListNode<T> *current = other.head; current != nullptr; current = current->next)
    {
        insertBack(current->val);
    }
}

template <typename T>
void LinkedList<T>::insertFront(const T &value)
{
    ListNode<T> *new_node = new ListNode<T>(value);
    new_node->next = head;
    head = new_node;
    size++;
}

template <typename T>
void LinkedList<T>::insertBack(const T &value)
{
    ListNode<T> *new_node = new ListNode<T>(value);
    if (head == nullptr)
    {
        head = new_node;
    }
    else
    {
        ListNode<T> *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    size++;
}

template <typename T>
void LinkedList<T>::removeFront()
{
    if (head == nullptr)
        return;
    ListNode<T> *new_head = head->next;
    delete head;
    head = new_head;
    size--;
}

template <typename T>
void LinkedList<T>::removeBack()
{
    if (head == nullptr)
        return;
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        size--;
        return;
    }
    ListNode<T> *current = head;
    while (current->next->next != nullptr)
    {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
    size--;
}

template <typename T>
void LinkedList<T>::insertAt(const T &value, int index)
{
    if (index < 0 || index > size)
    {
        cerr << "Index out of bounds\n";
        return;
    }
    if (index == 0)
        insertFront(value);
    else if (index == size)
        insertBack(value);
    else
    {
        ListNode<T> *new_node = new ListNode<T>(value);
        ListNode<T> *current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        size++;
    }
}

template <typename T>
void LinkedList<T>::popAt(int index)
{
    if (index < 0 || index >= size)
    {
        cerr << "Index out of range\n";
        return;
    }
    if (index == 0)
    {
        removeFront();
    }
    else if (index == size - 1 || index == -1)
    {
        removeBack();
    }
    else
    {
        ListNode<T> *current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        ListNode<T> *next_node = current->next->next;
        delete current->next;
        current->next = next_node;
        size--;
    }
}

template <typename T>
T LinkedList<T>::getAt(int index) const
{
    if (index < 0 || index >= size)
    {
        cerr << "Index out of range\n";
        return T();
    }
    ListNode<T> *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->val;
}

template <typename T>
void LinkedList<T>::clear()
{
    this->~LinkedList();
}

template <typename T>
void LinkedList<T>::print() const
{
    cout << '[';
    ListNode<T> *current = head;
    while (current != nullptr)
    {
        cout << current->val;
        if (current->next != nullptr)
        {
            cout << ' ';
        }
        current = current->next;
    }
    cout << ']';
    cout << '\n';
}
