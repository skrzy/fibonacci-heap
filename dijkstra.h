#ifndef FIBONACCI_HEAP_DIJKSTRA_H
#define FIBONACCI_HEAP_DIJKSTRA_H

#include <algorithm>
#include <cassert>
#include "fibonacci_heap.h"


const int INF = std::numeric_limits<int>::max();

int* dijkstra(int* edges, int size) {
    if (size < 2) throw -1;

    typedef fibonacci_heap::iter vertex;
    fibonacci_heap Q;
    vertex * D = new vertex[size];

    D[0] = Q.push(0);
    for (int i = 1; i < size; i++) {
       D[i] = Q.push(INF);
    }

    while (!Q.empty()) {
//         min = Q.top();
    }



}

#endif
