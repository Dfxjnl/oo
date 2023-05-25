#include "dimension.hpp"

#include <doctest/doctest.h>

TEST_CASE("Dimension")
{
    SUBCASE("area()")
    {
        constexpr oo::Dimension dimension {5, 10};
        CHECK(dimension.area() == 50);
    }
}
