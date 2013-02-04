#ifndef ARG3_DICE_TEST_H
#define ARG3_DICE_TEST_H

#include "dice.h"

using namespace arg3;

class DiceTestEngine : public Die::Engine
{

public:

    DiceTestEngine();

    DiceTestEngine(initializer_list<Die::value_type> items);

    DiceTestEngine(const DiceTestEngine &copy);

    virtual ~DiceTestEngine();

    DiceTestEngine &operator=(const DiceTestEngine &rhs);

    Die::value_type generate(Die::value_type from, Die::value_type to);

    void setNextRoll(initializer_list<Die::value_type> items);
private:
    vector<Die::value_type> mValues;
    size_t mCurrentValue;

};

#endif
