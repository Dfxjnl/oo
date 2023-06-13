#ifndef OO_TILE_HPP
#define OO_TILE_HPP

namespace oo
{
enum class TileType
{
    Grass,
    Tree
};

struct Tile
{
    constexpr void set_visible(const bool value) noexcept
    {
        if (value) {
            explored = true;
        }

        visible = true;
    }

    TileType type {TileType::Grass};
    bool visible {false};
    bool explored {false};
};
} // namespace oo

#endif // OO_TILE_HPP
