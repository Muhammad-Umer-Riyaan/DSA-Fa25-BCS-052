/*
====================================================================
DSA Lab 4 Tasks - C++ Implementation
====================================================================
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// ==========================================
// LAB TASK 1: Delete nodes with even/odd values
// ==========================================
void deleteEvenNodes(Node*& head) {
    if (head == NULL) return;
    
    // Handle head nodes with even values
    while (head != NULL && head->data % 2 == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    
    if (head == NULL) return;
    
    Node* curr = head;
    while (curr->next != NULL) {
        if (curr->next->data % 2 == 0) {
            Node* del = curr->next;
            curr->next = curr->next->next;
            delete del;
        } else {
            curr = curr->next;
        }
    }
}

// ==========================================
// LAB TASK 2: Josephus Problem
// ==========================================
struct JosephusNode {
    int id;
    JosephusNode* next;
};

int josephus(int n, int k) {
    if (n == 1) return 1;
    
    JosephusNode* head = new JosephusNode{1, NULL};
    JosephusNode* prev = head;
    for (int i = 2; i <= n; i++) {
        JosephusNode* temp = new JosephusNode{i, NULL};
        prev->next = temp;
        prev = temp;
    }
    prev->next = head; // Circular link
    
    JosephusNode* curr = head;
    JosephusNode* p = prev;
    
    while (p->next != p) {
        for (int i = 1; i < k; i++) {
            p = curr;
            curr = curr->next;
        }
        p->next = curr->next;
        delete curr;
        curr = p->next;
    }
    
    int survivor = p->id;
    delete p;
    return survivor;
}

// ==========================================
// LAB TASK 3: Delete even positioned nodes
// ==========================================
void deleteEvenPositionedNodes(Node*& head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    
    Node* odd = head;
    Node* even = head->next;
    
    while (odd != NULL && even != NULL) {
        odd->next = even->next;
        delete even;
        
        odd = odd->next;
        if (odd != NULL) {
            even = odd->next;
        } else {
            even = NULL;
        }
    }
}

// Helper function to print list
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main() {
    cout << "=== LAB TASK 1: Delete Even/Odd Values ===" << endl;
    Node* head1 = NULL;
    Node* first = new Node{1, NULL}; head1 = first;
    Node* second = new Node{2, NULL}; first->next = second;
    Node* third = new Node{3, NULL}; second->next = third;
    Node* fourth = new Node{4, NULL}; third->next = fourth;
    Node* fifth = new Node{5, NULL}; fourth->next = fifth;
    
    cout << "Original List: ";
    printList(head1);
    deleteEvenNodes(head1);
    cout << "After Deleting Even Values: ";
    printList(head1);
    
    cout << "\n=== LAB TASK 2: Josephus Problem ===" << endl;
    int n = 5, k = 2;
    cout << "N = " << n << ", K = " << k << endl;
    int survivor = josephus(n, k);
    cout << "Survivor position: " << survivor << endl;
    
    cout << "\n=== LAB TASK 3: Delete Even Positioned Nodes ===" << endl;
    Node* head3 = NULL;
    Node* tail = NULL;
    for (int i = 1; i <= 6; i++) {
        Node* newNode = new Node{i * 10, NULL};
        if (head3 == NULL) {
            head3 = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    cout << "Original List: ";
    printList(head3);
    deleteEvenPositionedNodes(head3);
    cout << "After Deleting Even Positioned Nodes: ";
    printList(head3);
    
    return 0;
}
