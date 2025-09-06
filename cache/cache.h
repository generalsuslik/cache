//
// Created by General Suslik on 06.09.2025.
//

#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H

#include "shard.h"

#include <mutex>
#include <shared_mutex>
#include <vector>

namespace imc {

    template <typename K, typename V, typename Hash = std::hash<K>>
    class Cache {
    public:
        Cache(const size_t num_shards, const size_t shard_cap)
            : num_shards_(num_shards)
            , shard_cap_(shard_cap)
        {
            shards_.reserve(num_shards);
            for (size_t i = 0; i < num_shards; ++i) {
                shards_.emplace_back(shard_cap);
            }
        }

        void Put(const K& key, const V& value) {
            auto hash = hash_(key);

            std::unique_lock lock(mutex_);
            shards_[hash % num_shards_].Put(key, value);
        }

        std::optional<V> Get(const K& key) {
            auto hash = hash_(key);

            std::shared_lock lock(mutex_);
            return shards_[hash % num_shards_].Get(key);
        }

    private:
        size_t num_shards_;
        size_t shard_cap_;
        std::vector<Shard<K, V>> shards_;

        Hash hash_;

        mutable std::shared_mutex mutex_;
    };

} // namespace imc

#endif //CACHE_CACHE_H