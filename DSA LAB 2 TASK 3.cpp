#include <iostream>
#include <stack>
#include <vector>
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

    // Returns the index of every node whose data matches 'value'.
    // If the value doesn't appear at all, the returned vector is empty.
    vector<int> findOccurrences(int value)
    {
        vector<int> positions;
        Node *temp = head;
        int index = 0;

        while (temp != nullptr)
        {
            if (temp->data == value)
                positions.push_back(index); // record where we found it, keep going

            temp = temp->next;
            index++;
        }

        return positions;
    }

    static LinkedList mergeSortedLists(LinkedList &list1, LinkedList &list2)
    {
        LinkedList merged;
        Node *p1 = list1.head;
        Node *p2 = list2.head;

        while (p1 != nullptr && p2 != nullptr)
        {
            if (p1->data <= p2->data)
            {
                merged.insertAtEnd(p1->data);
                p1 = p1->next;
            }
            else
            {
                merged.insertAtEnd(p2->data);
                p2 = p2->next;
            }
        }

        while (p1 != nullptr)
        {
            merged.insertAtEnd(p1->data);
            p1 = p1->next;
        }

        while (p2 != nullptr)
        {
            merged.insertAtEnd(p2->data);
            p2 = p2->next;
        }

        return merged;
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

    LinkedList listA;
    listA.insertAtEnd(10);
    listA.insertAtEnd(30);
    listA.insertAtEnd(50);
    listA.insertAtEnd(70);

    LinkedList listB;
    listB.insertAtEnd(5);
    listB.insertAtEnd(20);
    listB.insertAtEnd(40);
    listB.insertAtEnd(60);
    listB.insertAtEnd(80);

    cout << "List A:               ";
    listA.displayForward();

    cout << "List B:               ";
    listB.displayForward();

    LinkedList merged = LinkedList::mergeSortedLists(listA, listB);

    cout << "Merged List:          ";
    merged.displayForward();

    LinkedList listC;
    listC.insertAtEnd(15);
    listC.insertAtEnd(25);
    listC.insertAtEnd(15);
    listC.insertAtEnd(35);
    listC.insertAtEnd(15);
    listC.insertAtEnd(45);

    cout << "List C:               ";
    listC.displayForward();

    int searchValue = 15;
    vector<int> positions = listC.findOccurrences(searchValue);

    if (positions.empty())
    {
        cout << "Value " << searchValue << " not found in List C." << endl;
    }
    else
    {
        cout << "Value " << searchValue << " found at position(s): ";
        for (int pos : positions)
            cout << pos << " ";
        cout << endl;
    }

    return 0;
}
