#include "game.hpp"

#include <fmt/core.h>

#include <chrono>
#include <compare>
#include <deque>
#include <memory>
#include <ratio>
#include <thread>

#include "action.hpp"
#include "avatar.hpp"
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
namespace
{
constexpr int stats_offset {20};
}

Game::Game()
    : m_backend {std::make_unique<SDLBackend>()}
    , m_terminal {m_backend->console_size()}
    , m_map {{m_backend->console_size().width - stats_offset - 1, m_backend->console_size().height}}
    , m_avatar{{.x = m_backend->console_size().width / 2, .y = m_backend->console_size().height / 2}}
{
    m_map.set_tile({5, 10}, TileType::Tree);
    m_map.set_tile({5, 11}, TileType::Tree);
    m_map.set_tile({5, 12}, TileType::Tree);
    m_map.set_tile({5, 13}, TileType::Tree);
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
    render_stats();
    render_log();

    m_backend->draw(m_terminal.glyphs());
}

void Game::render_map()
{
    for (int y {0}; y < m_map.dimension().height; ++y) {
        for (int x {0}; x < m_map.dimension().width; ++x) {
            const Point point {x, y};
            const auto& tile {m_map.tile_at(point)};

            if (tile.explored) {
                switch (tile.type) {
                case TileType::Grass: {
                    m_terminal.write(point, '.', tile.visible ? colors::green : colors::dark_gray);
                } break;

                case TileType::Tree: {
                    m_terminal.write(point, '&', tile.visible ? colors::orange : colors::dark_gray);
                } break;
                }
            } else {
                m_terminal.write(point, ' ');
            }
        }
    }
}

void Game::render_colonists()
{
    m_terminal.write(m_avatar.position(), Avatar::glyph);
}

void Game::render_log()
{
    int y_offset {m_terminal.dimension().height - static_cast<int>(m_log.messages().size())};

    for (const auto& message : m_log.messages()) {
        m_terminal.write({0, y_offset}, message.text);

        if (message.count > 1) {
            m_terminal.write({static_cast<int>(message.text.length()), y_offset},
                             fmt::format("x{}", message.count),
                             colors::gray);
        }

        ++y_offset;
    }
}

void Game::render_stats()
{
    m_terminal.write({m_terminal.dimension().width - stats_offset, 1}, "oo");
}

void Game::handle_input()
{
    m_input_manager.clear();
    m_backend->poll_inputs(m_input_manager);

    if (m_input_manager.is_key_down(input::Key::Q)) {
        m_running = false;
    } else if (m_input_manager.is_key_down(input::Key::Up)) {
        m_avatar.set_next_action(std::make_unique<MoveAction>(m_avatar, Point {0, -1}));
    } else if (m_input_manager.is_key_down(input::Key::Down)) {
        m_avatar.set_next_action(std::make_unique<MoveAction>(m_avatar, Point {0, 1}));
    } else if (m_input_manager.is_key_down(input::Key::Left)) {
        m_avatar.set_next_action(std::make_unique<MoveAction>(m_avatar, Point {-1, 0}));
    } else if (m_input_manager.is_key_down(input::Key::Right)) {
        m_avatar.set_next_action(std::make_unique<MoveAction>(m_avatar, Point {1, 0}));
    }
}

void Game::update()
{
    update_fov();

    if (m_avatar.can_take_turn() && m_avatar.needs_input()) {
        return;
    }

    if (m_avatar.gain_energy()) {
        if (m_avatar.needs_input()) {
            return;
        }

        const auto action {m_avatar.take_turn()};
        action->perform(*this);
        m_visibility_dirty = true;
    }
}

void Game::update_fov()
{
    if (m_visibility_dirty) {
        m_map.reset_visibility();
        m_map.make_radius_visible(m_avatar.position(), 8);
    }
}
} // namespace oo
