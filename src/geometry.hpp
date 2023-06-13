#ifndef OO_GEOMETRY_HPP
#define OO_GEOMETRY_HPP

#include <cmath>
#include <functional>

#include "point.hpp"

namespace oo
{
constexpr auto project_angle(const Point origin, const int radius, const int degrees_radians)
    -> Point
{
    return {static_cast<int>(origin.x + radius * std::cos(degrees_radians)),
            static_cast<int>(origin.y + radius * std::sin(degrees_radians))};
}

void line_function(Point origin, Point destination, const std::function<void(Point)>& function);
} // namespace oo

#endif // OO_GEOMETRY_HPP
