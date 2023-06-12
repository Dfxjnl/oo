#include "game.hpp"

#include <chrono>
#include <compare>
#include <memory>
#include <ratio>
#include <thread>

#include "color.hpp"
#include "dimension.hpp"
#include "input_manager.hpp"
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
    , m_map {m_backend->console_size()}
{
    m_map.set_tile({5, 5}, TileType::Wall);
    m_map.set_tile({5, 6}, TileType::Wall);
    m_map.set_tile({5, 7}, TileType::Wall);
    m_map.set_tile({5, 8}, TileType::Wall);

    for (int i {0}; i < 30; ++i) {
        m_colonists.emplace_back(Point {i + 10, 8}, m_rng);
        m_colonists.emplace_back(Point {i + 10, 9}, m_rng);
        m_colonists.emplace_back(Point {i + 10, 10}, m_rng);
        m_colonists.emplace_back(Point {i + 10, 11}, m_rng);
    }
}

void Game::run()
{
    using namespace std::chrono_literals;
    auto duration {0ms};

    while (m_running) {
        const auto start_time {std::chrono::high_resolution_clock::now()};

        update();
        handle_input();
        render();

        const auto end_time {std::chrono::high_resolution_clock::now()};
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        constexpr auto frame_duration {33ms};

        if (duration < frame_duration) {
            const auto sleep_time {frame_duration - duration};
            std::this_thread::sleep_for(sleep_time);
            duration = frame_duration;
        }
    }
}

void Game::render()
{
    m_terminal.clear();

    render_map();
    render_colonists();

    m_backend->draw(m_terminal.glyphs());
}

void Game::render_map()
{
    for (int y {0}; y < m_map.dimension().height; ++y) {
        for (int x {0}; x < m_map.dimension().width; ++x) {
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
}

void Game::render_colonists()
{
    for (const auto& colonist : m_colonists) {
        m_terminal.write(colonist.position(), '@', colors::gray);
    }
}

void Game::handle_input()
{
    m_input_manager.clear();
    m_backend->poll_inputs(m_input_manager);

    if (m_input_manager.is_key_down(input::Key::Q)) {
        m_running = false;
    }
}

void Game::update()
{
    for (auto& colonist : m_colonists) {
        if (colonist.gain_energy()) {
            colonist.take_turn();
        }
    }
}
} // namespace oo
