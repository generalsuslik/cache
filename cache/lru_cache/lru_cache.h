//
// Created by General Suslik on 06.09.2025.
//

#ifndef CACHE_LRU_CACHE_H
#define CACHE_LRU_CACHE_H

#include <list>
#include <optional>
#include <unordered_map>

namespace core {

    template <typename K, typename V, typename Hash = std::hash<K>>
    class LRUCache {
        using Node = std::pair<K, V>;

    public:
        explicit LRUCache(const size_t capacity) : capacity_(capacity) {}

        void Put(const K& key, const V& value) {
            auto it = cache_.find(key);

            if (it != cache_.end()) {
                it->second->second = value;
                list_.splice(list_.begin(), list_, it->second);
            } else {
                if (list_.size() == capacity_) {
                    auto last = list_.back();
                    cache_.erase(last.first);
                    list_.pop_back();
                }
                list_.emplace_front(key, value);
                cache_[key] = list_.begin();
            }
        }

        std::optional<V> Get(const K& key) {
            auto it = cache_.find(key);
            if (it == cache_.end()) {
                return std::nullopt;
            }

            list_.splice(list_.begin(), list_, it->second);
            return it->second->second;
        }

        bool Contains(const K& key) const {
            return cache_.contains(key);
        }

        void Clear() {
            cache_.clear();
            list_.clear();
        }

    private:
        std::unordered_map<K, typename std::list<Node>::iterator, Hash> cache_;
        std::list<Node> list_;
        size_t capacity_;
    };

} // namespace core

#endif //CACHE_LRU_CACHE_H