#include "colonist.hpp"

#include <memory>

#include "action.hpp"
#include "map.hpp"
#include "point.hpp"
#include "rng.hpp"
#include "tile.hpp"

namespace oo
{
auto Colonist::gain_energy() -> bool
{
    return m_energy.gain();
}

auto Colonist::take_turn() -> std::unique_ptr<Action>
{
    switch (m_rng->get(0, 3)) {
    case 0: {
        if (m_position.y > 0) {
            return std::make_unique<MoveAction>(*this, Point {0, -1});
        }
    } break;

    case 1: {
        if (m_position.y < 19) {
            return std::make_unique<MoveAction>(*this, Point {0, 1});
        }
    } break;

    case 2: {
        if (m_position.x > 0) {
            return std::make_unique<MoveAction>(*this, Point {-1, 0});
        }
    } break;

    case 3: {
        if (m_position.x < 49) {
            return std::make_unique<MoveAction>(*this, Point {1, 0});
        }
    } break;
    }

    return std::make_unique<MoveAction>(*this, Point {0, 0});
}

auto Colonist::can_occupy(const Map& map, const Point position) -> bool
{
    if (!map.inbounds(position)) {
        return false;
    }

    return map.tile_at(position) == TileType::Grass;
}
} // namespace oo
