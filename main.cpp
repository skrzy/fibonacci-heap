#include <iostream>
#include "fibonacci_heap.h"

void test_insert() {
    auto heap = new fibonacci_heap;
    heap->push(2);
    heap->push(-45);
    heap->push(121);
    heap->push(56);
    heap->push(13);
    heap->push(22);
    heap->push(22);
    heap->print();
    std::cout << std::endl << heap->top() << std::endl;
    heap->pop();
    std::cout << std::endl << heap->top() << std::endl;
    heap->print();
}

int main() {
    test_insert();
    return 0;
}