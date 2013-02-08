/*!
 * @header Dice
 * A representation of dice or a single die for use in games.
 */
#ifndef ARG3_DICE_H
#define ARG3_DICE_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

namespace arg3
{

    /*!
     * A die with a given number of sides
     */
    class Die
    {
    public:
        /*!
         * type of the value of die sides
         */
        typedef unsigned int value_type;

        /*!
         * Default number of sides on a die
         */
        static const value_type DEFAULT_SIDES = 6;

        /*!
         * Abstract class for the underlying random engine
         */
        class Engine
        {
        public:
            /*!
             * the random generator method
             * @param from the start range
             * @param to the end range
             */
            virtual Die::value_type generate(Die::value_type from, Die::value_type to) = 0;
        };

        /*!
         * Default implementation of the underlying random engine
         */
        class DefaultEngine : public Engine
        {
        public:
            /*!
             * the random generator method
             * @param from the starting range
             * @param to the ending range
             */
            Die::value_type generate(Die::value_type from, Die::value_type to);
        };

        /*!
         * An instanceof the default random engine
         */
        static Engine *const default_engine;

        /*!
         * custom sides constructor
         * throws exception if sides <= 0
         * @param sides the number of sides on this die
         * @param engine the die engine to use
         */
        Die(const unsigned int sides = DEFAULT_SIDES, Engine *const engine = default_engine);

        /*!
         * copy constructor
         * @param other the object to copy from
         */
        Die(const Die &other);

        /*!
         * assignment operator
         * @param rhs the right hand side of the operator
         */
        Die &operator=(const Die &rhs);

        /*!
         * deconstructor
         */
        virtual ~Die();

        /*!
         * returns the number of sides on the die
         */
        unsigned int sides() const;

        /*!
         * sets a flag to indicate this die is frozen
         * @param value the value to set
         */
        void keep(bool value);

        /*!
         * flag to indicate this die is frozen
         */
        bool keep() const;

        /*!
         * equality operator
         * @param rhs the right hand side of the operator
         */
        bool operator==(const Die &rhs) const;
        /*!
         * inequality operator
         * @param rhs the right hand side of the operator
         */
        bool operator!=(const Die &rhs) const;

        // cast operator
        operator value_type () const;

        /*!
         * sets the number of sides on the die
         * @param value the valude to set
         */
        void sides(const unsigned int value);

        /*!
         * current value of the die, or the side facing up
         */
        value_type value() const;

        // returns one of the sides on the die (random)
        value_type roll();

    private:
        Engine *m_engine;     // engine to use for dice rolling
        unsigned int m_sides; // number of sides on die
        value_type m_value;   // the current roll value
        bool m_keep;        // flag for not rolling a die
    };


    /*!
     * simple class to encapsulate a collection of dice which can be rolled
     * a bonus value can be given
     */
    class Dice
    {

    private:
        short m_bonus;
        vector<Die> m_dice;
        vector<Die::value_type> m_lastRoll;
    public:
        /*! iterator type for each die */
        typedef typename vector<Die>::iterator iterator;
        /*! const iterator type for each die */
        typedef typename vector<Die>::const_iterator const_iterator;

        /*!
         * create x dice with default number of sides
         * creates x dice with y sides
         * @param num the number of dice to create
         * @param sides the number of sides per die
         * @param engine the die engine to use
         */
        Dice(const unsigned int num, const unsigned int sides = Die::DEFAULT_SIDES, Die::Engine *const engine = Die::default_engine);

        /*!
         * copy constructor
         * @param other the other dice to copy
         */
        Dice(const Dice &other);

        /*!
         * assignment operator
         * @param rhs the right hand side of the assignment
         */
        Dice &operator= (const Dice &rhs);

        /*!
         * equality operator
         * @param rhs the right hand side of the operator
         */
        bool operator==(const Dice &rhs) const;
        /*!
         * inequality operator
         * @param rhs the right hand side of the operator
         */
        bool operator!=(const Dice &rhs) const;

        /*!
         * deconstructor
         */
        virtual ~Dice();

        // iterator methods
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        // const iterator methods
        const const_iterator cbegin() const;
        const const_iterator cend() const;

        // returns how many die in this collection
        unsigned int size() const;

        /*!
         * index operator
         * @param index the index
         */
        Die &operator[] ( size_t index);

        /*!
         * const index operator
         * @param index the index
         */
        const Die &operator[] ( size_t index) const;

        /*!
         * returns the bonus value
         */
        int bonus() const;

        /*!
         * sets the bonus value
         * @param value the bonus value to set
         */
        void bonus(const int value);

        // a string representation of the dice ex. 5d20
        const string to_string() const;

        // returns the values for each die in the last roll
        const vector<Die::value_type> &values() const;

        // return the total of rolling all dice
        const Die::value_type roll();
    };

    ostream &operator<< (ostream &, const Dice &);

}

#endif
