#pragma once

#include <assert.h>

namespace RC {

template<typename T>
class Optional {
public:
    Optional<T>(T& obj) : has_value(true), contained(obj) {}
    Optional<T>() : has_value(false) {}

    T& unwrap() {
        assert(has_value);
        return contained;
    }
    
    inline bool is_some() const {
        return has_value;
    }
private:
    bool has_value;
    T& contained;
};


}
