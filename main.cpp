#include <iostream>
#include <cassert>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <memory>
#include "fibonacci_heap.h"
#include "fibonacci_heap_algorithm.h"
#include "dijkstra.h"
#include "test_data_generators.h"

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
    vector<int> unsorted = *generate_ints(10000);
    fibonacci_heap<int> fh = make_fibonacci_heap<int>(unsorted.begin(), unsorted.end());
    int* sorted = sort_fibonacci_heap(fh);

    std::vector<int> v(unsorted.begin(), unsorted.end());
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

template <typename T>
void sorting_performance_test(vector<T>* (*generator)(int), int size) {

    duration<double> fibonacci_heap_sort_time = duration<double>(0);
    duration<double> binary_heap_sort_time = duration<double>(0);

    for (int i = 0; i < 10; i++) {
        vector<T>* unsorted = generator(size);
        /* FIBONACCI */
        high_resolution_clock::time_point start = high_resolution_clock::now();

        fibonacci_heap<T> fh = make_fibonacci_heap<T>(unsorted->begin(), unsorted->end());
        T* sorted = sort_fibonacci_heap(fh);

        high_resolution_clock::time_point finish = high_resolution_clock::now();
        fibonacci_heap_sort_time += duration_cast<duration<double>>(finish - start);
        /* --------- */

        /* BINARY */
        start = high_resolution_clock::now();

        make_heap(unsorted->begin(), unsorted->end());
        sort_heap(unsorted->begin(), unsorted->end());

        finish = high_resolution_clock::now();
        binary_heap_sort_time += duration_cast<duration<double>>(finish - start);
        /* ------ */

        delete unsorted;
        delete[] sorted;
    }

    cout << "Results for " << size << " elements of type " << typeid(T).name() << ":" << endl;
    cout << "Fibonacci heap: " << fibonacci_heap_sort_time.count() / 10 << endl;
    cout << "Binary heap: " << binary_heap_sort_time.count() / 10 << endl;
    cout << "Ratio (fib/bin): " << fibonacci_heap_sort_time.count() / binary_heap_sort_time.count() << endl;
    cout << endl;

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

void test_dijkstra(vector<int> distances, vector<int> expectedResults) {

//    cout << endl << "dijkstra start" << endl;
    int graphSize = (int)sqrt(distances.size());
    vector<int> result = dijkstra(distances, graphSize);
//    cout << "dijkstra result: " << endl;

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

    test_dijkstra(*read_dijkstra_data("../dijkstra_data.txt"), {
            0, 78, 102, 171, 240, 258, 312, 352, 400, 92,
            154, 230, 171, 369, 440, 444, 501, 474, 548, 695,
            614, 647, 650, 733, 686, 643, 603, 747, 702, 798,
            779, 837, 883, 913, 827, 704, 575, 493, 551, 544,
            444, 411, 511, 503, 562, 529, 587, 719, 745, 609,
            710, 449, 313, 278, 417, 460, 619, 748, 803, 850,
            765
    });

    test_dijkstra({
            INF, 4, INF, INF, INF, INF, INF, 8, INF,
            4, INF, 8, INF, INF, INF, INF, 11, INF,
            INF, 8, INF, 7, INF, 4, INF, INF, 2,
            INF, INF, 7, INF, 9, 14, INF, INF, INF,
            INF, INF, INF, 9, INF, 10, INF, INF, INF,
            INF, INF, 4, 14, 10, INF, 2, INF, INF,
            INF, INF, INF, INF, INF, 2, INF, 1, 6,
            8, 11, INF, INF, INF, INF, 1, INF, 7,
            INF, INF, 2, INF, INF, INF, 6, 7, INF
    }, {
            0, 4, 12, 19, 21, 11, 9, 8, 14
    });

    sorting_performance_test(generate_ints, 10000);
    sorting_performance_test(generate_ints, 1000000);
    sorting_performance_test(generate_ints, 10000000);
    sorting_performance_test(generate_doubles, 10000);
    sorting_performance_test(generate_doubles, 1000000);
    sorting_performance_test(generate_doubles, 10000000);
    sorting_performance_test(generate_chars, 10000);
    sorting_performance_test(generate_chars, 1000000);
    sorting_performance_test(generate_chars, 10000000);
    sorting_performance_test(generate_Foos, 10000);
    sorting_performance_test(generate_Foos, 1000000);
    sorting_performance_test(generate_Foos, 10000000);
    return 0;
}