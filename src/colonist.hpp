#ifndef OO_COLONIST_HPP
#define OO_COLONIST_HPP

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

    [[nodiscard]] constexpr auto position() const noexcept { return m_position; }

private:
    Point m_position;
};
} // namespace oo

#endif // OO_COLONIST_HPP
