#include "colonist.hpp"

#include <memory>

#include "action.hpp"
#include "game.hpp"
#include "point.hpp"
#include "rng.hpp"

namespace oo
{
auto Colonist::gain_energy() -> bool
{
    return m_energy.gain();
}

auto Colonist::take_turn() -> std::unique_ptr<Action>
{
    switch (m_game->rng().get(0, 3)) {
    case 0: {
        if (m_position.y > 0) {
            return std::make_unique<MoveAction>(*this, Point {0, -1});
        }
    } break;

    case 1: {
        if (m_position.y < m_game->map().dimension().height) {
            return std::make_unique<MoveAction>(*this, Point {0, 1});
        }
    } break;

    case 2: {
        if (m_position.x > 0) {
            return std::make_unique<MoveAction>(*this, Point {-1, 0});
        }
    } break;

    case 3: {
        if (m_position.x < m_game->map().dimension().width) {
            return std::make_unique<MoveAction>(*this, Point {1, 0});
        }
    } break;
    }

    return std::make_unique<MoveAction>(*this, Point {0, 0});
}
} // namespace oo
