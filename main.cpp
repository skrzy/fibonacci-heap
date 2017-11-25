#include <iostream>
#include <cassert>
#include <algorithm>
#include "fibonacci_heap.h"
#include "fibonacci_heap_algorithm.h"

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

void test_sort() {
    int unsorted[] = {2, -45, 121, 56, 13, 22, 22 };
    int* sorted = fibonacci_heap_sort(unsorted, unsorted + 7);

    std::vector<int> v(unsorted, unsorted + 7);
    std::make_heap (v.begin(),v.end());
    std::sort_heap (v.begin(),v.end());
    for (int i = 0; i < v.size(); i++) {
        assert(sorted[i] == v[i]);
    }
}

int main() {
    test_insert();
    test_sort();
    return 0;
}