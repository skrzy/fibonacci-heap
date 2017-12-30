#ifndef FIBONACCI_HEAP_FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_FIBONACCI_HEAP_H

#include <cmath>
#include "fibonacci_degree_thresholds.h"

template <typename T, typename Compare = std::less<T>>
class fibonacci_heap {
private:
    struct node;
    typedef node* ptr;
    const Compare& comparator;
public:
    class iter {
        ptr node;
    public:
        iter() {}
        iter(ptr node): node(node) {};
        ptr getNode() {
            return node;
        };
        T getValue() {
            return node->key;
        }
    };
    iter push(T val);
    void pop();
    T top();
    bool decrease(iter i, T new_value);
    int size();
    bool empty();
    void print();

    fibonacci_heap(const Compare &comparator = Compare());

private:
    struct node {
        T key;
        ptr parent;
        ptr left;
        ptr right;
        ptr child;
        int degree;
        bool mark;

        node(T key): key(key), parent(nullptr), child(nullptr), degree(0), mark(false) {}
        void insert_before(ptr n);
        void remove_from_list();
        void add_child(ptr n);
        ptr as_list();
    };

    ptr min = nullptr;
    int node_count = 0;

    void consolidate();
    void link(ptr child, ptr parent);
    int get_max_degree();
    void cut(ptr child, ptr parent);
    void cascading_cut(ptr node);
    void print(ptr root, int level);

//    const double GOLDEN_RATIO = (1 + sqrt(5)) / 2;
};


template <typename T, typename Compare>
void fibonacci_heap<T, Compare>::node::insert_before(ptr n) {
    n->left = this->left;
    n->right = this;
    this->left->right = n;
    this->left = n;

//    this->left = n->left;
//    this->right = n;
//    n->left->right = this;
//    n->left = this;
}

template <typename T, typename Compare>
void fibonacci_heap<T, Compare>::node::remove_from_list() {
    this->left->right = this->right;
    this->right->left = this->left;
}

template <typename T, typename Compare>
void fibonacci_heap<T, Compare>::node::add_child(ptr n) {
    if (this->child == nullptr) {
        this->child = n->as_list();
    } else {
        this->child->insert_before(n);
    }
    n->parent = this;
}

template <typename T, typename Compare>
typename fibonacci_heap<T, Compare>::ptr fibonacci_heap<T, Compare>::node::as_list() {
    this->left = this;
    this->right = this;
    return this;
}

template <typename T, typename Compare>
typename fibonacci_heap<T, Compare>::iter fibonacci_heap<T, Compare>::push(T val) {
    auto new_node = (ptr)new node(val);

    if (min == nullptr) {
        // utworzenie listy korzeni
        min = new_node->as_list();
    } else {
        min->insert_before(new_node);     // wstawienie do listy korzeni, przed elementem min (miejsce jest dowolne)
        if (comparator(new_node->key, min->key)) {
            min = new_node;
        }
    }
    node_count++;

    return iter(new_node);
}

template <typename T, typename Compare>
T fibonacci_heap<T, Compare>::top() {
    return min->key;
}

template <typename T, typename Compare>
void fibonacci_heap<T, Compare>::pop() {

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
            min->insert_before(child);
            child->parent = nullptr;
        } while (child != last_child);
    }
    //usunięcie min z listy korzeni
    min->remove_from_list();

    if (min == min->right) {    // nie było innych korzeni
        min = nullptr;
    } else {
        min = min->right;
        consolidate();
    }
    node_count--;
}

template <typename T, typename Compare>
bool fibonacci_heap<T, Compare>::decrease(iter i, T new_value) {
    auto node = i.getNode();

    if (comparator(node->key, new_value)) {
        return false;
    }

    node->key = new_value;
    auto parent = node->parent;

    if (parent != nullptr && comparator(node->key, parent->key)) {
        cut(node, parent);
        cascading_cut(parent);
    }

    if (comparator(node->key, min->key)) {
        min = node;
    }

    return true;
}

