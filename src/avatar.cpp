#include "avatar.hpp"

#include <memory>
#include <utility>

#include "action.hpp"

namespace oo
{
auto Avatar::gain_energy() -> bool
{
    return m_energy.gain();
}

auto Avatar::take_turn() -> std::unique_ptr<Action>
{
    auto action {std::move(m_next_action)};
    m_next_action.reset();
    return action;
}

void Avatar::set_next_action(std::unique_ptr<Action> action)
{
    m_next_action = std::move(action);
}
} // namespace oo
