#include "map.hpp"

#include <fmt/core.h>

#include <cstddef>
#include <source_location>
#include <stdexcept>

#include "geometry.hpp"
#include "point.hpp"

namespace oo
{
void Map::set_tile(const Point position, const TileType type)
{
    m_tiles.at(index(position)).type = type;
}

auto Map::tile_at(const Point position) const -> const Tile&
{
    return m_tiles.at(index(position));
}

auto Map::can_occupy(const Point position) const -> bool
{
    if (!inbounds(position)) {
        return false;
    }

    return tile_at(position).type == TileType::Grass;
}

void Map::make_radius_visible(const Point position, const int radius)
{
    m_tiles.at(index(position)).visible = true;
    m_tiles.at(index(position)).explored = true;

    for (int angle {0}; angle < 360; ++angle) {
        const auto destination {project_angle(position, radius, angle)};
        line_function(position,
                      destination,
                      [this](const Point target)
                      {
                          if (inbounds(target)) {
                              m_tiles.at(index(target)).visible = true;
                              m_tiles.at(index(target)).explored = true;
                          }
                      });
    }
}

auto Map::index(const Point position) const -> std::size_t
{
    if (!inbounds(position)) {
        throw std::out_of_range(fmt::format("{}: Out of range: position: {}, dimension: {}",
                                            std::source_location::current().function_name(),
                                            position,
                                            m_dimension));
    }

    return static_cast<std::size_t>(position.y) * static_cast<std::size_t>(m_dimension.width)
        + static_cast<std::size_t>(position.x);
}
} // namespace oo
