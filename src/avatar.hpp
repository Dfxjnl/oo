#ifndef OO_AVATAR_HPP
#define OO_AVATAR_HPP

#include <memory>

#include "action.hpp"
#include "energy.hpp"
#include "point.hpp"

namespace oo
{
class Avatar
{
public:
    static constexpr char glyph {'@'};

    explicit Avatar(const Point position)
        : m_position {position}
    {
    }

    auto gain_energy() -> bool;
    auto take_turn() -> std::unique_ptr<Action>;

    constexpr void move(const Point offset) noexcept { m_position += offset; }

    void set_next_action(std::unique_ptr<Action> action);

    [[nodiscard]] constexpr auto can_take_turn() const noexcept { return m_energy.can_take_turn(); }

    [[nodiscard]] constexpr auto position() const noexcept { return m_position; }

    [[nodiscard]] constexpr auto needs_input() const noexcept { return m_next_action == nullptr; }

private:
    Point m_position;
    Energy m_energy;
    std::unique_ptr<Action> m_next_action {nullptr};
};
} // namespace oo

#endif // OO_AVATAR_HPP
