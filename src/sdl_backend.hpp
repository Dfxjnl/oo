#ifndef OO_SDL_BACKEND_HPP
#define OO_SDL_BACKEND_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <memory>
#include <span>

#include "dimension.hpp"
#include "graphics_backend.hpp"

namespace oo
{
namespace sdl
{
struct SDLDeleter
{
    void operator()(SDL_Window* window) noexcept { SDL_DestroyWindow(window); }

    void operator()(SDL_Renderer* renderer) noexcept { SDL_DestroyRenderer(renderer); }

    void operator()(SDL_Texture* texture) noexcept { SDL_DestroyTexture(texture); }
};

using Window = std::unique_ptr<SDL_Window, SDLDeleter>;
using Renderer = std::unique_ptr<SDL_Renderer, SDLDeleter>;
using Texture = std::unique_ptr<SDL_Texture, SDLDeleter>;
} // namespace sdl

class SDLBackend : public GraphicsBackend
{
public:
    SDLBackend();
    SDLBackend(const SDLBackend&) = delete;
    SDLBackend(SDLBackend&&) = default;
    auto operator=(const SDLBackend&) -> SDLBackend& = delete;
    auto operator=(SDLBackend&&) -> SDLBackend& = default;
    ~SDLBackend() override;

    void draw(std::span<const char> screen) override;

    [[nodiscard]] constexpr auto console_size() const noexcept -> Dimension override
    {
        return screen_dimension / tile_size;
    }

private:
    static constexpr Dimension screen_dimension {1280, 720};
    static constexpr int tile_size {8};

    sdl::Window m_window {nullptr};
    sdl::Renderer m_renderer {nullptr};
    sdl::Texture m_font_texture {nullptr};
};
} // namespace oo

#endif // OO_SDL_BACKEND_HPP
