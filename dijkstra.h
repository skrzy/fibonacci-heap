#ifndef FIBONACCI_HEAP_DIJKSTRA_H
#define FIBONACCI_HEAP_DIJKSTRA_H

#include <algorithm>
#include <cassert>
#include "fibonacci_heap.h"

using namespace std;

const int INF = std::numeric_limits<int>::max();

struct vertex {
    int index;
    int value;

    vertex(int index, int value) : index(index), value(value) {}

    friend bool operator <(const vertex& l, const vertex& r) {
        return l.value < r.value;
    }
};

int* dijkstra(vector<int>& edges, int size) {
    if (size < 2) throw -1;

    typedef fibonacci_heap<vertex>::iter ptr;
    fibonacci_heap<vertex> Q;
    vector<ptr> D;

    D.push_back(Q.push(vertex(0, 0)));
    for (int i = 1; i < size; i++) {
       D.push_back(Q.push(vertex(i, INF)));
    }

    while (!Q.empty()) {
        vertex min = Q.top();
        int rowStart = min.index * size;

        for (int i = 0; i < size; i++) {
            int edgeWeight = edges[rowStart + i];
            int currentWeightToVertex = D[i].getValue().value;
            int weightToNewVertex = D[min.index].getValue().value;
            int weightThroughNewVertex = weightToNewVertex + edgeWeight;

            if (edgeWeight != INF && weightToNewVertex != INF && currentWeightToVertex > weightThroughNewVertex) {
                Q.decrease(D[i], vertex(D[i].getValue().index, weightThroughNewVertex));
            }
        }

//        for(int i = 0; i < size; i++) {
//            cout << D[i].getValue().value << " ";
//        }
//        cout << endl;
        Q.pop();
    }

    auto result = new int[size];
    for (int i = 0; i < size; i++) {
        result[i] = D[i].getValue().value;
    }
    return result;
}

#endif
