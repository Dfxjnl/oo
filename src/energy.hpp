#ifndef OO_ENERGY_HPP
#define OO_ENERGY_HPP

namespace oo
{
class Energy
{
public:
    [[nodiscard]] constexpr auto can_take_turn() const noexcept { return m_energy >= action_cost; }

    constexpr auto gain() noexcept
    {
        ++m_energy;

        if (!can_take_turn()) {
            return false;
        }

        m_energy -= action_cost;
        return true;
    }

private:
    static constexpr auto action_cost {4};

    int m_energy {0};
};
} // namespace oo

#endif // OO_ENERGY_HPP
