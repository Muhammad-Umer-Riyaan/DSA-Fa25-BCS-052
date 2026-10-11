/*
====================================================================
DSA Lab 3 Tasks - Doubly Linked Lists Implementation
====================================================================
*/

#include <iostream>
using namespace std;

// ==========================================
// LAB TASK 1: Reverse a Doubly Linked List
// ==========================================
namespace Task1 {
    struct Node {
        int data;
        Node* prev;
        Node* next;
        
        Node(int value) {
            data = value;
            prev = nullptr;
            next = nullptr;
        }
    };

    void insertAtEnd(Node*& head, int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }

    void reverseList(Node*& head) {
        Node* current = head;
        Node* temp = nullptr;
        
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev; 
        }
        
        if (temp != nullptr) {
            head = temp->prev;
        }
    }

    void displayList(Node* head) {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
}

// ==========================================
// LAB TASK 2: Swap Two Nodes in a Doubly Linked List
// ==========================================
namespace Task2 {
    struct Node {
        int data;
        Node* prev;
        Node* next;
        
        Node(int value) {
            data = value;
            prev = nullptr;
            next = nullptr;
        }
    };

    void insertAtEnd(Node*& head, int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }

    Node* searchNode(Node* head, int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void swapNodes(Node*& head, Node* first, Node* second) {
        if (first == nullptr || second == nullptr || first == second) {
            return;
        }
        
        if (second->next == first) {
            swapNodes(head, second, first);
            return;
        }
        
        if (first->next == second) {
            Node* before = first->prev;
            Node* after = second->next;
            
            if (before != nullptr) {
                before->next = second;
            } else {
                head = second;
            }
            second->prev = before;
            second->next = first;
            
            first->prev = second;
            first->next = after;
            
            if (after != nullptr) {
                after->prev = first;
            }
            return;
        }
        
        Node* firstPrev = first->prev;
        Node* firstNext = first->next;
        Node* secondPrev = second->prev;
        Node* secondNext = second->next;
        
        if (firstPrev != nullptr) {
            firstPrev->next = second;
        } else {
            head = second;
        }
        
        if (firstNext != nullptr) {
            firstNext->prev = second;
        }
        
        if (secondPrev != nullptr) {
            secondPrev->next = first;
        } else {
            head = first;
        }
        
        if (secondNext != nullptr) {
            secondNext->prev = first;
        }
        
        first->prev = secondPrev;
        first->next = secondNext;
        second->prev = firstPrev;
        second->next = firstNext;
    }

    void displayList(Node* head) {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
}

// ==========================================
// LAB TASK 3: Convert Singly to Doubly Linked List
// ==========================================
namespace Task3 {
    struct SNode {
        int data;
        SNode* next;
        SNode(int value) {
            data = value;
            next = nullptr;
        }
    };

    struct DNode {
        int data;
        DNode* prev;
        DNode* next;
        DNode(int value) {
            data = value;
            prev = nullptr;
            next = nullptr;
        }
    };

    void insertSingly(SNode*& head, int value) {
        SNode* newNode = new SNode(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        SNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    DNode* convertToDoubly(SNode* head) {
        DNode* doublyHead = nullptr;
        DNode* doublyTail = nullptr;
        SNode* current = head;
        
        while (current != nullptr) {
            DNode* newNode = new DNode(current->data);
            if (doublyHead == nullptr) {
                doublyHead = newNode;
                doublyTail = newNode;
            } else {
                doublyTail->next = newNode;
                newNode->prev = doublyTail;
                doublyTail = newNode;
            }
            current = current->next;
        }
        return doublyHead;
    }

    void displaySingly(SNode* head) {
        SNode* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void displayDoubly(DNode* head) {
        DNode* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
}

int main() {
    int choice;
    cout << "===========================================\n";
    cout << "       DSA LAB 3 - DOUBLY LINKED LISTS     \n";
    cout << "===========================================\n";
    cout << "1. Lab Task 1: Reverse a Doubly Linked List\n";
    cout << "2. Lab Task 2: Swap Two Nodes in Doubly Linked List\n";
    cout << "3. Lab Task 3: Convert Singly to Doubly Linked List\n";
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    
    if (choice == 1) {
        cout << "\n--- Running Lab Task 1 ---" << endl;
        Task1::Node* head = nullptr;
        int n, value;
        cout << "Enter the number of nodes: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Enter value: ";
            cin >> value;
            Task1::insertAtEnd(head, value);
        }
        cout << "Original list: ";
        Task1::displayList(head);
        Task1::reverseList(head);
        cout << "Reversed list: ";
        Task1::displayList(head);
    } 
    else if (choice == 2) {
        cout << "\n--- Running Lab Task 2 ---" << endl;
        Task2::Node* head = nullptr;
        int n, value, firstVal, secondVal;
        cout << "Enter the number of nodes: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Enter value: ";
            cin >> value;
            Task2::insertAtEnd(head, value);
        }
        cout << "Original list: ";
        Task2::displayList(head);
        cout << "Enter the first value to swap: ";
        cin >> firstVal;
        cout << "Enter the second value to swap: ";
        cin >> secondVal;
        
        Task2::Node* first = Task2::searchNode(head, firstVal);
        Task2::Node* second = Task2::searchNode(head, secondVal);
        
        if (first == nullptr || second == nullptr) {
            cout << "One or both values were not found." << endl;
        } else {
            Task2::swapNodes(head, first, second);
            cout << "List after swapping nodes: ";
            Task2::displayList(head);
        }
    } 
    else if (choice == 3) {
        cout << "\n--- Running Lab Task 3 ---" << endl;
        Task3::SNode* singlyHead = nullptr;
        int n, value;
        cout << "Enter the number of nodes: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Enter value: ";
            cin >> value;
            Task3::insertSingly(singlyHead, value);
        }
        cout << "Original singly linked list: ";
        Task3::displaySingly(singlyHead);
        
        Task3::DNode* doublyHead = Task3::convertToDoubly(singlyHead);
        cout << "Converted doubly linked list: ";
        Task3::displayDoubly(doublyHead);
    } 
    else {
        cout << "Invalid choice!" << endl;
    }
    
    return 0;
}
