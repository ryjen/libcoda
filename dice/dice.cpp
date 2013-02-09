
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

        static std::default_random_engine random_engine(time(0));

        uniform_int_distribution<Die::value_type> distribution(from, to);

        return distribution(random_engine);
    }

    Die::Die(const unsigned int sides, Die::Engine *const engine) : m_engine(engine), m_value(0), m_keep(false)
    {
        if (sides == 0)
        {
            throw new invalid_argument("Dice must have one or more sides.");
        }

        m_sides = sides;
    }

    Die::Die(const Die &other) : m_engine(other.m_engine), m_sides(other.m_sides), m_value(other.m_value), m_keep(other.m_keep)
    {
    }

    Die &Die::operator= (const Die &other)
    {
        if (this != &other)
        {
            m_engine = other.m_engine;
            m_sides = other.m_sides;
            m_value = other.m_value;
            m_keep = other.m_keep;
        }
        return *this;
    }

    Die::~Die()
    {
        // nothing to do
    }

    bool Die::operator== (const Die &rhs) const
    {
        return m_value == rhs.m_value;
    }

    bool Die::operator!= (const Die &rhs) const
    {
        return !operator==(rhs);
    }

    Die::operator value_type() const
    {
        return m_value;
    }

    /*
     * returns the number of sides on the die
     */
    unsigned int Die::sides() const
    {
        return m_sides;
    }

    /*
     * sets the number of sides on the die
     */
    void Die::sides(const unsigned int value)
    {
        m_sides = value;
    }

    Die::value_type Die::value() const
    {
        return m_value;
    }

// returns one of the sides on the die (random)
    Die::value_type Die::roll()
    {
        assert(m_engine != 0);

        m_value = m_engine->generate(1, m_sides + 1);

        return m_value;
    }

    void Die::keep(bool value)
    {
        m_keep = value;
    }

    bool Die::keep() const
    {
        return m_keep;
    }

// #######################################################################################################
// Dice
// #######################################################################################################

// creates x dice with y sides
    Dice::Dice(const unsigned int count, const unsigned int sides, Die::Engine *const engine) : m_bonus(0), m_dice(), m_lastRoll()
    {
        for (int i = 0; i < count; i++)
            m_dice.push_back(Die(sides, engine));
    }

// copy constructor
    Dice::Dice(const Dice &other) : m_bonus(other.m_bonus), m_dice(other.m_dice), m_lastRoll(other.m_lastRoll)
    {
    }

    Dice &Dice::operator=(const Dice &other)
    {
        if (this != &other)
        {
            m_bonus = other.m_bonus;
            m_dice = other.m_dice;
            m_lastRoll = other.m_lastRoll;
        }
        return *this;
    }

    bool Dice::operator==(const Dice &other) const
    {
        return m_bonus == other.m_bonus && m_dice == other.m_dice && m_lastRoll == other.m_lastRoll;
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
        return m_dice.begin();
    }

    Dice::const_iterator Dice::begin() const
    {
        return m_dice.begin();
    }

// const iterator methods
    const Dice::const_iterator Dice::cbegin() const
    {
        return m_dice.cbegin();
    }

    Dice::iterator Dice::end()
    {
        return m_dice.end();
    }

    Dice::const_iterator Dice::end() const
    {
        return m_dice.end();
    }

    const Dice::const_iterator Dice::cend() const
    {
        return m_dice.cend();
    }

    unsigned int Dice::size() const
    {
        return m_dice.size();
    }

    /*
     * returns the bonus value
     */
    int Dice::bonus() const
    {
        return m_bonus;
    }

    /*
     * sets the bonus value
     */
    void Dice::bonus(const int value)
    {
        m_bonus = value;
    }

// a string representation of the dice ex. 5d20
    const string Dice::to_string() const
    {
        stringstream buf;

        size_t size = m_dice.size();

        buf << size;

        if (size > 0)
        {
            buf << "d" << m_dice.begin()->sides();
        }

        if (m_bonus > 0)
        {
            buf << "+" << m_bonus;
        }
        return buf.str();
    }

// returns the values for each die in the last roll
    const vector<Die::value_type> &Dice::values() const
    {
        return m_lastRoll;
    }

// return the total of rolling all dice
    const unsigned int Dice::roll()
    {
        Die::value_type value = 0;

        m_lastRoll.clear(); // reset the last roll values

for (Die & d : m_dice)
        {
            auto roll = d.keep() ? d.value() : d.roll(); // roll the die
            value += roll; // sum the total
            // save each value for use later
            m_lastRoll.push_back(roll);
        }
        return value + bonus(); // add the bonus
    }

    Die &Dice::operator[] ( size_t n )
    {
        return m_dice[n];
    }

    const Die &Dice::operator[] ( size_t n ) const
    {
        return m_dice[n];
    }

    ostream &operator<< (ostream &out, const Dice &dice)
    {
        out << dice.to_string();
        return out;
    }

}
