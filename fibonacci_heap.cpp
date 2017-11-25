#include <iostream>
#include <array>
#include "fibonacci_heap.h"

void fibonacci_heap::node::insert_before(ptr n) {
    this->left = n->left;
    this->right = n;
    n->left->right = this;
    n->left = this;
}

void fibonacci_heap::node::switch_with(ptr n) {
    auto tmp_key = this->key;
    this->key = n->key;
    n->key = tmp_key;

    auto tmp_child = this->child;
    this->child = n->child;
    n->child = tmp_child;
}

void fibonacci_heap::node::remove_from_list() {
    this->left->right = this->right;
    this->right->left = this->left;
}

void fibonacci_heap::node::add_child(ptr n) {
    if (this->child == nullptr) {
        this->child = n->as_list();
    } else {
        n->insert_before(this->child);
    }
}

fibonacci_heap::ptr fibonacci_heap::node::as_list() {
    this->left = this;
    this->right = this;
    return this;
}

void fibonacci_heap::push(int val) {
    auto new_node = (ptr)new node(val);

    if (min == nullptr) {
        // utworzenie listy korzeni
        min = new_node->as_list();
    } else {
        new_node->insert_before(min);     // wstawienie do listy korzeni, przed elementem min (miejsce jest dowolne)
        if (new_node->key < min->key) {
            min = new_node;
        }
    }
    node_count++;
}

int fibonacci_heap::top() {
    return min->key;
}

void fibonacci_heap::pop() {

    if (min == nullptr) {
        return;
    }

    // przeniesienie dzieci elementu min do listy korzeni
    ptr child = min->child;
    if (child != nullptr) {
        auto last_child = child->left;
        child = child->left;
        auto next_child = child->right;
        do {
            child = next_child;
            next_child = child->right;
            child->insert_before(min);
            child->parent = nullptr;
        } while (child != last_child);
    }
    //usunięcie min z listy korzeni
    min->remove_from_list();

    if (min == min->right) {    // nie było innych korzeni
        delete min;
        min = nullptr;
    } else {
        auto tmp = min;     // ustawiamy min na kolejny korzeń, w tym momencie min nie musi wskazywać na minimalny element
        min = min->right;
        delete tmp;
        consolidate();
    }
    node_count--;
}

int fibonacci_heap::size() {
    return node_count;
}

bool fibonacci_heap::empty() {
    return min == nullptr;
}

void fibonacci_heap::consolidate() {
    int max_deg = max_degree();
    auto degrees = new ptr[max_deg]/*()*/;   // TODO sprawdzić
    std::fill_n(degrees, max_deg, nullptr);

    auto current_root = min->left;
    auto last_element = min->left;
    do {
        current_root = current_root->right;
//        auto x = current_root;  // TODO chyba niepotrzebne
        auto current_degree = current_root->degree;
        while (degrees[current_degree] != nullptr) {
            auto same_degree_root = degrees[current_degree];
            if (current_root->key > same_degree_root->key) {
                current_root->switch_with(same_degree_root);
            }
            link(same_degree_root, current_root);
            degrees[current_degree] = nullptr;
            current_degree++;
        }
        degrees[current_degree] = current_root;


    } while (current_root != last_element);

    min = nullptr;

    for (int i = 0; i < max_deg; i++) {
        if (degrees[i] != nullptr) {
            if (min == nullptr) {
                min = degrees[i]->as_list();
            } else {
                degrees[i]->insert_before(min);
                if (degrees[i]->key < min->key) {
                    min = degrees[i];
                }
            }
        }
    }

    delete[] degrees;
}

void fibonacci_heap::link(ptr child, ptr parent) {
    child->remove_from_list();
    parent->add_child(child);
    parent->degree++;
    child->mark = false; //TODO po co?
}

int fibonacci_heap::max_degree() {
    return int(log(node_count)/log(GOLDEN_RATIO));
}

void fibonacci_heap::print() {
    print(min, 0);
}

void fibonacci_heap::print(ptr root, int level) {
    auto tmp = root;
    do {
        std::cout << tmp->key << "L" << level;
        if (tmp->child != nullptr) {
            std::cout << "->(";
            print(tmp->child, level + 1);
            std::cout << ")";
        }
        std::cout << " ";
        tmp = tmp->right;
    } while (tmp != root);
}
