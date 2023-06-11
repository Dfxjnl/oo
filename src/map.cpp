#include "map.hpp"

#include <fmt/core.h>

#include <cstddef>
#include <source_location>
#include <stdexcept>

#include "point.hpp"

namespace oo
{
enum class TileType;

void Map::set_tile(const Point position, const TileType type)
{
    m_tiles.at(index(position)) = type;
}

auto Map::tile_at(const Point position) const -> TileType
{
    return m_tiles.at(index(position));
}

auto Map::index(const Point position) -> std::size_t
{
    if (position.x < 0 || position.x >= dimension.width || position.y < 0
        || position.y >= dimension.height)
    {
        throw std::out_of_range(fmt::format("{}: Out of range: position: {}, dimension: {}",
                                            std::source_location::current().function_name(),
                                            position,
                                            dimension));
    }

    return static_cast<std::size_t>(position.y) * static_cast<std::size_t>(dimension.width)
        + static_cast<std::size_t>(position.x);
}
} // namespace oo
