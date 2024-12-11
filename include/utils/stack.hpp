#ifndef STACK_H
#define STACK_H

#include <iostream>

typedef double Elem_t;
static const size_t DEFAULT_CAPACITY = 25;

template <typename T>
class Stack {
private:
	size_t size;
	T data[DEFAULT_CAPACITY];

public:
    Stack(): size(0) {};

    size_t get_size() {
        return size;
    }

    void Push(T elem) {
	    data[size] = elem;
	    ++size;
    }

    T Pop() {
        --size;
        T del_elem = data[size];
	    return del_elem;
    }

    void Print() {
        for(int i = 0; i < size; ++i) {
            std::cerr << "  " << data[i];
        }
        std::cerr << std::endl;
    }
};

#endif // STACK_H