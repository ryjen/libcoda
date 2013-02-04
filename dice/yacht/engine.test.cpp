#include <igloo/igloo.h>

#include "engine.h"

#include "../dice.test.h"

using namespace igloo;

using namespace arg3;

using namespace arg3::yacht;

Context(YachtTest)
{
    static Engine *yacht;

    static DiceTestEngine randEngine;

    static void SetUpContext()
    {
        yacht = Engine::instance();

        yacht->setRandomEngine(&randEngine);

        yacht->addPlayer("testPlayer");
    }

    void SetUp()
    {
        int size = yacht->numberOfPlayers();

        while (size >= 1)
        {
            yacht->removePlayer(size--);
        }
    }

    Spec(currentPlayer)
    {
        yacht->currentPlayer()->roll();

        yacht->addPlayer("newPlayerB");

        yacht->nextPlayer();

        Assert::That(yacht->currentPlayer()->name(), Equals("newPlayerB"));

        yacht->removePlayer(1);

        Assert::That(yacht->currentPlayer()->name(), !Equals("newPlayerB"));
    }

    Spec(numberOfPlayers)
    {
        Assert::That(yacht->numberOfPlayers(), Equals(1));
    }

};


Engine *YachtTest::yacht;
DiceTestEngine YachtTest::randEngine;

