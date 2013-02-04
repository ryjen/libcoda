#include <igloo/igloo.h>
#include "player.h"
#include "engine.h"
#include "../dice.test.h"

using namespace igloo;

using namespace arg3::yacht;

Context(YachtPlayerTest)
{
    static DiceTestEngine randEngine;

    static Player player;

    /*void SetUp()
    {
        //player = new Player("testA", &randEngine);
    }

    void TearDown()
    {
        delete player;
        player = 0;
    }*/

    Spec(calculateFourOfAKindPositive)
    {
        randEngine.setNextRoll( {4, 4, 4, 1, 4} );

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::KIND_FOUR);

        Assert::That(score, Equals(17));
    }

    Spec(calculateFourOfAKindNegative)
    {
        randEngine.setNextRoll( {4, 4, 1, 2, 3} );

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::KIND_FOUR);

        Assert::That(score, Equals(0));
    }


    Spec(calculateThreeOfAKindPositive)
    {
        randEngine.setNextRoll( {4, 4, 4, 1, 2} );

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::KIND_THREE);

        Assert::That(score, Equals(15));
    }

    Spec(calculateThreeOfAKindNegative)
    {
        randEngine.setNextRoll( {4, 3, 2, 1, 5} );

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::KIND_THREE);

        Assert::That(score, Equals(0));
    }

    Spec(calculateUpperScorePositive)
    {
        for (Die::value_type i = 1; i <= Constants::NUM_DICE; i++)
        {
            randEngine.setNextRoll( {{i}});

            player.roll();

            auto score = player.calculateUpperScore(i);

            Assert::That(score, Equals(i * Constants::NUM_DICE));
        }
    }

    Spec(calculateUpperScoreNegative)
    {
        for (Die::value_type i = 1; i <= Constants::NUM_DICE; i++)
        {
            randEngine.setNextRoll( {{i > 1 ? 1 : i + 1}});

            player.roll();

            auto score = player.calculateUpperScore(i);

            Assert::That(score, Equals(0));
        }
    }

    Spec(calculateFullHousePositive)
    {
        randEngine.setNextRoll( { 1, 1, 1, 4, 4 });

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::FULL_HOUSE);

        Assert::That(score, Equals(25));
    }

    Spec(calculateFullHouseNegative)
    {
        randEngine.setNextRoll( { 2, 2, 3, 5, 4 });

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::FULL_HOUSE);

        Assert::That(score, Equals(0));
    }



    Spec(calculateSmallStraightPositive)
    {
        randEngine.setNextRoll( { 1, 1, 2, 3, 4} );

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::STRAIGHT_SMALL);

        Assert::That(score, Equals(30));
    }

    Spec(calculateSmallStraightNegative)
    {
        randEngine.setNextRoll( { 2, 5, 3, 5, 6 });

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::STRAIGHT_SMALL);

        Assert::That(score, Equals(0));
    }


    Spec(calculateBigStraightPositive)
    {
        randEngine.setNextRoll( { 1, 2, 3, 4, 5 });

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::STRAIGHT_BIG);

        Assert::That(score, Equals(40));
    }

    Spec(calculateBigStraightNegative)
    {
        randEngine.setNextRoll( { 2, 2, 3, 5, 3 });

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::STRAIGHT_BIG);

        Assert::That(score, Equals(0));
    }


    Spec(calculateYachtPositive)
    {
        randEngine.setNextRoll( { 1, 1, 1, 1, 1} );

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::YACHT);

        Assert::That(score, Equals(50));
    }

    Spec(calculateYachtNegative)
    {
        randEngine.setNextRoll( { 2, 2, 3, 5, 4 });

        player.roll();

        auto score = player.calculateLowerScore(ScoreSheet::YACHT);

        Assert::That(score, Equals(0));
    }

    Spec(keepDie)
    {

        randEngine.setNextRoll( { 4, 3, 6, 1, 3});

        player.roll();

        player.keepDie(1);

        randEngine.setNextRoll( {1, 2, 4, 3});

        player.roll();

        auto values = player.values();

        Assert::That(values[0], !Equals(4));

        Assert::That(values[1], Equals(3));

        player.keepDie(4);

        randEngine.setNextRoll( {6, 6, 4});

        player.roll();

        values = player.values();

        Assert::That(values[0], !Equals(1));

        Assert::That(values[4], Equals(3));
    }

    Spec(calculateBestLowerScore)
    {
        randEngine.setNextRoll( { 5, 5, 4, 4, 4 } );

        player.roll();

        auto lower = player.calculateBestLowerScore();

        Assert::That(lower.first, Equals(ScoreSheet::Type::FULL_HOUSE));

        Assert::That(lower.second, Equals(25));

    }

    Spec(calculateBestUpperScore)
    {
        randEngine.setNextRoll( { 2, 2, 3, 3, 4 } );

        player.roll();

        auto upper = player.calculateBestUpperScore();

        Assert::That(upper.first, Equals(3));

        Assert::That(upper.second, Equals(6));
    }

    Spec(calculateBestScore)
    {
        randEngine.setNextRoll( {3, 6, 1, 6, 1});

        player.roll();

        auto score = player.calculateBestScore();

        Assert::That(score, Equals(17));

        player.score().lowerScore(ScoreSheet::CHANCE, score);

        score = player.calculateBestScore();

        Assert::That(score, Equals(12));
    }
};

DiceTestEngine YachtPlayerTest::randEngine;

Player YachtPlayerTest::player("testA", &YachtPlayerTest::randEngine);


