#ifndef OO_COLONIST_HPP
#define OO_COLONIST_HPP

#include "energy.hpp"
#include "point.hpp"

namespace oo
{
class Rng;

class Colonist
{
public:
    Colonist(const Point position, Rng& rng)
        : m_position {position}
        , m_rng {&rng}
    {
    }

    [[nodiscard]] constexpr auto can_take_turn() const noexcept { return m_energy.can_take_turn(); }

    auto gain_energy() -> bool;
    void take_turn();

    [[nodiscard]] constexpr auto position() const noexcept { return m_position; }

private:
    constexpr void move(const Point offset) noexcept { m_position += offset; }

    Point m_position;
    Energy m_energy;

    Rng* m_rng {nullptr};
};
} // namespace oo

#endif // OO_COLONIST_HPP
