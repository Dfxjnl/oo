#include "game.hpp"

#include <chrono>
#include <memory>
#include <thread>

#include "color.hpp"
#include "map.hpp"
#include "point.hpp"
#include "sdl_backend.hpp"
#include "terminal.hpp"
#include "tile.hpp"

namespace oo
{
Game::Game()
    : m_backend {std::make_unique<SDLBackend>()}
    , m_terminal {m_backend->console_size()}
{
    m_map.set_tile({5, 5}, TileType::Wall);
    m_map.set_tile({5, 6}, TileType::Wall);
    m_map.set_tile({5, 7}, TileType::Wall);
    m_map.set_tile({5, 8}, TileType::Wall);
}

void Game::run()
{
    render();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
}

void Game::render()
{
    m_terminal.clear();

    // Render the map.
    for (int y {0}; y < Map::dimension.height; ++y) {
        for (int x {0}; x < Map::dimension.width; ++x) {
            const Point point {x, y};

            switch (m_map.tile_at(point)) {
            case TileType::Floor: {
                m_terminal.write(point, '.', colors::dark_gray);
            } break;

            case TileType::Wall: {
                m_terminal.write(point, '#', colors::white);
            } break;
            }
        }
    }

    m_backend->draw(m_terminal.glyphs());
}
} // namespace oo
