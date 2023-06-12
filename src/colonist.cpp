#include "colonist.hpp"

namespace oo
{
void Colonist::update()
{
    if (m_energy.update()) {
        take_turn();
    }
}

void Colonist::take_turn()
{
    switch (m_rng->get(0, 3)) {
    case 0: {
        if (m_position.y > 0) {
            --m_position.y;
        }
    } break;

    case 1: {
        if (m_position.y < 19) {
            ++m_position.y;
        }
    } break;

    case 2: {
        if (m_position.x > 0) {
            --m_position.x;
        }
    } break;

    case 3: {
        if (m_position.x < 49) {
            ++m_position.x;
        }
    } break;
    }
}
} // namespace oo
