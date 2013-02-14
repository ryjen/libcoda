/*!
     @header Yacht Player
     The Yacht Player provides a functional interface to a player in a game of Yacht.
     Use the functions declared here to handle gameplay.
     @copyright ryan jennings (arg3.com) 2012 LGPL
     @updated 2012-09-09
 */
#ifndef ARG3_YACHT_PLAYER_H
#define ARG3_YACHT_PLAYER_H

#include "../dice_game.h"
#include "scoresheet.h"

namespace arg3
{

    namespace yacht
    {

        /*!
         * @class Player
         * A player in a game of yacht
         */
        class Player : public DiceGame
        {
            friend std::ostream &operator<<(std::ostream &stm, const Player & );

        public:
            /*!
             * number of sides in a die
             */
            unsigned int dieSides() const;

            /*!
             * number of die
             */
            unsigned int dieCount() const;

            /*!
             * default constructor takes a name
             * @param name
             * the name given to a player
             * @param engine
             * the die engine to use
             */
            Player(const string &name, Die::Engine *const = Die::default_engine);

            /*!
             * copy constructor
             */
            Player(const Player &);

            /*!
             * assignment operator
             */
            Player &operator=(const Player &);

            /*!
             * destructor
             */
            virtual ~Player();

            /*!
             * keeps a die
             */
            void keepDie(size_t index);

            /*!
             * calculate a value on the lower part of scoresheet
             * @param type
             * the type of lower score
             */
            ScoreSheet::value_type calculateLowerScore(ScoreSheet::Type) const;

            /*!
             * calcualte a value on the upper part of scoresheet
             * @param type
             * the type of upper score
             */
            ScoreSheet::value_type calculateUpperScore(Die::value_type) const;

            /*!
             * calculates the best score available in hand
             */
            ScoreSheet::value_type calculateBestScore() const;

            pair<ScoreSheet::Type, ScoreSheet::value_type> calculateBestLowerScore() const;

            pair<Die::value_type, ScoreSheet::value_type> calculateBestUpperScore() const;


            ScoreSheet &score();

            /*!
             * name of the player
             */
            const string &name() const;

            /*!
             * equality operator
             */
            bool operator==(const Player &) const;

            /*!
             * equality operator
             */
            bool operator!=(const Player &) const;

        private:

            ScoreSheet::value_type calculateNumberOfAKind(int) const;
            ScoreSheet::value_type calculateFullHouse() const;
            ScoreSheet::value_type calculateStraight(int) const;
            ScoreSheet::value_type calculateChance() const;
            ScoreSheet::value_type calculateYacht() const;

            ScoreSheet m_score;  // the score sheet
            unsigned short m_rollCount; // number of die rolls
            string m_name;   // player name
        };

    }

}

#endif
