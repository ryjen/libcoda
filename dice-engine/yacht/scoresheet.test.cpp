#include <igloo/igloo.h>
#include "scoresheet.h"
#include "constants.h"
#include "../dice.h"

using namespace igloo;
using namespace arg3;
using namespace arg3::yacht;

Context(ScoreSheetTest)
{
    ScoreSheet *score;

    void SetUp()
    {
        score = new ScoreSheet();
    }

    void TearDown()
    {
        delete score;
    }

    Spec(setOnes)
    {
        score->upperScore(1, 1 * Constants::NUM_DICE);

        Assert::That(score->upperScore(1), Equals(5));
    }

    Spec(upperScore)
    {

        for (int i = 1; i <= Die::DEFAULT_SIDES; i++)
        {
            auto value = 2 * i;

            score->upperScore(2, value);

            Assert::That(score->upperScore(2), Equals(value));
        }
    }

    Spec(lowerScore)
    {
        for (int i = ScoreSheet::FIRST_TYPE; i < ScoreSheet::MAX_TYPE; i++)
        {
            auto value = 2 * i;

            score->upperScore(2, value);

            Assert::That(score->upperScore(2), Equals(value));
        }
    }

    Spec(reset)
    {
        score->upperScore(2, 10);

        Assert::That(score->upperScore(2), Equals(10));

        score->reset();

        Assert::That(score->upperScore(2), !Equals(10));
    }
};
