#ifndef OO_MAP_HPP
#define OO_MAP_HPP

#include <cstddef>
#include <vector>

#include "dimension.hpp"
#include "point.hpp"
#include "tile.hpp"

namespace oo
{
class Map
{
public:
    constexpr explicit Map(const Dimension dimension)
        : m_dimension {dimension}
    {
        m_tiles.resize(static_cast<std::size_t>(dimension.area()), {});
    }

    void set_tile(Point position, TileType type);
    [[nodiscard]] auto tile_at(Point position) const -> const Tile&;

    [[nodiscard]] auto can_occupy(Point position) const -> bool;

    void reset_visibility();
    void make_radius_visible(Point position, int radius);

    [[nodiscard]] constexpr auto dimension() const noexcept { return m_dimension; }

    [[nodiscard]] constexpr auto inbounds(const Point position) const noexcept -> bool
    {
        return position.x >= 0 && position.x < m_dimension.width && position.y >= 0
            && position.y < m_dimension.height;
    }

private:
    [[nodiscard]] auto index(Point position) const -> std::size_t;

    std::vector<Tile> m_tiles;
    Dimension m_dimension;
};
} // namespace oo

#endif // OO_MAP_HPP
