//
// Created by General Suslik on 06.09.2025.
//

#include <iostream>
#include <thread>

#include "cache/cache.h"

int main() {

    imc::Cache<size_t, size_t> cache(3, 100);

    constexpr size_t num_threads = 4;

    std::vector<std::thread> producers;
    producers.reserve(num_threads);
    for (size_t i = 0; i < num_threads; ++i) {
        producers.emplace_back([&] {
            cache.Put(i, i);
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::vector<std::thread> consumers;
    consumers.reserve(num_threads);
    for (size_t i = 0; i < num_threads; ++i) {
        consumers.emplace_back([&] {
            auto opt = cache.Get(i);
            if (opt.has_value()) {
                std::cout << opt.value() << std::endl;
            } else {
                std::cout << "Not found" << std::endl;
            }
        });
    }

    for (auto& t : producers) {
        t.join();
    }

    for (auto& t : consumers) {
        t.join();
    }

    return 0;
}