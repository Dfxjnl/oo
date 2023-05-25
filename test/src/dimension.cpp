#include "dimension.hpp"

#include <doctest/doctest.h>

TEST_CASE("Dimension")
{
    constexpr oo::Dimension dimension {5, 10};

    SUBCASE("area()")
    {
        CHECK(dimension.area() == 50);
    }

    SUBCASE("operator/")
    {
        constexpr auto result {dimension / 2};

        CHECK(result.width == 2);
        CHECK(result.height == 5);
    }
}
