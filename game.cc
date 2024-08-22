#include "game.hh"
#include "randgen.hh"

game::game(std::size_t n, randgen& gen)
    : len(n), gen(gen)
{
    this->buffer = std::make_unique<std::optional<int>[]>(n);

    std::fill(buffer.get(), buffer.get() + len, std::nullopt);
}

game::gameover game::play(int& last_value)
{
    std::optional<game::gameover> gameover;

    while (!gameover.has_value())
    {
        gameover = play_once(last_value);
    }

    return gameover.value();
}


bool game::check_win() const
{
    for (int i = 0; i < len; ++i)
    {
        if (!buffer[i].has_value())
        {
            return false;
        }
    }
    return true;
}

std::optional<game::gameover> game::play_once(int& last_value)
{
    if (check_win())
    {
        return gameover::win;
    }

    last_value = gen.next();
    int x = last_value;

    std::size_t s = len;
    for (; s > 0; --s)
    {
        if (buffer[s - 1].has_value() && buffer[s - 1].value() < x)
        {
            break;
        }
    }

    std::size_t t = 0;
    if (!(buffer[t].has_value() && buffer[t].value() > x))
    {
        for(; t + 1 < len; ++t)
        {
            if (buffer[t + 1].has_value() && buffer[t + 1].value() > x)
            {
                break;
            }
        }
    }

    if (s > t)
    {
        return gameover::lose;
    }

    int a = buffer[s].has_value() ? buffer[s].value() : gen.minimum;

    int b = buffer[t].has_value() ? buffer[t].value() : gen.maximum;

    std::size_t slots = 1 + t - s;

    double range = 1 + b - a;

    double bucket_size = range / slots;

    for (int i = 0; i < slots; ++i)
    {
        if (x < a + (i + 1) * bucket_size)
        {
            buffer[s + i] = x;
            break;
        }
    }

    return {};
}

std::ostream& operator<<(std::ostream& os, const game& g)
{
    os << "Game state: [";
    for (std::size_t i = 0; i < g.len; ++i)
    {
        if (g.buffer[i].has_value())
        {
            os << g.buffer[i].value();
        }
        else
        {
            os << "_";
        }
        if (i < g.len - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
