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

        value.add_str("test");

        value.add_int(1234);

        value.add_double(123.321);

        value.add_bool(true);

        auto i = value.begin();

        Assert::That(i->is_str(), Equals(true));

        Assert::That(i->to_str(), Equals("test"));

        i++;

        Assert::That(i->is_int(), Equals(true));

        Assert::That(i->to_int(), Equals(1234));

        i++;

        Assert::That(i->is_double(), Equals(true));

        Assert::That(i->to_double(), Equals(123.321));

        i++;

        Assert::That(i->is_bool(), Equals(true));

        Assert::That(i->to_bool(), Equals(true));
    }
};
