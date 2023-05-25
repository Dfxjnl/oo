#ifndef OO_DIMENSION_HPP
#define OO_DIMENSION_HPP

#include <fmt/core.h>

namespace oo
{
struct Dimension
{
    [[nodiscard]] constexpr auto area() const noexcept { return width * height; }

    int width {0};
    int height {0};
};
} // namespace oo

template <>
struct fmt::formatter<oo::Dimension>
{
    static constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const oo::Dimension dimension, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "{}x{}", dimension.width, dimension.height);
    }
};

#endif // OO_DIMENSION_HPP
