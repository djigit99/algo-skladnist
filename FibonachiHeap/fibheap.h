#ifndef FIBHEAP_H
#define FIBHEAP_H

struct Node {
    int key;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    int degree;
    bool mark;

    Node() : parent(nullptr), child(nullptr), left(nullptr), right(nullptr) {}
    Node(int key) : key(key), parent(nullptr), child(nullptr), left(nullptr), right(nullptr) {}
};

class FibHeap {
    int size;
    Node* min;
    void unionLists(Node*, Node*);
    void consolidate();
    void linkHeap(Node*, Node*);\
public:
    FibHeap();
    void insert_key(int);\
    int getMin();
    Node* extractMin();
    void merge(FibHeap*);
};

#endif // FIBHEAP_H
