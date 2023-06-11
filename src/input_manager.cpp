#include "input_manager.hpp"

namespace oo
{
void InputManager::clear() noexcept
{
    m_pressed_keys.clear();
}

void InputManager::on_command(const input::Key key)
{
    if (key != input::Key::None) {
        m_pressed_keys.emplace(key);
    }
}

auto InputManager::is_key_down(const input::Key key) const -> bool
{
    return m_pressed_keys.contains(key);
}
} // namespace oo
