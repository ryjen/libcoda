#include "dice_game.h"

namespace arg3
{
    DiceGame::DiceGame(unsigned int count, unsigned int sides, Die::Engine *const engine) : m_dice(count, sides, engine)
    {

    }

    DiceGame::DiceGame(const DiceGame &other) : m_dice(other.m_dice)
    {

    }

    DiceGame::~DiceGame()
    {

    }

    DiceGame &DiceGame::operator=(const DiceGame &other)
    {

        if (this != &other)
        {
            m_dice = other.m_dice;
        }
        return *this;
    }

    void DiceGame::roll()
    {
        m_dice.roll();
    }

    const vector<Die::value_type> &DiceGame::values() const
    {
        return m_dice.values();
    }

    bool DiceGame::operator==(const DiceGame &other) const
    {
        return m_dice == other.m_dice;
    }

    bool DiceGame::operator!=(const DiceGame &other) const
    {
        return !operator==(other);
    }
}
