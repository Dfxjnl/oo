#ifndef OO_INPUT_MANAGER_HPP
#define OO_INPUT_MANAGER_HPP

#include <set>

namespace oo
{
namespace input
{
enum class Key
{
    None,
    Up,
    Down,
    Left,
    Right,
    Q
};
} // namespace input

class InputManager
{
public:
    void clear() noexcept;
    void on_command(input::Key key);
    [[nodiscard]] auto is_key_down(input::Key key) const -> bool;

private:
    std::set<input::Key> m_pressed_keys;
};
} // namespace oo

#endif // OO_INPUT_MANAGER_HPP
