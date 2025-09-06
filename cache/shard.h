//
// Created by General Suslik on 06.09.2025.
//

#ifndef CACHE_BIN_SHARD_H
#define CACHE_BIN_SHARD_H

#include "cache/lru_cache/lru_cache.h"

namespace imc {

    template <typename K, typename V, typename Hash = std::hash<K>>
    class Shard {
    public:
        explicit Shard(const size_t capacity) : cache_(capacity) {}

        void Put(const K& key, const V& value) {
            cache_.Put(key, value);
        }

        std::optional<V> Get(const K& key) {
            return cache_.Get(key);
        }

        bool Contains(const K& key) const {
            return cache_.Contains(key);
        }

        void Clear() {
            cache_.Clear();
        }

    private:
        core::LRUCache<K, V, Hash> cache_;
    };

} // namespace imc

#endif //CACHE_BIN_SHARD_H