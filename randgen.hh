#pragma once

#include <memory>
#include <random>
#include <set>

class randgen {
public:
    randgen(int a, int b);
    int next();

    const int minimum;
    const int maximum;
private:
    std::unique_ptr<std::random_device> device_ptr;
    std::unique_ptr<std::default_random_engine> engine_ptr;
    std::unique_ptr<std::set<int>> available_numbers;
};
