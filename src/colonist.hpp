#ifndef OO_COLONIST_HPP
#define OO_COLONIST_HPP

#include "energy.hpp"
#include "point.hpp"
#include "rng.hpp"

namespace oo
{
class Colonist
{
public:
    Colonist(const Point position, Rng& rng)
        : m_position {position}
        , m_rng {&rng}
    {
    }

    void update();

    [[nodiscard]] constexpr auto position() const noexcept { return m_position; }

private:
    void take_turn();

    Point m_position;
    Energy m_energy;

    Rng* m_rng {nullptr};
};
} // namespace oo

#endif // OO_COLONIST_HPP
