#ifndef OO_GAME_HPP
#define OO_GAME_HPP

#include <memory>

#include "graphics_backend.hpp"
#include "terminal.hpp"

namespace oo
{
class Game
{
public:
    Game();

    void run();

private:
    std::unique_ptr<GraphicsBackend> m_backend {nullptr};
    Terminal m_terminal;
};
} // namespace oo

#endif // OO_GAME_HPP
