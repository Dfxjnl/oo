#ifndef OO_RNG_HPP
#define OO_RNG_HPP

#include <random>

namespace oo
{
class Rng
{
public:
    [[nodiscard]] auto get(int min, int max) -> int;

private:
    std::mt19937 m_engine {std::random_device {}()};
};
} // namespace oo

#endif // OO_RNG_HPP
