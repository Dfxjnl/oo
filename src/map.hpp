#ifndef OO_MAP_HPP
#define OO_MAP_HPP

#include <array>
#include <cstddef>

#include "dimension.hpp"

namespace oo
{
enum class TileType;
struct Point;

class Map
{
public:
    static constexpr Dimension dimension {.width = 64, .height = 64};

    void set_tile(Point position, TileType type);
    [[nodiscard]] auto tile_at(Point position) const -> TileType;

private:
    [[nodiscard]] static auto index(Point position) -> std::size_t;

    std::array<TileType,
               static_cast<std::size_t>(dimension.width)
                   * static_cast<std::size_t>(dimension.height)>
        m_tiles {};
};
} // namespace oo

#endif // OO_MAP_HPP
