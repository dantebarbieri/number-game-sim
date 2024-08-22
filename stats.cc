#include "stats.hh"

#include <cmath>

double calculate_median(std::vector<std::size_t> const& values) {
    std::size_t size = values.size();
    if (size == 0) return 0;

    if (size % 2 == 0) {
        return (values[size / 2 - 1] + values[size / 2]) / 2.0;
    } else {
        return values[size / 2];
    }
}

std::vector<std::size_t> calculate_mode(std::unordered_map<std::size_t, std::size_t> const& occurrences) {
    std::size_t max_count = 0;
    std::vector<std::size_t> modes;
    
    for (const auto& entry : occurrences) {
        if (entry.second > max_count) {
            max_count = entry.second;
            modes.clear();
            modes.push_back(entry.first);
        } else if (entry.second == max_count) {
            modes.push_back(entry.first);
        }
    }
    
    return modes;
}

double calculate_percentile(std::vector<std::size_t> const& values, double percentile) {
    std::size_t size = values.size();
    if (size == 0) return 0;
    
    double index = (percentile / 100.0) * (size - 1);
    std::size_t lower = std::floor(index);
    std::size_t upper = std::ceil(index);
    
    if (lower == upper) {
        return values[lower];
    } else {
        return values[lower] * (upper - index) + values[upper] * (index - lower);
    }
}