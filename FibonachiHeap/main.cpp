#include <iostream>
#include "fibheap.h"

int main() {
    FibHeap heap;
    heap.insert_key(9);
    Node* x = heap.insert_key(5);
    Node* y = heap.insert_key(6);
    heap.insert_key(10);
    heap.insert_key(6);
    heap.insert_key(3);
    heap.deleteNode(x);
    std::cout << heap.extractMin()->key << '\n';
    heap.deleteNode(y);
    std::cout << heap.extractMin()->key << '\n';
    std::cout << heap.extractMin()->key << '\n';
    std::cout << heap.extractMin()->key << '\n';
    //std::cout << heap.extractMin()->key << '\n';
    //std::cout << heap.extractMin()->key << '\n';
    return 0;
}
