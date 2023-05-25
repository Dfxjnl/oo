#ifndef OO_COLOR_HPP
#define OO_COLOR_HPP

#include <algorithm>
#include <compare>

namespace oo
{
struct Color
{
    constexpr Color() = default;

    constexpr Color(const int p_red, const int p_green, const int p_blue)
    {
        red = std::clamp(p_red, 0x00, 0xFF);
        green = std::clamp(p_green, 0x00, 0xFF);
        blue = std::clamp(p_blue, 0x00, 0xFF);
    }

    constexpr auto operator<=>(const Color&) const = default;

    int red {0};
    int green {0};
    int blue {0};
};

namespace colors
{
constexpr Color black {0x00, 0x00, 0x00};
constexpr Color white {0xDD, 0xDD, 0xDD};
constexpr Color red {0xCC, 0x00, 0x00};
constexpr Color green {0x00, 0xAA, 0x00};
constexpr Color blue {0x00, 0x22, 0xFF};
} // namespace colors
} // namespace oo

#endif // OO_COLOR_HPP
