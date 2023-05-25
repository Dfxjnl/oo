#ifndef OO_TERMINAL_HPP
#define OO_TERMINAL_HPP

#include <algorithm>
#include <cstddef>
#include <string_view>
#include <vector>

#include "dimension.hpp"
#include "point.hpp"

namespace oo
{
class Terminal
{
public:
    constexpr explicit Terminal(const Dimension dimension)
        : m_dimension {dimension}
    {
        m_glyphs.resize(static_cast<std::size_t>(dimension.area()), ' ');
    }

    constexpr void clear() noexcept { std::ranges::fill(m_glyphs, ' '); }

    void write(Point position, char character);
    void write(Point position, std::string_view text);

    [[nodiscard]] auto read_at(Point position) const -> char;

    [[nodiscard]] constexpr auto glyphs() const noexcept -> const std::vector<char>&
    {
        return m_glyphs;
    }

private:
    [[nodiscard]] auto index(Point position) const -> std::size_t;

    std::vector<char> m_glyphs {' '};
    Dimension m_dimension;
};
} // namespace oo

#endif // OO_TERMINAL_HPP
