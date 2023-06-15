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

    [[nodiscard]] constexpr auto map() const noexcept -> const Map& { return m_map; }

    [[nodiscard]] constexpr auto log() noexcept -> Log& { return m_log; }

    [[nodiscard]] constexpr auto rng() noexcept -> Rng& { return m_rng; }

private:
    void render();
    void render_map();
    void render_colonists();
    void render_log();
    void render_stats();

    void handle_input();

    void update();
    void update_fov();

    std::unique_ptr<GraphicsBackend> m_backend {nullptr};
    Terminal m_terminal;
    InputManager m_input_manager;
    Rng m_rng;
    Log m_log;

    bool m_running {true};

    Map m_map;
    std::vector<Colonist> m_colonists;

    bool m_visibility_dirty {true};
};
} // namespace oo

#endif // OO_GAME_HPP
