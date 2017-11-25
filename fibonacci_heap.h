#ifndef FIBONACCI_HEAP_FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_FIBONACCI_HEAP_H

#include <cmath>

class fibonacci_heap {
public:
    void push(int val);
    void pop();
    int top();  // TODO template
    void print();
private:
    struct node;
    typedef node* ptr;

    struct node {
        int key;    //TODO template
        ptr parent; // TODO niepotrzebne?
        ptr left;
        ptr right;
        ptr child;
        int degree;
        bool mark;

        node(int key): key(key), parent(nullptr), child(nullptr), degree(0), mark(false) {} //TODO template
        void insert_before(ptr n);
        void switch_with(ptr n);
        void remove_from_list();
        void add_child(ptr n);
        ptr as_list();
    };

    ptr min = nullptr;
    int node_count = 0;

    void consolidate();
    void link(ptr child, ptr parent);
    int max_degree();
    void print(ptr root, int level);

    const double GOLDEN_RATIO = (1 + sqrt(5)) / 2;
};

#endif
