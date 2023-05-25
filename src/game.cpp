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

    m_terminal.write({4, 3}, "white", colors::white);

    int y_offset {4};
    m_terminal.write({4, y_offset}, "gray", colors::gray);
    m_terminal.write({4, ++y_offset}, "red", colors::red);
    m_terminal.write({4, ++y_offset}, "orange", colors::orange);
    m_terminal.write({4, ++y_offset}, "yellow", colors::yellow);
    m_terminal.write({4, ++y_offset}, "green", colors::green);
    m_terminal.write({4, ++y_offset}, "aqua", colors::aqua);
    m_terminal.write({4, ++y_offset}, "blue", colors::blue);
    m_terminal.write({4, ++y_offset}, "purple", colors::purple);

    int dark_y_offset {4};
    m_terminal.write({14, dark_y_offset}, "dark gray", colors::dark_gray);
    m_terminal.write({14, ++dark_y_offset}, "dark red", colors::dark_red);
    m_terminal.write({14, ++dark_y_offset}, "dark orange", colors::dark_orange);
    m_terminal.write({14, ++dark_y_offset}, "dark yellow", colors::dark_yellow);
    m_terminal.write({14, ++dark_y_offset}, "dark green", colors::dark_green);
    m_terminal.write({14, ++dark_y_offset}, "dark aqua", colors::dark_aqua);
    m_terminal.write({14, ++dark_y_offset}, "dark blue", colors::dark_blue);
    m_terminal.write({14, ++dark_y_offset}, "dark purple", colors::dark_purple);

    m_backend->draw(m_terminal.glyphs());

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(4s);
}
} // namespace oo
