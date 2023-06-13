#ifndef OO_MAP_HPP
#define OO_MAP_HPP

#include <cstddef>
#include <vector>

#include "dimension.hpp"

namespace oo
{
enum class TileType;
struct Point;

class Map
{
public:
    constexpr explicit Map(const Dimension dimension)
        : m_dimension {dimension}
    {
        m_tiles.resize(static_cast<std::size_t>(dimension.area()), {});
    }

    void set_tile(Point position, TileType type);
    [[nodiscard]] auto tile_at(Point position) const -> TileType;

    [[nodiscard]] constexpr auto dimension() const noexcept { return m_dimension; }

    [[nodiscard]] auto inbounds(Point position) const -> bool;

private:
    [[nodiscard]] auto index(Point position) const -> std::size_t;

    std::vector<TileType> m_tiles {};
    Dimension m_dimension;
};
} // namespace oo

#endif // OO_MAP_HPP
