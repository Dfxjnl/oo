#include "sdl_backend.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <fmt/core.h>

#include <cstddef>
#include <source_location>
#include <span>
#include <stdexcept>

#include "dimension.hpp"
#include "point.hpp"

namespace oo
{
SDLBackend::SDLBackend()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(fmt::format("{}: Failed to initialize SDL: {}",
                                             std::source_location::current().function_name(),
                                             SDL_GetError()));
    }

    m_window.reset(SDL_CreateWindow("oo",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    screen_dimension.width,
                                    screen_dimension.height,
                                    0));

    if (m_window == nullptr) {
        throw std::runtime_error(fmt::format("{}: Failed to create window: {}",
                                             std::source_location::current().function_name(),
                                             SDL_GetError()));
    }

    m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_PRESENTVSYNC));

    if (m_renderer == nullptr) {
        throw std::runtime_error(fmt::format("{}: Failed to create renderer: {}",
                                             std::source_location::current().function_name(),
                                             SDL_GetError()));
    }

    constexpr auto img_flags {IMG_INIT_PNG};

    if ((IMG_Init(img_flags) & img_flags) != img_flags) {
        throw std::runtime_error(fmt::format("{}: Failed to initialize SDL_image: {}",
                                             std::source_location::current().function_name(),
                                             IMG_GetError()));
    }

    SDL_Surface* font_surface {IMG_Load("data/terminal8x8.png")};

    if (font_surface == nullptr) {
        throw std::runtime_error(fmt::format("{}: Failed to load font: {}",
                                             std::source_location::current().function_name(),
                                             IMG_GetError()));
    }

    m_font_texture.reset(SDL_CreateTextureFromSurface(m_renderer.get(), font_surface));
    SDL_FreeSurface(font_surface);
}

SDLBackend::~SDLBackend()
{
    m_font_texture.reset();
    m_renderer.reset();
    m_window.reset();

    IMG_Quit();
    SDL_Quit();
}

void SDLBackend::draw(const std::span<const char> screen)
{
    SDL_SetRenderDrawColor(m_renderer.get(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(m_renderer.get());

    const Dimension ascii_dimension {console_size()};

    for (int y {0}; y < ascii_dimension.height; ++y) {
        for (int x {0}; x < ascii_dimension.width; ++x) {
            const Point screen_position {x * tile_size, y * tile_size};
            const char target_character {
                screen[static_cast<std::size_t>(y * ascii_dimension.width + x)]};
            const Point texture_position {(target_character % (tile_size * 2)) * tile_size,
                                          (target_character / (tile_size * 2)) * tile_size};

            const SDL_Rect source {texture_position.x, texture_position.y, tile_size, tile_size};
            const SDL_Rect destination {screen_position.x, screen_position.y, tile_size, tile_size};

            SDL_RenderCopy(m_renderer.get(), m_font_texture.get(), &source, &destination);
        }
    }

    SDL_RenderPresent(m_renderer.get());
}
} // namespace oo
