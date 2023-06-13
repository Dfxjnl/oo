#ifndef OO_COLONIST_HPP
#define OO_COLONIST_HPP

#include <memory>

#include "energy.hpp"
#include "point.hpp"

namespace oo
{
class Action;
class Map;
class Rng;

class Colonist
{
public:
    static constexpr char glyph {'@'};

    Colonist(const Point position, Rng& rng)
        : m_position {position}
        , m_rng {&rng}
    {
    }

    auto gain_energy() -> bool;
    auto take_turn() -> std::unique_ptr<Action>;

    constexpr void move(const Point offset) noexcept { m_position += offset; }

    [[nodiscard]] constexpr auto can_take_turn() const noexcept { return m_energy.can_take_turn(); }

    [[nodiscard]] static auto can_occupy(const Map& map, Point position) -> bool;

    [[nodiscard]] constexpr auto position() const noexcept { return m_position; }

private:
    Point m_position;
    Energy m_energy;

    Rng* m_rng {nullptr};
};
} // namespace oo

#endif // OO_COLONIST_HPP
