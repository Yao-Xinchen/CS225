#include <iostream>
using namespace std;


struct node
{
    int val;
    node *prev;
    node *next;
};


class List
{
public:
    node *head;

    List()
    {
        head = nullptr;
    }

    ~List()
    {
        node *temp = head;
        while (head != nullptr)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
        head = nullptr;
    }

    void insert(int val)
    {
        if (head == nullptr)
        {
            head = new node;
            head->val = val;
            head->next = nullptr;
            head->prev = nullptr;
        } else
        {
            node *temp = new node;
            temp->val = val;
            temp->next = head;
            head->prev = temp;
            temp->prev = nullptr;
            head = temp;
        }
    }

    void oddprint() const
    {
        cout << endl;
        node *temp = head;
        while (temp != nullptr && temp->next != nullptr)
        {
            temp = temp->next->next;
            if (temp != nullptr)
                cout << temp->val << " ";
        }
        cout << endl;
    }
};


/*
*	This function should print a linked list in a odd fashion (fix it so it doesn't segfault in a reasonable way)
*
*/

int main()
{
    List list;

    for (int i = 0; i < 10; ++i)
    {
        list.insert(i);
    }
    list.oddprint();
}
