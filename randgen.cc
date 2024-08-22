#include "randgen.hh"

randgen::randgen(int a, int b)
    : minimum(std::min(a, b)), maximum(std::max(a, b)), available_numbers(std::make_unique<std::set<int>>())
{
    this->device_ptr = std::make_unique<std::random_device>();
    this->engine_ptr = std::make_unique<std::default_random_engine>((*this->device_ptr)());

    for (int i = this->minimum; i <= this->maximum; ++i) {
        available_numbers->insert(i);
    }
}

int randgen::next() {
    // Generate a random index within the set
    std::uniform_int_distribution<int> dist(0, available_numbers->size() - 1);
    auto it = std::next(available_numbers->begin(), dist(*this->engine_ptr));

    int value = *it;
    available_numbers->erase(it);  // Remove the selected value

    return value;
}
