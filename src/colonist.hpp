#ifndef OO_COLONIST_HPP
#define OO_COLONIST_HPP

#include <memory>

#include "energy.hpp"
#include "point.hpp"

namespace oo
{
class Action;
class Game;

class Colonist
{
public:
    static constexpr char glyph {'@'};

    Colonist(const Point position, Game& game)
        : m_position {position}
        , m_game {&game}
    {
    }

    auto gain_energy() -> bool;
    auto take_turn() -> std::unique_ptr<Action>;

    constexpr void move(const Point offset) noexcept { m_position += offset; }

    [[nodiscard]] constexpr auto can_take_turn() const noexcept { return m_energy.can_take_turn(); }

    [[nodiscard]] constexpr auto position() const noexcept { return m_position; }

private:
    Point m_position;
    Energy m_energy;

    Game* m_game {nullptr};
};
} // namespace oo

#endif // OO_COLONIST_HPP
