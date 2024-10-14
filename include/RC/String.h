#pragma once

#include <string.h>

namespace RC {

class String {
public:
    String() : size(0), capacity(0), data(nullptr) {}

    String(const char *str) {
        size = strlen(str);
        capacity = size + 1;
        data = new char[capacity];
        strcpy(data, str);
    }

    String(const String& other) {
        size = other.size;
        capacity = other.capacity;
        data = new char[capacity];
        strcpy(data, other.data);
    }

    String(String&& other) noexcept : size(other.size), capacity(other.capacity), data(other.data) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    String operator+(const String& other) const {
        String res;

        res.size = size + other.size;
        res.capacity = res.size + 1;
        res.data = new char[res.capacity];

        if (data) strcpy(res.data, data);
        if (other.data) strcat(res.data, other.data);

        return res;
    }

    friend String operator+(const String& lhs, const char *rhs) {
        String res;
        size_t rhs_size = strlen(rhs);
        res.size = lhs.size + rhs_size;
        res.capacity = res.size + 1;
        res.data = new char[res.capacity];

        if (lhs.data) strcpy(res.data, lhs.data);
        strcpy(res.data + lhs.size, rhs);

        return res;
    }

    void append(const char *str) {
        size_t new_size = size + strlen(str);
        size_t new_capacity = new_size + 1;
        char *new_data = new char[new_capacity];

        memcpy(new_data, data, size);
        delete[] data;
        strcpy(new_data + size, str);
        size = new_size;
        data = new_data;
        capacity = new_capacity;
    }

    friend String operator+(const char *lhs, const String& rhs) {
        String res;
        size_t lhs_size = strlen(lhs);
        res.size = lhs_size + rhs.size;
        res.capacity = res.size + 1;
        res.data = new char[res.capacity];

        strcpy(res.data, lhs);
        strcpy(res.data + lhs_size, rhs.data);

        return res;
    }

    const char *as_cstr() const {
        return data ? data : "";
    }

    size_t len() const {
        return size;
    }

private:
    size_t size;
    size_t capacity;
    char *data;

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity) {
            char *new_data = new char[new_capacity];
            if (data) {
                strcpy(new_data, data);
                delete[] data;
            }
            data = new_data;
            capacity = new_capacity;
        }
    }
};

}
