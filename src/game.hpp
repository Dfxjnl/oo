#ifndef OO_GAME_HPP
#define OO_GAME_HPP

#include "terminal.hpp"

namespace oo
{
class Game
{
public:
    Game();

private:
    Terminal m_terminal {
        {90, 30}
    };
};
} // namespace oo

#endif // OO_GAME_HPP
