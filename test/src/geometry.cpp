#include "geometry.hpp"

#include <doctest/doctest.h>

#include <vector>

#include "point.hpp"

TEST_CASE("line_function")
{
    using oo::line_function;
    using oo::Point;

    SUBCASE("Horizontal line")
    {
        std::vector<Point> points;
        line_function({0, 0}, {5, 0}, [&points](const auto point) { points.push_back(point); });

        const std::vector<Point> expected_points {
            {0, 0},
            {1, 0},
            {2, 0},
            {3, 0},
            {4, 0},
            {5, 0}
        };

        REQUIRE(points == expected_points);
    }

    SUBCASE("Vertical line")
    {
        std::vector<Point> points;
        line_function({0, 0}, {0, 5}, [&points](const auto point) { points.push_back(point); });

        const std::vector<Point> expected_points {
            {0, 0},
            {0, 1},
            {0, 2},
            {0, 3},
            {0, 4},
            {0, 5}
        };

        REQUIRE(points == expected_points);
    }
}
