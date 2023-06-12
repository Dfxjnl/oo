#include "terminal.hpp"

#include <fmt/core.h>

#include <cstddef>
#include <source_location>
#include <stdexcept>
#include <string_view>

#include "point.hpp"

namespace oo
{
void Terminal::write(const Point position,
                     const char character,
                     const Color foreground,
                     const Color background)
{
    m_glyphs.at(index(position)) = {character, foreground, background};
}

void Terminal::write(const Point position,
                     const std::string_view text,
                     const Color foreground,
                     const Color background)
{
    for (std::size_t i {0}; i < text.size(); ++i) {
        if (position.x + static_cast<int>(i) >= m_dimension.width) {
            break;
        }

        write({position.x + static_cast<int>(i), position.y}, text[i], foreground, background);
    }
}

auto Terminal::read_at(const Point position) const -> const Glyph&
{
    return m_glyphs.at(index(position));
}

auto Terminal::index(const Point position) const -> std::size_t
{
    if (position.x < 0 || position.x >= m_dimension.width || position.y < 0
        || position.y >= m_dimension.height)
    {
        throw std::out_of_range(fmt::format("{}: Out of range: position: {} dimension: {}",
                                            std::source_location::current().function_name(),
                                            position,
                                            m_dimension));
    }

    return static_cast<std::size_t>(position.y * m_dimension.width + position.x);
}
} // namespace oo
