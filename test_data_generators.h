#ifndef FIBONACCI_HEAP_TEST_DATA_GENERATORS_H
#define FIBONACCI_HEAP_TEST_DATA_GENERATORS_H

#include <vector>
#include <random>

using namespace std;
vector<int>* generate_ints(int size) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, size * 1000);

    auto collection = new vector<int>();
    for (int i = 0; i < size; i++) {
        int r = distribution(generator);
        collection->push_back(r);
    }
    return collection;
}

vector<double>* generate_doubles(int size) {
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0, 100000);

    auto collection = new vector<double>();
    for (int i = 0; i < size; i++) {
        double r = distribution(generator);
        collection->push_back(r);
    }
    return collection;
}

vector<char>* generate_chars(int size) {
    default_random_engine generator;
    uniform_int_distribution<char> distribution(0, 127);

    auto collection = new vector<char>();
    for (int i = 0; i < size; i++) {
        char r = distribution(generator);
        collection->push_back(r);
    }
    return collection;
}

class Foo {
    int bar;
    string baz;

public:
    Foo(int bar, const string &baz) : bar(bar), baz(baz) {}
    Foo() {}

private:
    friend bool operator <(const Foo& l, const Foo& r) {
        return l.bar < r.bar;
    }
};


vector<Foo>* generate_Foos(int size) {

    string sample_strings[] = {
            "Lorem",
            "ipsum dolor sit amet",
            "Aenean hendrerit neque in justo mollis, id hendrerit augue porttitor"
    };

    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, size * 1000);

    auto collection = new vector<Foo>();
    for (int i = 0; i < size; i++) {
        int r = distribution(generator);
        collection->push_back(Foo(r, sample_strings[r % 3]));
    }
    return collection;
}

#endif
