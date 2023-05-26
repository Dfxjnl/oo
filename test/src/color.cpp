#include "color.hpp"

#include <doctest/doctest.h>

TEST_CASE("Color")
{
    using namespace oo::colors;
    using oo::Color;

    SUBCASE("Default constructor")
    {
        constexpr Color color;

        CHECK(color == black);
    }

    SUBCASE("Constructor with values")
    {
        constexpr Color color {0x12, 0x34, 0x56};

        CHECK(color.red == 0x12);
        CHECK(color.green == 0x34);
        CHECK(color.blue == 0x56);
    }

    SUBCASE("Clamping")
    {
        constexpr Color color {-1, 0, 256};

        CHECK(color == Color {0x00, 0x00, 0xFF});
    }
}
