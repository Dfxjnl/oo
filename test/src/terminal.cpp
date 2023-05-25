#include "terminal.hpp"

#include <doctest/doctest.h>

#include <cstddef>
#include <stdexcept>
#include <string>

#include "dimension.hpp"
#include "point.hpp"

TEST_CASE("Terminal")
{
    using oo::Point;

    constexpr oo::Dimension dimension {10, 5};
    oo::Terminal terminal {dimension};

    SUBCASE("Writing a character at a position")
    {
        constexpr Point position {2, 3};
        constexpr char character {'A'};

        terminal.write(position, character);

        CHECK(terminal.read_at(position) == character);
    }

    SUBCASE("Writing a string at a position")
    {
        constexpr Point position {5, 2};
        const std::string string {"Hello"};

        terminal.write(position, string);

        const std::size_t start {position.y * dimension.width + position.x};

        for (std::size_t i {0}; i < string.size(); ++i) {
            CHECK(terminal.glyphs()[start + i] == string[i]);
        }
    }

    SUBCASE("Writing out of range")
    {
        constexpr Point position {12, 3};
        constexpr char character {'A'};

        CHECK_THROWS_AS(terminal.write(position, character), std::out_of_range);
    }
}
