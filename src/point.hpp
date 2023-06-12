#ifndef OO_POINT_HPP
#define OO_POINT_HPP

#include <fmt/format.h>

namespace oo
{
struct Point
{
    constexpr auto operator+=(const Point other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    int x {0};
    int y {0};
};
} // namespace oo

template <>
struct fmt::formatter<oo::Point>
{
    static constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const oo::Point point, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "{}:{}", point.x, point.y);
    }
};

#endif // OO_POINT_HPP
