#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "game.hh"
#include "randgen.hh"
#include "stats.hh"

void print_statistics(std::unordered_map<std::size_t, std::size_t> const& complete_occurrences, std::size_t length) {
    std::vector<std::size_t> scores;
    std::vector<std::size_t> all_games;
    
    for (std::size_t i = 0; i <= length; ++i) {
        auto it = complete_occurrences.find(i);
        if (it != complete_occurrences.end()) {
            for (std::size_t j = 0; j < it->second; ++j) {
                all_games.push_back(it->first);
            }
        }
        scores.push_back(it->second);
    }

    std::sort(all_games.begin(), all_games.end());

    double total_games = all_games.size();
    double mean = std::accumulate(all_games.begin(), all_games.end(), 0.0) / total_games;
    double median = calculate_median(all_games);
    auto mode = calculate_mode(complete_occurrences);

    double variance = 0.0;
    for (const auto& score : all_games) {
        variance += (score - mean) * (score - mean);
    }
    variance /= total_games;
    double stdev = std::sqrt(variance);

    double q1 = calculate_percentile(all_games, 25.0);
    double q3 = calculate_percentile(all_games, 75.0);

    std::size_t min = all_games.front();
    std::size_t max = all_games.back();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Game Statistics:\n";
    std::cout << "-----------------\n";
    for (std::size_t i = 0; i <= length; ++i) {
        std::cout << "Score " << i << ": " << complete_occurrences.at(i) << " games\n";
    }

    std::cout << "\nAggregate Statistics:\n";
    std::cout << "---------------------\n";
    std::cout << "Mean: " << mean << "\n";
    std::cout << "Median: " << median << "\n";
    std::cout << "Mode: ";
    for (const auto& m : mode) {
        std::cout << m << " ";
    }
    std::cout << "\n";
    std::cout << "Standard Deviation: " << stdev << "\n";
    std::cout << "Min: " << min << "\n";
    std::cout << "Max: " << max << "\n";
    std::cout << "Q1 (25th percentile): " << q1 << "\n";
    std::cout << "Q3 (75th percentile): " << q3 << "\n";
}


int main()
{
    constexpr int minimum = 1;
    constexpr int maximum = 1000;
    constexpr std::size_t length = 20;

    std::unordered_map<std::size_t, std::size_t> complete_occurrences;
    for (std::size_t i = 0; i <= length; ++i)
    {
        complete_occurrences[i] = 0;
    }

    std::vector<std::string> winning_games;

    std::size_t wins = 0;
    for (std::size_t games = 1; games <= 100'000'000; ++games)
    {
        std::ostringstream oss;
        randgen r(minimum, maximum);
        game g(length, r);
        int last_value;
        auto result = g.play(last_value);

        complete_occurrences[g.completed()]++;

        if (result == game::gameover::win)
        {
            std::cout << "Winner!" << '\n';
            oss << g << std::flush;
            winning_games.push_back(oss.str());
            ++wins;
        }

        print_statistics(complete_occurrences, length);

        std::cout << "Wins/Games: " << wins << '/' << games << '\n';
        double ratio = ((double)wins)/games;
        std::cout << "Ratio: " << ratio << '\n';
    }

    std::cout << std::flush;

    return 0;
}
