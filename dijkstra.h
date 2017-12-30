#ifndef FIBONACCI_HEAP_DIJKSTRA_H
#define FIBONACCI_HEAP_DIJKSTRA_H

#include <algorithm>
#include <cassert>
#include <set>
#include <map>
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

vector<int> dijkstra(vector<int>& edges, int size) {
    if (size < 2) throw -1;

    typedef fibonacci_heap<vertex>::handler handler;
    fibonacci_heap<vertex> Q;
    vector<int> D;
    map<int, handler> unvisitedVertexes;

    D.push_back(0);
    unvisitedVertexes[0] = Q.push(vertex(0, 0));
    for (int i = 1; i < size; i++) {
        D.push_back(INF);
        unvisitedVertexes[i] = Q.push(vertex(i, INF));
    }

    while (!Q.empty()) {
        vertex min = Q.top();
        Q.pop();
        unvisitedVertexes.erase(unvisitedVertexes.find(min.index));
        int rowStart = min.index * size;

        for (int i = 0; i < size; i++) {
            int edgeWeight = edges[rowStart + i];
            int currentWeightToVertex = D[i];
            int weightToNewVertex = D[min.index];
            int weightThroughNewVertex = weightToNewVertex + edgeWeight;

            if (edgeWeight != INF && weightToNewVertex != INF && currentWeightToVertex > weightThroughNewVertex) {
                D[i] = weightThroughNewVertex;
                if (unvisitedVertexes.count(i)) {
                    Q.decrease(unvisitedVertexes[i], vertex(unvisitedVertexes[i].getValue().index, weightThroughNewVertex));
                }
            }
        }

//        for(int i = 0; i < size; i++) {
//            cout << D[i] << " ";
//        }
//        cout << endl;
    }

    return D;
}

#endif
