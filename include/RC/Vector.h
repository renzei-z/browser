#pragma once

#include <stdlib.h>
#include <string.h>

namespace RC {

template<typename T>
class Vector {
public:
    Vector(size_t capacity = 4);
    ~Vector();

    void push_back(const T& value);
    T& operator[](size_t index);
    size_t len() const;
private:
    T* data;
    size_t capacity;
    size_t length;

    void resize(size_t new_capacity);
};

}
