#ifndef OO_GRAPHICS_BACKEND_HPP
#define OO_GRAPHICS_BACKEND_HPP

#include <span>

#include "dimension.hpp"

namespace oo
{
struct Glyph;

class GraphicsBackend
{
public:
    virtual ~GraphicsBackend() = default;

    virtual void draw(std::span<const Glyph> screen) = 0;
    [[nodiscard]] virtual auto console_size() const -> Dimension = 0;
};
} // namespace oo

#endif // OO_GRAPHICS_BACKEND_HPP
