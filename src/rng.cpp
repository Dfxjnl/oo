#include "rng.hpp"

#include <random>

namespace oo
{
auto Rng::get(const int min, const int max) -> int
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(m_engine);
}
} // namespace oo