template <typename T, typename Compare>
void fibonacci_heap<T, Compare>::cut(ptr child, ptr parent) {
    if (child->right != child) {
        parent->child = child->right;
    } else {
        parent->child = nullptr;
    }
    child->remove_from_list();
    parent->degree--;
    min->insert_before(child);  // dodanie do listy korzeni
    child->parent = nullptr;
    child->mark = false;
}

template <typename T, typename Compare>
void fibonacci_heap<T, Compare>::cascading_cut(ptr node) {
    auto parent = node->parent;
    if (parent != nullptr) {
        if (!node->mark) {
            node->mark = true;
        } else {
            cut(node, parent);
            cascading_cut(parent);
        }
    }
}

template <typename T, typename Compare>
int fibonacci_heap<T, Compare>::size() {
    return node_count;
}

template <typename T, typename Compare>
bool fibonacci_heap<T, Compare>::empty() {
    return min == nullptr;
}

template <typename T, typename Compare>
void fibonacci_heap<T, Compare>::consolidate() {
    int max_deg = get_max_degree();
    auto degrees = new ptr[max_deg];
    std::fill_n(degrees, max_deg, nullptr);

    auto current_root = min->left;
    auto last_element = min->left;
    ptr processed_element;     //dla warunku zakonczenia petli
    ptr next_root = current_root->right;
    do {
        current_root = next_root;
        processed_element = current_root;
        next_root = current_root->right;
        auto current_degree = current_root->degree;
        while (degrees[current_degree] != nullptr) {
            auto same_degree_root = degrees[current_degree];
            if (comparator(same_degree_root->key, current_root->key)) {
                auto tmp = current_root;
                current_root = same_degree_root;
                same_degree_root = tmp;
            }
            link(same_degree_root, current_root);
            degrees[current_degree] = nullptr;
            current_degree++;
        }
        degrees[current_degree] = current_root;


    } while (processed_element != last_element);

    min = nullptr;

    for (int i = 0; i < max_deg; i++) {
        if (degrees[i] != nullptr) {
            if (min == nullptr) {
                min = degrees[i]->as_list();
            } else {
                min->insert_before(degrees[i]);
                if (comparator(degrees[i]->key, min->key)) {
                    min = degrees[i];
                }
            }
        }
    }

    delete[] degrees;
}

template <typename T, typename Compare>
void fibonacci_heap<T, Compare>::link(ptr child, ptr parent) {
    child->remove_from_list();
    parent->add_child(child);
    parent->degree++;
    child->mark = false;
}

template <typename T, typename Compare>
int fibonacci_heap<T, Compare>::get_max_degree() {
    /* METHOD 1 */
//    int result = 0;
//    while (node_count > fibonacci_degree_thresholds[result]) {
//        result++;
//    }
//    return result;

    /* METHOD 2 */
//    return int(log(node_count)/log(GOLDEN_RATIO));

    /* METHOD 3 */
//    if (node_count < fibonacci_degree_thresholds[max_degree]) {
//        max_degree--;
//    } else {
//        while (node_count > fibonacci_degree_thresholds[max_degree + 1]) {
//            max_degree++;
//        }
//    }
//    return max_degree;

    /* METHOD 4 */
    return std::lower_bound(fibonacci_degree_thresholds, fibonacci_degree_thresholds + 40, node_count) - fibonacci_degree_thresholds;
}

template <typename T, typename Compare>
void fibonacci_heap<T, Compare>::print() {
    if (min == nullptr) std::cout << "empty" << std::endl;
    else print(min, 0);
    std::cout << std::endl;
}

template <typename T, typename Compare>
void fibonacci_heap<T, Compare>::print(ptr root, int level) {
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

template <typename T, typename Compare>
fibonacci_heap<T, Compare>::fibonacci_heap(const Compare &comparator) : comparator(comparator) {}

#endif
