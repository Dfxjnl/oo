#ifndef OO_TERMINAL_HPP
#define OO_TERMINAL_HPP

#include <algorithm>
#include <cstddef>
#include <string_view>
#include <vector>

#include "color.hpp"
#include "dimension.hpp"
#include "point.hpp"

namespace oo
{
struct Glyph
{
    char character {' '};
    Color foreground {colors::white};
    Color background {colors::black};
};

class Terminal
{
public:
    constexpr explicit Terminal(const Dimension dimension)
        : m_dimension {dimension}
    {
        m_glyphs.resize(static_cast<std::size_t>(dimension.area()), Glyph {});
    }

    constexpr void clear() noexcept { std::ranges::fill(m_glyphs, Glyph {}); }

    void write(Point position,
               char character,
               Color foreground = colors::white,
               Color background = colors::black);

    void write(Point position,
               std::string_view text,
               Color foreground = colors::white,
               Color background = colors::black);

    [[nodiscard]] auto read_at(Point position) const -> const Glyph&;

    [[nodiscard]] constexpr auto glyphs() const noexcept -> const std::vector<Glyph>&
    {
        return m_glyphs;
    }

private:
    [[nodiscard]] auto index(Point position) const -> std::size_t;

    std::vector<Glyph> m_glyphs {' '};
    Dimension m_dimension;
};
} // namespace oo

#endif // OO_TERMINAL_HPP
