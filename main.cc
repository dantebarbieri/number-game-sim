#include <iostream>

#include "game.hh"
#include "randgen.hh"

int main()
{
    constexpr int minimum = 1;
    constexpr int maximum = 1000;
    constexpr std::size_t length = 20;

    std::size_t wins = 0, games = 0;
    for (int i = 0; i < 100'000'000; ++i)
    {
        randgen r(minimum, maximum);
        game g(length, r);
        int last_value;
        auto result = g.play(last_value);

        std::cout << g << '\n';
        std::cout << "Last value: " << last_value << '\n';

        if (result == game::gameover::win)
        {
            std::cout << "Winner!" << '\n';
            ++wins;
        } else if (result == game::gameover::lose)
        {
            std::cout << "Loser :(" << '\n';
        }
        ++games;

        std::cout << "Wins/Games: " << wins << '/' << games << '\n';
        double ratio = ((double)wins)/games;
        std::cout << "Ratio: " << ratio << '\n';
    }

    std::cout << std::flush;

    return 0;
}