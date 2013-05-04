/*!
 * @header Yacht ScoreSheet
 * The Yacht ScoreSheet provides an interfaces to tracking scores in a game of Yacht
 */
#ifndef ARG3_YACHT_SCORE_H
#define ARG3_YACHT_SCORE_H

#include <array>
#include "../dice.h"
#include "constants.h"

using namespace std;

namespace arg3
{

    namespace yacht
    {

        /*!
         * Class to track scores
         */
        class ScoreSheet
        {
        public:

            /*! Underlying type to store scores */
            typedef unsigned short value_type;

            /*! Types of scoring */
            typedef enum
            {
                /*! three of a kind */
                KIND_THREE,
                /*! four of a kind */
                KIND_FOUR,
                /*! full house */
                FULL_HOUSE,
                /*! straight of 4 */
                STRAIGHT_SMALL,
                /*! straight of 5 */
                STRAIGHT_BIG,
                /*! 5 of a kind */
                YACHT,
                /*! total of dice */
                CHANCE,
                /*! maximum type for looping */
                MAX_TYPE,
                /*! first type for looping */
                FIRST_TYPE = KIND_THREE
            } Type;

            /*! default constructor */
            ScoreSheet();

            /*!
             * copy constructor
             * @param other the object to copy from
             */
            ScoreSheet(const ScoreSheet &other);

            ScoreSheet(ScoreSheet &&other);

            /*!
             * destructor
             */
            virtual ~ScoreSheet();

            /*!
             * assignment operator
             * @param rhs the right hand side of the operator
             */
            ScoreSheet &operator=(const ScoreSheet &rhs);

            ScoreSheet &operator=(ScoreSheet &&rhs);

            /*!
             * sets a score on the lower page
             * @param type the type of score
             * @param value the value to set
             */
            void lowerScore(Type type, ScoreSheet::value_type value);

            /*!
             * sets a score on the upper page
             * @param type the type of score
             * @param value the value to set
             */
            void upperScore(Die::value_type type, ScoreSheet::value_type value);

            /*!
             * resets/clears the score
             */
            void reset();

            /*!
             * gets the upper score
             * @param type the type of score to get
             */
            ScoreSheet::value_type lowerScore(Type type) const;

            /*!
             * gets the lower score
             * @param type the type of score to get
             */
            ScoreSheet::value_type upperScore(Die::value_type type) const;

        private:
            array<value_type, MAX_TYPE> upperValues_;
            array<value_type, Constants::NUM_DICE> lowerValues_;
        };

    }

}

#endif
