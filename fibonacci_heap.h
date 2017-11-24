#ifndef FIBONACCI_HEAP_FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_FIBONACCI_HEAP_H

class fibonacci_heap {
public:
    bool insert(int val);
    void print();
private:
    struct node;
    typedef node* ptr;

    struct node {
        int key;    //TODO template
        ptr parent;
        ptr left;
        ptr right;
        ptr child;
        int degree;
        bool mark;

        node(int key): key(key), parent(nullptr), child(nullptr), degree(0), mark(false) {}
    };

    ptr min = nullptr;
    int n_nodes = 0;

    void print(ptr root, int level);
};

#endif
