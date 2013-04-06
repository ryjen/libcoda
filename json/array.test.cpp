#include "array.h"
#include "object.h"
#include <igloo/igloo.h>

using namespace arg3;
using namespace igloo;

Context(ArrayTest)
{
    Spec(testIterator)
    {
        json::array value;

        value.addString("test");

        value.addInt(1234);

        value.addDouble(123.321);

        value.addBool(true);

        auto i = value.begin();

        Assert::That(i->isString(), Equals(true));

        Assert::That(i->toString(), Equals("test"));

        i++;

        Assert::That(i->isInt(), Equals(true));

        Assert::That(i->toInt(), Equals(1234));

        i++;

        Assert::That(i->isDouble(), Equals(true));

        Assert::That(i->toDouble(), Equals(123.321));

        i++;

        Assert::That(i->isBool(), Equals(true));

        Assert::That(i->toBool(), Equals(true));
    }
};
