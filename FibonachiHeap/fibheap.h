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

    Node() : parent(nullptr), child(nullptr), left(nullptr), right(nullptr),
        degree(0), mark(false){}
    Node(int key) : key(key), parent(nullptr), child(nullptr), left(nullptr),
        right(nullptr), degree(0), mark(false){}
};

class FibHeap {
    int size;
    Node* min;
    void unionLists(Node*, Node*);
    void consolidate();
    void linkHeap(Node*, Node*);\
    void decreaseKey(Node*, int);
    void cut(Node*, Node*);
    void cascadingCut(Node*);
public:
    FibHeap();
    Node* insert_key(int);\
    int getMin();
    Node* extractMin();
    void merge(FibHeap*);
    void deleteNode(Node*);
};

#endif // FIBHEAP_H
