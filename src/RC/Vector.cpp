#include <RC/Vector.h>

namespace RC {

template<typename T>
Vector<T>::Vector(size_t capacity)
    : capacity(capacity), length(0) {
    data = new T[capacity];
}

template<typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (length == capacity) resize(capacity * 2);
    data[length++] = value;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= length) {
        // TODO: Index out of bounds - we need to panic here?
    }
    return data[index];
}

template<typename T>
void Vector<T>::resize(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    memcpy(new_data, data, length * sizeof(T));
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

}
