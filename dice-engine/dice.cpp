
#include <random>
#include <functional>
#include "dice.h"
#include <cassert>

namespace arg3
{
    // #######################################################################################################
    // Die
    // #######################################################################################################

    // randomness for dice rolls
    static Die::DefaultEngine default_die_engine = Die::DefaultEngine();

    const Die::value_type Die::DEFAULT_SIDES;

    Die::Engine *const Die::default_engine = &default_die_engine;

    Die::value_type Die::DefaultEngine::generate(Die::value_type from, Die::value_type to)
    {

        static std::default_random_engine randomEngine(time(0));

        uniform_int_distribution<Die::value_type> distribution(from, to);

        return distribution(randomEngine);
    }

    Die::Die(const unsigned int sides, Die::Engine *const engine) : mEngine(engine), mValue(0), mFrozen(false)
    {
        if (sides == 0)
        {
            throw new invalid_argument("Dice must have one or more sides.");
        }

        mSides = sides;
    }

    Die::Die(const Die &other) : mEngine(other.mEngine), mSides(other.mSides), mValue(other.mValue), mFrozen(other.mFrozen)
    {
    }

    Die &Die::operator= (const Die &other)
    {
        if (this != &other)
        {
            mEngine = other.mEngine;
            mSides = other.mSides;
            mValue = other.mValue;
            mFrozen = other.mFrozen;
        }
        return *this;
    }

    Die::~Die()
    {
        // nothing to do
    }

    bool Die::operator== (const Die &rhs) const
    {
        return mValue == rhs.mValue;
    }

    bool Die::operator!= (const Die &rhs) const
    {
        return !operator==(rhs);
    }

    Die::operator value_type() const
    {
        return mValue;
    }

    /*
     * returns the number of sides on the die
     */
    unsigned int Die::sides() const
    {
        return mSides;
    }

    /*
     * sets the number of sides on the die
     */
    void Die::sides(const unsigned int value)
    {
        mSides = value;
    }

    Die::value_type Die::value() const
    {
        return mValue;
    }

    // returns one of the sides on the die (random)
    Die::value_type Die::roll()
    {
        assert(mEngine != 0);

        mValue = mEngine->generate(1, mSides + 1);

        return mValue;
    }

    void Die::frozen(bool value)
    {
        mFrozen = value;
    }

    bool Die::frozen() const
    {
        return mFrozen;
    }

    // #######################################################################################################
    // Dice
    // #######################################################################################################

    // creates x dice with y sides
    Dice::Dice(const unsigned int count, const unsigned int sides, Die::Engine *const engine) : mBonus(0), mDice(), mLastRoll()
    {
        for (int i = 0; i < count; i++)
            mDice.push_back(Die(sides, engine));
    }

    // copy constructor
    Dice::Dice(const Dice &other) : mBonus(other.mBonus), mDice(other.mDice), mLastRoll(other.mLastRoll)
    {
    }

    Dice &Dice::operator=(const Dice &other)
    {
        if (this != &other)
        {
            mBonus = other.mBonus;
            mDice = other.mDice;
            mLastRoll = other.mLastRoll;
        }
        return *this;
    }

    bool Dice::operator==(const Dice &other) const
    {
        return mBonus == other.mBonus && mDice == other.mDice && mLastRoll == other.mLastRoll;
    }

    bool Dice::operator!=(const Dice &other) const
    {
        return !operator==(other);
    }

    // deconstructor
    Dice::~Dice()
    {

    }

    // iterator methods
    Dice::iterator Dice::begin()
    {
        return mDice.begin();
    }

    Dice::const_iterator Dice::begin() const
    {
        return mDice.begin();
    }

    // const iterator methods
    const Dice::const_iterator Dice::cbegin() const
    {
        return mDice.cbegin();
    }

    Dice::iterator Dice::end()
    {
        return mDice.end();
    }

    Dice::const_iterator Dice::end() const
    {
        return mDice.end();
    }

    const Dice::const_iterator Dice::cend() const
    {
        return mDice.cend();
    }

    unsigned int Dice::size() const
    {
        return mDice.size();
    }

    /*
     * returns the bonus value
     */
    int Dice::bonus() const
    {
        return mBonus;
    }

    /*
     * sets the bonus value
     */
    void Dice::bonus(const int value)
    {
        mBonus = value;
    }

    // a string representation of the dice ex. 5d20
    const string Dice::to_string() const
    {
        stringstream buf;

        size_t size = mDice.size();

        buf << size;

        if (size > 0)
        {
            buf << "d" << mDice.begin()->sides();
        }

        if (mBonus > 0)
        {
            buf << "+" << mBonus;
        }
        return buf.str();
    }

    // returns the values for each die in the last roll
    const vector<Die::value_type> &Dice::values() const
    {
        return mLastRoll;
    }

    // return the total of rolling all dice
    const unsigned int Dice::roll()
    {
        Die::value_type value = 0;

        mLastRoll.clear(); // reset the last roll values

        for (Die & d : mDice)
        {
            auto roll = d.frozen() ? d.value() : d.roll(); // roll the die
            value += roll; // sum the total
            // save each value for use later
            mLastRoll.push_back(roll);
        }
        return value + bonus(); // add the bonus
    }

    Die &Dice::operator[] ( size_t n )
    {
        return mDice[n];
    }

    const Die &Dice::operator[] ( size_t n ) const
    {
        return mDice[n];
    }

    ostream &operator<< (ostream &out, const Dice &dice)
    {
        out << dice.to_string();
        return out;
    }

}
