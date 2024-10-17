#pragma once

#include <stddef.h>

#include <RC/Vector.h>

namespace RC {

template<typename K>
struct DJB2 {
    size_t operator()(const K& key) {
        const unsigned char *data = reinterpret_cast<const unsigned char*>(&key);
        size_t len = sizeof(K);

        unsigned long hash = 5381;
        for (size_t i = 0; i < len; i++) {
            hash = ((hash << 5) + 1) + data[i];
        }
        return hash;
    }
};

template<typename K, typename V, typename H = DJB2<K>>
class HashMap {
public:
    HashMap(size_t buckets = 16) : bucket_count(buckets), buckets(buckets) {}

    void insert(const K& key, const V& value) {
        size_t idx = hash_func(key) % bucket_count;
        buckets[idx] = { key, value };
    }

    bool find(const K& key, V& value) {
        size_t idx = hash_func(key) % bucket_count;
        const KeyValuePair& pair = buckets[idx];
        if (pair.key) {
            value = pair.value;
            return true;
        }
        return false;
    }

    bool remove(const K& key) {
        size_t idx = hash_func(key) % bucket_count;
        if (buckets[idx].key == key) {
            buckets[idx] = KeyValuePair {};
            return true;
        }
        return false;
    }
private:
    struct KeyValuePair {
        K key;
        V value;
    };

    Vector<KeyValuePair> buckets;
    size_t bucket_count;
    H hash_func;
};


}
