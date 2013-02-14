#include "engine.h"

namespace arg3
{

    namespace yacht
    {

        std::ostream &operator<<(std::ostream &stm, const Player &p)
        {
            stm << p.name();
            return stm;
        }

        Player::Player(const string &name, Die::Engine *const engine) : DiceGame(dieCount(), dieSides(), engine),
            m_score(), m_rollCount(0), m_name(name)
        {

        }
        Player::Player(const Player &other) : DiceGame(other), m_score(other.m_score), m_rollCount(other.m_rollCount),
            m_name(other.m_name)
        {

        }

        Player::~Player()
        {

        }

        Player &Player::operator=(const Player &other)
        {

            DiceGame::operator=(other);

            if (this != &other)
            {
                m_score = other.m_score;
                m_rollCount = other.m_rollCount;
                m_name = other.m_name;
            }
            return *this;
        }

        unsigned int Player::dieSides() const
        {
            return Die::DEFAULT_SIDES;
        }

        unsigned int Player::dieCount() const
        {
            return Constants::NUM_DICE;
        }

        void Player::keepDie(size_t index)
        {
            m_dice[index].keep(true);
        }

        const string &Player::name() const
        {
            return m_name;
        }

        ScoreSheet &Player::score()
        {
            return m_score;
        }

        bool Player::operator==(const Player &other) const
        {
            return m_name == other.m_name;
        }

        bool Player::operator!=(const Player &other) const
        {
            return !operator==(other);
        }

        ScoreSheet::value_type Player::calculateUpperScore(Die::value_type value) const
        {
            ScoreSheet::value_type score = 0;
for (auto & d : m_dice)
            {
                if (d.value() == value)
                    score += value;
            }
            return score;
        }



        ScoreSheet::value_type Player::calculateNumberOfAKind(int length) const
        {
            auto values = m_dice.values();

            sort(values.begin(), values.end());

            int count = 0;
            Die::value_type lastValue = 0;

for (auto & d : values)
            {
                if (lastValue != d)
                {
                    count = 0;
                    lastValue = d;
                }
                else
                {
                    if (++count == length - 1)
                    {
                        return calculateChance();
                    }
                }
            }
            return 0;
        }

        ScoreSheet::value_type Player::calculateFullHouse() const
        {
            auto values = m_dice.values();

            if (values.size() < 5)
                return 0;

            sort(values.begin(), values.end());

            if (
                (
                    (values[0] == values[1]) &&
                    (values[1] == values[2]) &&
                    (values[3] == values[4]) &&
                    (values[2] != values[3])
                ) ||
                (
                    (values[0] == values[1]) &&
                    (values[1] != values[2]) &&
                    (values[2] == values[3]) &&
                    (values[3] == values[4])
                )
            )
            {
                return 25;
            }

            return 0;
        }

        ScoreSheet::value_type Player::calculateStraight(int length) const
        {
            auto values = m_dice.values();

            sort(values.begin(), values.end());

            Die::value_type test = 0;

            int count = 0;

for (auto & d : values)
            {
                if (test == 0)
                {

                    test = d;
                    continue;
                }
                if (test + 1 == d)
                {
                    if (++count == length)
                    {
                        return length * 10;
                    }
                }

                test = d;
            }
            return 0;
        }

        ScoreSheet::value_type Player::calculateChance() const
        {
            ScoreSheet::value_type value = 0;
for (auto & d : m_dice.values())
            {
                value += d;
            }
            return value;
        }

        pair<ScoreSheet::Type, ScoreSheet::value_type> Player::calculateBestLowerScore() const
        {
            ScoreSheet::value_type value = 0;
            ScoreSheet::Type type = ScoreSheet::MAX_TYPE;

            for (auto t = ScoreSheet::FIRST_TYPE; t < ScoreSheet::MAX_TYPE; t++)
            {
                if (m_score.lowerScore(t) != 0) continue;

                auto score = calculateLowerScore(t);
                if (score > value)
                {
                    type = t;
                    value = score;
                }
            }
            return make_pair(type, value);
        }

        pair<Die::value_type, ScoreSheet::value_type> Player::calculateBestUpperScore() const
        {
            Die::value_type type = 0;
            ScoreSheet::value_type value = 0;

            for (Die::value_type d = 1; d <= Die::DEFAULT_SIDES; d++)
            {

                if (m_score.upperScore(d) != 0) continue;

                auto score = calculateUpperScore(d);

                if (score > value)
                {
                    type = d;
                    value = score;
                }
            }

            return make_pair(type, value);
        }

        ScoreSheet::value_type Player::calculateBestScore() const
        {
            auto lower = calculateBestLowerScore();

            auto higher = calculateBestUpperScore();

            return max(lower.second, higher.second);
        }

        ScoreSheet::value_type Player::calculateYacht() const
        {
            auto values = m_dice.values();

            sort(values.begin(), values.end());

            if (values.front() == values.back())
                return 50;

            return 0;
        }

        ScoreSheet::value_type Player::calculateLowerScore(ScoreSheet::Type type) const
        {
            switch (type)
            {
            case ScoreSheet::KIND_THREE:
                return calculateNumberOfAKind(Constants::NUM_DICE - 2);
            case ScoreSheet::KIND_FOUR:
                return calculateNumberOfAKind(Constants::NUM_DICE - 1);
            case ScoreSheet::FULL_HOUSE:
                return calculateFullHouse();
            case ScoreSheet::STRAIGHT_SMALL:
                return calculateStraight(Constants::NUM_DICE - 2);
            case ScoreSheet::STRAIGHT_BIG:
                return calculateStraight(Constants::NUM_DICE - 1);
            case ScoreSheet::YACHT:
                return calculateYacht();
            case ScoreSheet::CHANCE:
                return calculateChance();
            default:
                return 0;
            }
        }

    }

}