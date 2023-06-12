#ifndef OO_COLONIST_HPP
#define OO_COLONIST_HPP

#include "energy.hpp"
#include "point.hpp"

namespace oo
{
class Colonist
{
public:
    explicit Colonist(const Point position)
        : m_position {position}
    {
    }

    void update();

    [[nodiscard]] constexpr auto position() const noexcept { return m_position; }

private:
    void take_turn();

    Point m_position;
    Energy m_energy;
};
} // namespace oo

#endif // OO_COLONIST_HPP
