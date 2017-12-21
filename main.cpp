#include <iostream>
#include <cassert>
#include <algorithm>
#include <chrono>
#include "fibonacci_heap.h"
#include "fibonacci_heap_algorithm.h"
#include "dijkstra.h"

using namespace std;
using namespace std::chrono;

void test_insert() {
    auto heap = new fibonacci_heap<int>;
    heap->push(2);
    heap->push(-45);
    heap->push(121);
    heap->push(22);
    heap->push(56);
    heap->push(13);
    heap->push(22);
    assert(heap->top() == -45);
    heap->pop();
    assert(heap->top() == 2);
    heap->pop();
    assert(heap->top() == 13);
    heap->pop();
    assert(heap->top() == 22);
    heap->pop();
    assert(heap->top() == 22);
    heap->pop();
    assert(heap->top() == 56);
    heap->pop();
    assert(heap->top() == 121);
}

void test_sort() {
    int unsorted[] = {2, -45, 121, 56, 13, 22, 22 };
    fibonacci_heap<int> fh = make_fibonacci_heap(unsorted, unsorted + 7);
    int* sorted = sort_fibonacci_heap(fh);

    std::vector<int> v(unsorted, unsorted + 7);
    make_heap(v.begin(), v.end());
    sort_heap(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        assert(sorted[i] == v[i]);
    }
}

void test_decrease() {
    auto heap = new fibonacci_heap<int>;
    heap->push(2);
    heap->push(-45);
    auto el = heap->push(121);
    heap->push(56);
    heap->push(13);
    heap->push(22);
    heap->push(22);
    heap->pop();
    heap->decrease(el, 1);
    assert(heap->top() == 1);
}

void test_greater() {
    auto heap = new fibonacci_heap<int, greater<>>;
    heap->push(2);
    heap->push(-45);
    heap->push(13);
    heap->push(22);
    assert(heap->top() == 22);
    heap->pop();
    assert(heap->top() == 13);
    heap->pop();
    assert(heap->top() == 2);
    heap->pop();
    assert(heap->top() == -45);
}

void sorting_performance_test() {

    const int N = 1000000;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, N * 1000);

    int* unsorted = new int[N];
    for (int i = 0; i < N; i++) {
        int r = distribution(generator);
        unsorted[i] = r;
    }

    fibonacci_heap<int> fh = make_fibonacci_heap(unsorted, unsorted + N);

    high_resolution_clock::time_point start = high_resolution_clock::now();
    int* sorted = sort_fibonacci_heap(fh);
    high_resolution_clock::time_point finish = high_resolution_clock::now();
    duration<double> fibonacci_heap_sort_time = duration_cast<duration<double>>(finish - start);

    vector<int> v(unsorted, unsorted + N);
    make_heap(v.begin(), v.end());

    start = high_resolution_clock::now();
    sort_heap(v.begin(), v.end());
    finish = high_resolution_clock::now();
    duration<double> binary_heap_sort_time = duration_cast<duration<double>>(finish - start);

    cout << "Results for " << N << " elements:" << endl;
    cout << "Fibonacci heap: " << fibonacci_heap_sort_time.count() << endl;
    cout << "Binary heap: " << binary_heap_sort_time.count() << endl;

}

int main() {
    test_insert();
    test_sort();
    test_decrease();
    test_greater();
    sorting_performance_test();


    const int N_VERTEXES = 5;

    vector<int> edges = {
    //FROM     a      b     c      d      e      //TO
              0,     10,   INF,   INF,     5,    //a
              INF,   0,      1,   INF,     2,    //b
              INF,   INF,    0,     4,   INF,    //c
              7,     INF,    6,     0,   INF,    //d
              INF,   3,      9,     2,     0,    //e
    };

    cout << endl << "dijkstra start" << endl;
    int * result = dijkstra(edges, N_VERTEXES);
    cout << "dijkstra result: " << endl;
    for (int i = 0; i < N_VERTEXES; i++) {
        cout << result[i] << " ";
    }

//    cout << endl;
//
//    const double GOLDEN_RATIO = (1 + sqrt(5)) / 2;
//    int node_count = 0;
//    vector<int> steps;
//    int current_step = -1;
//    while (current_step < 40) {
//        int step = int(log(node_count)/log(GOLDEN_RATIO)) + 2;
//        if (step != current_step) {
//            steps.push_back(node_count);
//            current_step = step;
//        }
//        node_count ++;
//    }
//
//    for (int i = 0; i < 40; i++) {
//        cout << steps[i] << " ";
//    }
//
    return 0;
}