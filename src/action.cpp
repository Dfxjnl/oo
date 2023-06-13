#include "action.hpp"

#include "colonist.hpp"

namespace oo
{
void MoveAction::perform()
{
    m_colonist->move(m_offset);
}
} // namespace oo
