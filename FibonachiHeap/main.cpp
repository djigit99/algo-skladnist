#include <iostream>
#include "fibheap.h"

int main() {
    FibHeap heap;
    heap.insert_key(9);
    heap.insert_key(5);
    heap.insert_key(6);
    heap.insert_key(10);
    heap.insert_key(6);
    heap.insert_key(3);
    std::cout << heap.extractMin()->key << '\n';
    std::cout << heap.extractMin()->key << '\n';
    std::cout << heap.extractMin()->key << '\n';
    std::cout << heap.extractMin()->key << '\n';
    std::cout << heap.extractMin()->key << '\n';
    std::cout << heap.extractMin()->key << '\n';
    return 0;
}
