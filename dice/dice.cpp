
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

    Die::Die(const unsigned int sides, Die::Engine *const engine) : engine_(engine), value_(0), keep_(false)
    {
        if (sides == 0)
        {
            throw new invalid_argument("Dice must have one or more sides.");
        }

        sides_ = sides;
    }

    Die::Die(const Die &other) : engine_(other.engine_), sides_(other.sides_), value_(other.value_), keep_(other.keep_)
    {
    }

    Die::Die(Die &&other) : engine_(std::move(other.engine_)), sides_(other.sides_), value_(other.value_), keep_(other.keep_)
    {}

    Die &Die::operator= (const Die &other)
    {
        if (this != &other)
        {
            engine_ = other.engine_;
            sides_ = other.sides_;
            value_ = other.value_;
            keep_ = other.keep_;
        }
        return *this;
    }

    Die &Die::operator= (Die &&other)
    {
        if (this != &other)
        {
            engine_ = std::move(other.engine_);
            sides_ = other.sides_;
            value_ = other.value_;
            keep_ = other.keep_;
        }
        return *this;
    }

    Die::~Die()
    {
        // nothing to do
    }

    bool Die::operator== (const Die &rhs) const
    {
        return value_ == rhs.value_;
    }

    bool Die::operator!= (const Die &rhs) const
    {
        return !operator==(rhs);
    }

    Die::operator value_type() const
    {
        return value_;
    }

    /*
     * returns the number of sides on the die
     */
    unsigned int Die::sides() const
    {
        return sides_;
    }

    /*
     * sets the number of sides on the die
     */
    void Die::sides(const unsigned int value)
    {
        sides_ = value;
    }

    Die::value_type Die::value() const
    {
        return value_;
    }

    // returns one of the sides on the die (random)
    Die::value_type Die::roll()
    {
        assert(engine_ != 0);

        value_ = engine_->generate(1, sides_ + 1);

        return value_;
    }

    void Die::keep(bool value)
    {
        keep_ = value;
    }

    bool Die::keep() const
    {
        return keep_;
    }

    // #######################################################################################################
    // Dice
    // #######################################################################################################

    // creates x dice with y sides
    Dice::Dice(const unsigned int count, const unsigned int sides, Die::Engine *const engine) : bonus_(0), dice_(), lastRoll_()
    {
        for (int i = 0; i < count; i++)
            dice_.push_back(Die(sides, engine));
    }

    // copy constructor
    Dice::Dice(const Dice &other) : bonus_(other.bonus_), dice_(other.dice_), lastRoll_(other.lastRoll_)
    {
    }

    // move constructor
    Dice::Dice(Dice &&other) : bonus_(other.bonus_), dice_(std::move(other.dice_)), lastRoll_(std::move(other.lastRoll_))
    {
    }

    Dice &Dice::operator=(const Dice &other)
    {
        if (this != &other)
        {
            bonus_ = other.bonus_;
            dice_ = other.dice_;
            lastRoll_ = other.lastRoll_;
        }
        return *this;
    }

    Dice &Dice::operator=(Dice &&other)
    {
        if (this != &other)
        {
            bonus_ = other.bonus_;
            dice_ = std::move(other.dice_);
            lastRoll_ = std::move(other.lastRoll_);
        }
        return *this;
    }

    bool Dice::operator==(const Dice &other) const
    {
        return bonus_ == other.bonus_ && dice_ == other.dice_ && lastRoll_ == other.lastRoll_;
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
        return dice_.begin();
    }

    Dice::const_iterator Dice::begin() const
    {
        return dice_.begin();
    }

    // const iterator methods
    const Dice::const_iterator Dice::cbegin() const
    {
        return dice_.cbegin();
    }

    Dice::iterator Dice::end()
    {
        return dice_.end();
    }

    Dice::const_iterator Dice::end() const
    {
        return dice_.end();
    }

    const Dice::const_iterator Dice::cend() const
    {
        return dice_.cend();
    }

    unsigned int Dice::size() const
    {
        return dice_.size();
    }

    /*
     * returns the bonus value
     */
    int Dice::bonus() const
    {
        return bonus_;
    }

    /*
     * sets the bonus value
     */
    void Dice::bonus(const int value)
    {
        bonus_ = value;
    }

    // a string representation of the dice ex. 5d20
    const string Dice::to_string() const
    {
        stringstream buf;

        size_t size = dice_.size();

        buf << size;

        if (size > 0)
        {
            buf << "d" << dice_.begin()->sides();
        }

        if (bonus_ > 0)
        {
            buf << "+" << bonus_;
        }
        return buf.str();
    }

    // returns the values for each die in the last roll
    const vector<Die::value_type> &Dice::values() const
    {
        return lastRoll_;
    }

    // return the total of rolling all dice
    const unsigned int Dice::roll()
    {
        Die::value_type value = 0;

        lastRoll_.clear(); // reset the last roll values

        for (Die & d : dice_)
        {
            auto roll = d.keep() ? d.value() : d.roll(); // roll the die
            value += roll; // sum the total
            // save each value for use later
            lastRoll_.push_back(roll);
        }
        return value + bonus(); // add the bonus
    }

    Die &Dice::operator[] ( size_t n )
    {
        return dice_[n];
    }

    const Die &Dice::operator[] ( size_t n ) const
    {
        return dice_[n];
    }

    ostream &operator<< (ostream &out, const Dice &dice)
    {
        out << dice.to_string();
        return out;
    }

}
