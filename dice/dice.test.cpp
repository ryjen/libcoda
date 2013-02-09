
#include <igloo/igloo.h>
#include "dice.h"
#include "dice.test.h"

using namespace igloo;

using namespace arg3;

DiceTestEngine::DiceTestEngine() : mValues(), mCurrentValue(0) {}

DiceTestEngine::DiceTestEngine(initializer_list<Die::value_type> value) : mValues(value), mCurrentValue(0) {}

DiceTestEngine::DiceTestEngine(const DiceTestEngine &copy) : mValues(copy.mValues.size()), mCurrentValue(copy.mCurrentValue)
{
for (auto & d : copy.mValues)
        mValues.push_back(d);
}

DiceTestEngine &DiceTestEngine::operator=(const DiceTestEngine &rhs)
{
    if (this != &rhs)
    {
        mValues = rhs.mValues;
        mCurrentValue = rhs.mCurrentValue;
    }

    return *this;
}

DiceTestEngine::~DiceTestEngine() {}

Die::value_type DiceTestEngine::generate(Die::value_type from, Die::value_type to)
{
    if (mValues.size() == 0)
        return 0;

    if ( mCurrentValue >= mValues.size() )
    {
        mCurrentValue = 0;
    }

    return mValues[mCurrentValue++];
}

void DiceTestEngine::setNextRoll(initializer_list<Die::value_type> items)
{
    mValues = items;
    mCurrentValue = 0;
}

Context(DieTest)
{
    static DiceTestEngine randEngine;

    Spec(Constructor_No_Arg)
    {
        Die d;

        Assert::That(d.sides(), Equals(Die::DEFAULT_SIDES));
    }

    Spec(Constructor_Sides)
    {
        Die d(100);

        Assert::That(d.sides(), Equals(100));
    }

    Spec(Constructor_Copy)
    {
        Die d(10);

        Die d2 = d;

        Assert::That(d2.sides(), Equals(10));
    }

    Spec(Roll)
    {
        Die d(10);

        for (int i = 0; i < 10; i++)
        {
            Assert::That(d.sides(), IsGreaterThan(0));
            Assert::That(d.sides(), IsLessThan(11));
        }
    }

    Spec(sides)
    {
        Die d(7);

        Assert::That(d.sides(), Equals(7));

        d.sides(25);

        Assert::That(d.sides(), Equals(25));
    }
};

DiceTestEngine DieTest::randEngine;


Context(DiceTest)
{
    Spec(Constructor_With_Count)
    {
        Dice d(10);

        Assert::That(d.size(), Equals(10));
    }

    Spec(Constructor_With_Count_And_Sides)
    {
        Dice dice(10, 10);

        Assert::That(dice.size(), Equals(10));

for (Die & d : dice)
        {
            Assert::That(d.sides(), Equals(10));
        }
    }

    Spec(size)
    {
        Dice d(10);

        Assert::That(d.size(), Equals(10));
    }

    Spec(bonus)
    {
        Dice d(2);

        d.bonus(23);

        Assert::That(d.bonus(), Equals(23));
    }

    Spec(to_string)
    {
        Dice d(10, 20);

        Assert::That(d.to_string(), Equals("10d20"));

        d.bonus(5);

        Assert::That(d.to_string(), Equals("10d20+5"));
    }
};
