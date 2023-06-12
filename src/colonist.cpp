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
    if (m_position.y > 0) {
        --m_position.y;
    }
}
} // namespace oo
