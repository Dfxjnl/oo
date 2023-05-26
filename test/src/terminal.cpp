#include "terminal.hpp"

#include <doctest/doctest.h>

#include <algorithm>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <string>

#include "color.hpp"
#include "dimension.hpp"
#include "point.hpp"

TEST_CASE("Terminal")
{
    using namespace oo::colors;
    using oo::Glyph;
    using oo::Point;

    constexpr oo::Dimension dimension {10, 5};
    oo::Terminal terminal {dimension};

    SUBCASE("Clearing the terminal")
    {
        terminal.clear();

        CHECK(std::ranges::all_of(terminal.glyphs(),
                                  [](const Glyph glyph) {
                                      return glyph.character == ' ' && glyph.foreground == white
                                          && glyph.background == black;
                                  }));
    }

    SUBCASE("Writing a character at a position")
    {
        constexpr Point position {2, 3};
        constexpr char character {'A'};

        terminal.write(position, character, red, white);

        CHECK(terminal.read_at(position).character == character);
        CHECK(terminal.read_at(position).foreground == red);
        CHECK(terminal.read_at(position).background == white);
    }

    SUBCASE("Writing a string at a position")
    {
        constexpr Point position {5, 2};
        const std::string string {"Hello"};

        terminal.write(position, string, red, white);

        const std::size_t start {position.y * dimension.width + position.x};

        for (std::size_t i {0}; i < string.size(); ++i) {
            CHECK(terminal.glyphs()[start + i].character == string[i]);
            CHECK(terminal.glyphs()[start + i].foreground == red);
            CHECK(terminal.glyphs()[start + i].background == white);
        }
    }

    SUBCASE("Writing out of range")
    {
        constexpr Point position {12, 3};
        constexpr char character {'A'};

        CHECK_THROWS_AS(terminal.write(position, character), std::out_of_range);
    }
}
