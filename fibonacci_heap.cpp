#include <iostream>
#include "fibonacci_heap.h"

bool fibonacci_heap::insert(int val) {
    auto new_node = (ptr)new node(val);

    if (min == nullptr) {
        new_node->left = new_node;      // utworzenie listy korzeni
        new_node->right = new_node;
        min = new_node;
    } else {
        new_node->left = min->left;     // wstawienie do listy korzeni, przed elementem min (miejsce jest dowolne)
        new_node->right = min;
        min->left->right = new_node;
        min->left = new_node;
        if (new_node->key < min->key) {
            min = new_node;
        }
    }
    n_nodes++;

}


void fibonacci_heap::print() {
    print(min, 0);
}

void fibonacci_heap::print(ptr root, int level) {
    auto tmp = root;
    do {
        std::cout << tmp->key << "L" << level;
        tmp = tmp->right;
        if (tmp->child != nullptr) {
            std::cout << "->(";
            print(tmp->child, level++);
            std::cout << ")";
        }
        std::cout << " | ";
    } while (tmp != root);
}
