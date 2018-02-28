#include "fibheap.h"

FibHeap::FibHeap() {
    size = 0;
    min = nullptr;
}
void FibHeap::insert_key(int key) {
    Node* newNode = new Node(key);
    if (!size) {
        min = newNode;
        min->left = newNode;
        min->right = newNode;
    } else {
        Node* prevLeft = min->left;
        min->left = newNode;
        newNode->right = min;
        newNode->left = prevLeft;
        prevLeft->right = newNode;
    }
    if (newNode->key < min->key) {
        min = newNode;
    }
    size++;
}
int FibHeap::getMin() {
    return min->key;
}
void FibHeap::unionLists(Node *first, Node *second) {
    Node* L = first->left;
    Node* R = second->right;
    second->right = first;
    first->left = second;
    L->right = R;
    R->left = L;
}
void FibHeap::merge(FibHeap* that) {
    if (!that->size) {
        return ;
    }
    if (!size) {
        min = that->min;
        size = that->size;
    } else {
        unionLists(min, that->min);
        size += that->size;
        if (that->min->key < min->key) {
            min = that->min;
        }
    }
}
void FibHeap::linkHeap(Node* x, Node* y) {
    if (!y || !x) {
        return;
    }
    if (!x->child) {
        x->child = y;
    } else {
        unionLists(x->child, y);
    }
    y->parent = x;
    x->degree++;
    y->mark = false;
}

void FibHeap::consolidate() {
    Node** conslArray = new Node*[size];
    for (int i = 0; i < size; i++) {
       conslArray[i] = nullptr;
    }
    Node* it = min;
    do
    {
       Node* x = it;
       int d = x->degree;
       while (conslArray[d]) {
           Node* y = conslArray[d];
           if (x->key > y->key) {
               Node* tmp = x;
               x = y;
               y = tmp;
           }
           linkHeap(x, y);
           conslArray[d] = nullptr;
           d++;
       }
       conslArray[d] = x;
       it = it->right;
    } while ( it != min);
    min = nullptr;
    for (int i = 0; i < size; i++) {
        if (conslArray[i]) {
            if (!min) {
                min = conslArray[i];
            } else {
                unionLists(min, conslArray[i]);
                if (conslArray[i]->key < min->key) {
                    min = conslArray[i];
                }
            }
        }
    }
}
Node* FibHeap::extractMin() {
    Node* prevMin = min;
    if (min->child) {
        unionLists(min, min->child);
    }
    Node* L = min->left;
    Node* R = min->right;
    L->right = R;
    R->left = L;
    size--;
    if (prevMin->right == prevMin) {
       min = nullptr;
       return prevMin;
    }
    min = min->right;
    consolidate();
    return prevMin;
}
