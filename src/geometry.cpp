#include "geometry.hpp"

#include <cmath>
#include <functional>

#include "point.hpp"

namespace oo
{
void line_function(const Point origin,
                   const Point destination,
                   const std::function<void(Point)>& function)
{
    int delta_x {destination.x - origin.x};
    int step_x {static_cast<int>(delta_x > 0) - static_cast<int>(delta_x < 0)};
    delta_x = std::abs(delta_x) * 2;

    int delta_y {destination.y - origin.y};
    int step_y {static_cast<int>(delta_y > 0) - static_cast<int>(delta_y < 0)};
    delta_y = std::abs(delta_y) * 2;

    Point current {origin};
    function(current);

    if (delta_x >= delta_y) {
        int error {delta_y - (delta_x / 2)};

        while (current.x != destination.x) {
            if (error >= 0 && (error != 0 || step_x > 0)) {
                error -= delta_x;
                current.y += step_y;
            }

            error += delta_y;
            current.x += step_x;
            function(current);
        }
    } else {
        int error {delta_x - (delta_y / 2)};

        while (current.y != destination.y) {
            if (error >= 0 && (error != 0 || step_y > 0)) {
                error -= delta_y;
                current.x += step_x;
            }

            error += delta_x;
            current.y += step_y;
            function(current);
        }
    }
}
} // namespace oo
