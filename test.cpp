#include <iostream>
#include <memory>
using namespace std;

struct ll_node
{
    int data;
    ll_node *next = nullptr;
    ll_node(int d) : data(d), next(nullptr) {}
    ll_node *self() { return this; }
};

void print_list(ll_node &head)
{
    ll_node *current = &head;
    while (current != nullptr)
    {
        cout << current->data << " -> ";
        current = current->next;
    }
}

void delete_list(ll_node *&head)
{
    ll_node *current = head;
    while (current != nullptr)
    {
        ll_node *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

ll_node create_list(int src[], int size)
{
    if (size <= 0)
        return ll_node(0); // Return a dummy node for invalid size

    ll_node head(src[0]);
    ll_node *current = &head;

    for (int i = 1; i < size; i++)
    {
        ll_node *next = new ll_node(src[i]);
        current->next = next;
        current = next;
    }
    return head;
}



int main()
{
    int arr[] = {1, 2, 3, 4, 5};

    ll_node *head = new ll_node(create_list(arr, 5));
    print_list(*head);

    delete_list(head);
    return 0;
}
