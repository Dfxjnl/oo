#ifndef OO_GAME_HPP
#define OO_GAME_HPP

#include <memory>

#include "graphics_backend.hpp"
#include "input_manager.hpp"
#include "map.hpp"
#include "terminal.hpp"

namespace oo
{
class Game
{
public:
    Game();

    void run();

private:
    void render();

    void handle_input();

    std::unique_ptr<GraphicsBackend> m_backend {nullptr};
    Terminal m_terminal;
    InputManager m_input_manager;

    bool m_running {true};

    Map m_map;
};
} // namespace oo

#endif // OO_GAME_HPP
