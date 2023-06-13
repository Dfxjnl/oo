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
constexpr Color gray {0x77, 0x77, 0x77};
constexpr Color red {0xFF, 0x00, 0x00};
constexpr Color orange {0xFF, 0x88, 0x00};
constexpr Color yellow {0xFF, 0xDD, 0x00};
constexpr Color green {0x00, 0xAA, 0x00};
constexpr Color aqua {0x00, 0xCC, 0xAA};
constexpr Color blue {0x00, 0x22, 0xFF};
constexpr Color purple {0xCC, 0x33, 0xFF};

constexpr Color dark_gray {0x44, 0x44, 0x44};
constexpr Color dark_red {0x88, 0x00, 0x00};
constexpr Color dark_orange {0x88, 0x33, 0x00};
constexpr Color dark_yellow {0x77, 0x66, 0x00};
constexpr Color dark_green {0x00, 0x55, 0x00};
constexpr Color dark_aqua {0x00, 0x66, 0x55};
constexpr Color dark_blue {0x00, 0x33, 0xBB};
constexpr Color dark_purple {0x77, 0x00, 0x88};
} // namespace colors
} // namespace oo

#endif // OO_COLOR_HPP
