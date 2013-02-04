#include "dice_game.h"

namespace arg3
{
    DiceGame::DiceGame(unsigned int count, unsigned int sides, Die::Engine *const engine) : mDice(count, sides, engine)
    {

    }

    DiceGame::DiceGame(const DiceGame &other) : mDice(other.mDice)
    {

    }

    DiceGame::~DiceGame()
    {

    }

    DiceGame &DiceGame::operator=(const DiceGame &other)
    {

        if (this != &other)
        {
            mDice = other.mDice;
        }
        return *this;
    }

    void DiceGame::roll()
    {
        mDice.roll();
    }

    const vector<Die::value_type> &DiceGame::values() const
    {
        return mDice.values();
    }

    bool DiceGame::operator==(const DiceGame &other) const
    {
        return mDice == other.mDice;
    }

    bool DiceGame::operator!=(const DiceGame &other) const
    {
        return !operator==(other);
    }
}
