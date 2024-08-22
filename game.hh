#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <iostream>

#include "randgen.hh"

class game {
public:
    enum class gameover { lose, win };
    game(std::size_t n, randgen& gen);
    gameover play(int& last_value);

    const std::size_t len;

    friend std::ostream& operator<<(std::ostream& os, const game& g);

private:
    bool check_win() const;
    std::optional<gameover> play_once(int& last_value);

    std::unique_ptr<std::optional<int>[]> buffer;
    randgen& gen;
};
