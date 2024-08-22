#pragma once

#include <unordered_map>
#include <vector>

double calculate_median(std::vector<std::size_t> const& values);

std::vector<std::size_t> calculate_mode(std::unordered_map<std::size_t, std::size_t> const& occurrences);

double calculate_percentile(const std::vector<std::size_t>& values, double percentile);

