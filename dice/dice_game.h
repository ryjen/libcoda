/*!
 * @header Dice Game
 * Abstract class for a game of dice
 */
#ifndef ARG3_DICE_GAME_H
#define ARG3_DICE_GAME_H

#include "dice.h"

namespace arg3
{

    /*!
     * class representing a game of dice
     */
    class DiceGame
    {
    protected:
        Dice m_dice;

        DiceGame(unsigned int, unsigned int, Die::Engine * = Die::default_engine);
        DiceGame(const DiceGame &);
        DiceGame &operator=(const DiceGame &);
        virtual ~DiceGame();
    public:
        // rolls the dice for the game
        void roll();
        // returns the values of the dice for the game
        const vector<Die::value_type> &values() const;

        // equality operator
        bool operator==(const DiceGame &) const;
        // inequality operator
        bool operator!=(const DiceGame &) const;
    };

}

#endif
