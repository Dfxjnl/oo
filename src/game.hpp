#ifndef OO_GAME_HPP
#define OO_GAME_HPP

#include <memory>
#include <vector>

#include "colonist.hpp"
#include "graphics_backend.hpp"
#include "input_manager.hpp"
#include "log.hpp"
#include "map.hpp"
#include "rng.hpp"
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
    void render_map();
    void render_colonists();
    void render_log();

    void handle_input();

    void update();

    std::unique_ptr<GraphicsBackend> m_backend {nullptr};
    Terminal m_terminal;
    InputManager m_input_manager;
    Rng m_rng;
    Log m_log;

    bool m_running {true};

    Map m_map;
    std::vector<Colonist> m_colonists;
};
} // namespace oo

#endif // OO_GAME_HPP
