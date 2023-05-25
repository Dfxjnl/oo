#include "game.hpp"

#include <chrono>
#include <memory>
#include <thread>

#include "color.hpp"
#include "sdl_backend.hpp"
#include "terminal.hpp"

namespace oo
{
Game::Game()
    : m_backend {std::make_unique<SDLBackend>()}
    , m_terminal {m_backend->console_size()}
{
}

void Game::run()
{
    m_terminal.clear();
    m_terminal.write({0, 0}, "Hello world!", colors::red);
    m_backend->draw(m_terminal.glyphs());

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
}
} // namespace oo
