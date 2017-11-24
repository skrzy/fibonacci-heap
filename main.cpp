#include <iostream>
#include "fibonacci_heap.h"

void test_insert() {
    auto heap = new fibonacci_heap;
    heap->insert(2);
    heap->insert(-45);
    heap->insert(121);
    heap->insert(56);
    heap->insert(13);
    heap->insert(22);
    heap->insert(22);
    heap->print();
}

int main() {
    test_insert();
    return 0;
}