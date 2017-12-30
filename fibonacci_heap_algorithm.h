#ifndef FIBONACCI_HEAP_FIBONACCI_HEAP_ALGORITHM_H
#define FIBONACCI_HEAP_FIBONACCI_HEAP_ALGORITHM_H

#include "fibonacci_heap.h"

template <typename T, typename Iterator>
fibonacci_heap<T> make_fibonacci_heap(Iterator begin, Iterator end) {
    fibonacci_heap<T> heap;
    while (begin != end) {
        heap.push(*begin);
        begin++;
    }
    return heap;
}

template <typename T>
T* sort_fibonacci_heap(fibonacci_heap<T>& heap) {
    T * result = new T[heap.size()];
    int index = 0;

    while (!heap.empty()) {
        result[index++] = heap.top();
        heap.pop();
    }

    return result;
}

#endif
