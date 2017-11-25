#ifndef FIBONACCI_HEAP_FIBONACCI_HEAP_ALGORITHM_H
#define FIBONACCI_HEAP_FIBONACCI_HEAP_ALGORITHM_H

#include "fibonacci_heap.h"

fibonacci_heap make_fibonacci_heap(int* begin, int* end) {
    fibonacci_heap heap;
    while (begin != end) {
        heap.push(*begin);
        begin++;
    }
    return heap;
}

int* sort_fibonacci_heap(fibonacci_heap& heap) {
    int * result = new int[heap.size()];
    int index = 0;

    while (!heap.empty()) {
        result[index++] = heap.top();
        heap.pop();
    }

    return result;
}

#endif
