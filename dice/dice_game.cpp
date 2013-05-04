#include "dice_game.h"

namespace arg3
{
    DiceGame::DiceGame(unsigned int count, unsigned int sides, Die::Engine *const engine) : dice_(count, sides, engine)
    {

    }

    DiceGame::DiceGame(const DiceGame &other) : dice_(other.dice_)
    {

    }

    DiceGame::DiceGame(DiceGame &&other) : dice_(std::move(other.dice_))
    {}

    DiceGame::~DiceGame()
    {

    }

    DiceGame &DiceGame::operator=(const DiceGame &other)
    {

        if (this != &other)
        {
            dice_ = other.dice_;
        }
        return *this;
    }

    DiceGame &DiceGame::operator=(DiceGame &&other)
    {

        if (this != &other)
        {
            dice_ = std::move(other.dice_);
        }
        return *this;
    }
    
    void DiceGame::roll()
    {
        dice_.roll();
    }

    const vector<Die::value_type> &DiceGame::values() const
    {
        return dice_.values();
    }

    bool DiceGame::operator==(const DiceGame &other) const
    {
        return dice_ == other.dice_;
    }

    bool DiceGame::operator!=(const DiceGame &other) const
    {
        return !operator==(other);
    }
}
