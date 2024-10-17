#pragma once

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <RC/Vector.h>

namespace RC {

class SV {
public:
    SV() : data(nullptr), len(0) {};
    SV(const char *data) : data(data) {
        len = strlen(data);
    }
    SV(const char *data, size_t len) : data(data), len(len) {}
    ~SV() {};

    SV substr(size_t offset, size_t len) const {
        return SV(data + offset, len);
    }

    size_t find_substr(const char *substr) const {
        const char *found = strstr(data, substr);
        if (found) {
            return found - data;
        }
        return len;
    }

    size_t find_char(char c, size_t start) const {
        for (size_t i = start; i < len; i++) {
            if (data[i] == c) return i;
        }

        return len;
    }

    SV trim() {
        size_t start = 0;
        size_t end = len;

        while (start < end && isspace(static_cast<unsigned char>(data[start]))) {
            ++start;
        }

        while (end > start && isspace(static_cast<unsigned char>(data[end - 1]))) {
            --end;
        }

        return SV(data + start, end - start);
    }

    // NOTE: Needs to be freed or deleted.
    const char *as_cstr() const {
        char *cstr = new char[len + 1];
        memcpy(cstr, data, len);
        cstr[len] = '\0';
        return cstr;
    }

    Vector<SV> split_multiple(char delim) {
        size_t p = 0;
        SV search(data, len);
        Vector<SV> res;

        while ((p = search.find_char(delim, 0)) < search.len) {
            SV start(search.data, p);
            res.push_back(start);

            // Move search forward, past the delimiter
            search.data += p + 1;
            search.len -= p + 1;
        }

        // Add the remaining part of the string after the last delimiter
        if (search.len > 0) {
            res.push_back(SV(search.data, search.len));
        }

        return res;
    }

    int to_int() {
        int result = 0;
        for (size_t i = 0; i < len; i++) {
            char c = data[i];
            if ((int) c < 48 || (int) c > 57) return -1;
            int val = ((int) c) - 48;
            result *= 10;
            result += val;
        }
        return result;
    }

    bool operator==(const SV& other) const {
        if (len != other.len) return false;
        return (strncmp(data, other.data, len) == 0);
    }

    const char *data;
    size_t len;
};

}
