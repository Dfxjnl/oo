#include "colonist.hpp"

#include "rng.hpp"

namespace oo
{
auto Colonist::gain_energy() -> bool
{
    return m_energy.gain();
}

void Colonist::take_turn()
{
    switch (m_rng->get(0, 3)) {
    case 0: {
        if (m_position.y > 0) {
            move({0, -1});
        }
    } break;

    case 1: {
        if (m_position.y < 19) {
            move({0, 1});
        }
    } break;

    case 2: {
        if (m_position.x > 0) {
            move({-1, 0});
        }
    } break;

    case 3: {
        if (m_position.x < 49) {
            move({1, 0});
        }
    } break;
    }
}
} // namespace oo
