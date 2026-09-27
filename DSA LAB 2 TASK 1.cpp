#include <iostream>
#include <stack>
using namespace std;

// ---------------- Node ----------------
struct Node
{
    int data;
    Node *next;
    Node(int value) : data(value), next(nullptr) {}
};

// ---------------- Singly Linked List ----------------
class LinkedList
{
private:
    Node *head;

    // Private recursive helper (needs a Node* parameter to recurse with,
    // which we don't want to expose in the public interface)
    void displayReverseRecursiveHelper(Node *node)
    {
        if (node == nullptr) // base case: went past the last node
            return;

        displayReverseRecursiveHelper(node->next); // go deeper FIRST (towards the tail)
        cout << node->data << " ";                  // print AFTER the recursive call returns
    }

public:
    LinkedList() : head(nullptr) {}

    void insertAtEnd(int value)
    {
        Node *newNode = new Node(value);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }

        Node *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }

    void displayForward()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // ---------------- Reverse Display: Recursive Approach ----------------
    void displayReverseRecursive()
    {
        displayReverseRecursiveHelper(head);
        cout << endl;
    }

    // ---------------- Reverse Display: Iterative (Loop) Approach ----------------
    // A singly linked list has no 'prev' pointer, so a plain loop can't walk
    // backwards on its own. We use an explicit stack: push every value while
    // moving forward, then pop them all off (LIFO order = reverse order).
    void displayReverseIterative()
    {
        stack<int> s;
        Node *temp = head;

        while (temp != nullptr)
        {
            s.push(temp->data);
            temp = temp->next;
        }

        while (!s.empty())
        {
            cout << s.top() << " ";
            s.pop();
        }
        cout << endl;
    }

    ~LinkedList()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main()
{
    LinkedList list;
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    list.insertAtEnd(50);

    cout << "Forward Display:      ";
    list.displayForward();

    cout << "Reverse (Recursive):  ";
    list.displayReverseRecursive();

    cout << "Reverse (Iterative):  ";
    list.displayReverseIterative();

    return 0;
}
