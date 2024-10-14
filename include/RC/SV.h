#pragma once

#include <stddef.h>
#include <string.h>

namespace RC {

class SV {
public:
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

    // NOTE: Needs to be freed or deleted.
    const char *as_cstr() {
        char *cstr = new char[len + 1];
        memcpy(cstr, data, len);
        cstr[len] = '\0';
        return cstr;
    }

    const char *data;
    size_t len;
};

}
