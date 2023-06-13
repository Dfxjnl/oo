#include "action.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include "colonist.hpp"
#include "game.hpp"
#include "log.hpp"
#include "map.hpp"

namespace oo
{
void MoveAction::perform(Game& game)
{
    const auto destination {m_colonist->position() + m_offset};

    if (game.map().can_occupy(destination)) {
        m_colonist->move(m_offset);
    } else {
        game.log().add(fmt::format("{} hit a tree.", fmt::ptr(m_colonist)));
    }
}
} // namespace oo
