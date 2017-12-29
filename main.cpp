#include <iostream>
#include <cassert>
#include <algorithm>
#include <chrono>
#include <fstream>
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
    cout << "Ratio (fib/bin): " << fibonacci_heap_sort_time.count() / binary_heap_sort_time.count() << endl;

}

vector<int> * read_dijkstra_data(string filename) {
    ifstream ifs;

	ifs.open(filename);
    if (!ifs.is_open()) {
        cout << "file opening error" << endl;
        throw -1;
    }

    auto distances = new vector<int>();
    while (!ifs.eof()) {
        string value;
        ifs >> value;
        if (value == "x") {
            distances->push_back(INF);
        } else {
            distances->push_back(stoi(value));
        }
    }

    return distances;
}

void test_dijkstra() {

//    cout << endl << "dijkstra start" << endl;
    vector<int> * distances = read_dijkstra_data("../dijkstra_data.txt");
    int graphSize = (int)sqrt(distances->size());
    int * result = dijkstra(*distances, graphSize);
//    cout << "dijkstra result: " << endl;

    vector<int> expectedResults = { 0, 78, 102, 171, 240, 258, 312, 352, 400, 92,
                                    154, 230, 171, 369, 440, 444, 501, 474, 548, 695,
                                    614, 647, 650, 733, 686, 643, 603, 747, 702, 798,
                                    779, 837, 883, 913, 827, 704, 575, 493, 551, 544,
                                    444, 411, 511, 503, 562, 529, 587, 719, 745, 609,
                                    710, 449, 313, 278, 417, 460, 619, 748, 803, 850,
                                    765 };

    for (int i = 0; i < graphSize; i++) {
//        cout << result[i] << " ";
        assert(result[i] == expectedResults[i]);
    }
}

int main() {
    test_insert();
    test_sort();
    test_decrease();
    test_greater();
    test_dijkstra();
    sorting_performance_test();
    return 0;
}