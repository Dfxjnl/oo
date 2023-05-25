#include "game.hpp"

#include <fmt/core.h>

#include <source_location>

namespace oo
{
Game::Game()
{
    fmt::print("{}\n", std::source_location::current().function_name());
}
} // namespace oo
