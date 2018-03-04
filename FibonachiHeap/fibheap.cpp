#include "fibheap.h"
#include <iostream>
FibHeap::FibHeap() {
    size = 0;
    min = nullptr;
}
Node* FibHeap::insert_key(int key) {
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
    return newNode;
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
    Node* L = y->left;
    Node* R = y->right;
    L->right = R;
    R->left = L;
    y->left = y->right = y;
    if (x->child == nullptr) {
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
    Node* it = min->right;
    while (it != min)
    {

       Node* x = it;
       Node* R = it->right;
       Node* L = it->left;
       R->left = L;
       L->right = R;
       int d = x->degree;
       x->left = x->right = x;

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
       it = R;
    }
    Node* x = it;
    Node* R = it->right;
    Node* L = it->left;
    R->left = L;
    L->right = R;
    int d = x->degree;
    x->left = x->right = x;

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
    it = R;
    min = nullptr;
    for (int i = 0; i < size; i++) {
        if (conslArray[i]) {
            Node* t = conslArray[i];

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
    delete[] conslArray;
}
Node* FibHeap::extractMin() {
    Node* prevMin = min;
    if (min->child) {
        Node* it = min->child;
        do
        {
            Node* R = it->right;
            it->parent = nullptr;
            it->left = it->right = it;
            unionLists(min, it);
            it = R;
        } while(it != min->child);
        min->child = nullptr;
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
void FibHeap::decreaseKey(Node* x, int k) {
    if (k > x->key) {
        return ;
    }
    x->key = k;
    Node* y = x->parent;
    if (y && x->key < y->key) {
        cut(x, y);
        cascadingCut(y);
    }
    if (x->key < min->key) {
        min = x;
    }
}
void FibHeap::cut(Node *x, Node *y) {
    Node* L = x->left;
    Node* R = x->right;
    L->right = R;
    R->left = L;
    y->degree--;
    if (y->child == x) {
        if (x->right == x) {
            y->child = nullptr;
        } else {
            y->child = x->right;
        }
    }
    x->parent = nullptr;
    x->left = x->right = x;
    unionLists(min, x);
}
void FibHeap::cascadingCut(Node *y) {
    Node* z = y->parent;
    if (z) {
        if (y->mark == false) {
            y->mark = true;
        } else {
            cut(y,z);
            cascadingCut(z);
        }
    }
}
void FibHeap::deleteNode(Node *x) {
    decreaseKey(x, -1e9);
    extractMin();
}
