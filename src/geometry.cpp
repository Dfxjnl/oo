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
    int ix {static_cast<int>(delta_x > 0) - static_cast<int>(delta_x < 0)};
    delta_x = std::abs(delta_x) << 1;

    int delta_y {destination.y - origin.y};
    int iy {static_cast<int>(delta_y > 0) - static_cast<int>(delta_y < 0)};
    delta_y = std::abs(delta_y) << 1;

    Point current {origin};
    function(current);

    if (delta_x >= delta_y) {
        int error {delta_y - (delta_x >> 1)};

        while (current.x != destination.x) {
            if (error >= 0 && (error != 0 || ix > 0)) {
                error -= delta_x;
                current.y += iy;
            }

            error += delta_y;
            current.x += ix;
            function(current);
        }
    } else {
        int error {delta_x - (delta_y >> 1)};

        while (current.y != destination.y) {
            if (error >= 0 && (error != 0 || iy > 0)) {
                error -= delta_y;
                current.x += ix;
            }

            error += delta_x;
            current.y += iy;
            function(current);
        }
    }
}
} // namespace oo
