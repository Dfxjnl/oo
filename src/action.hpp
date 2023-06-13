#ifndef OO_ACTION_HPP
#define OO_ACTION_HPP

#include "point.hpp"

namespace oo
{
class Colonist;

class Action
{
public:
    constexpr Action() = default;
    constexpr Action(const Action&) = default;
    constexpr Action(Action&&) = default;
    constexpr auto operator=(const Action&) -> Action& = default;
    constexpr auto operator=(Action&&) -> Action& = default;
    constexpr virtual ~Action() = default;

    virtual void perform() = 0;
};

class MoveAction : public Action
{
public:
    constexpr explicit MoveAction(Colonist& colonist, const Point offset)
        : m_colonist {&colonist}
        , m_offset {offset}
    {
    }

    void perform() override;

private:
    Colonist* m_colonist {nullptr};
    Point m_offset;
};
} // namespace oo

#endif // OO_ACTION_HPP
