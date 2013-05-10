#include <igloo/igloo.h>
#include "bigint.h"

using namespace igloo;
using namespace arg3;

Context(BigIntTest)
{
    Spec(toString)
    {

        const char *bignum = "34098792871928374019287305239874052938465018273192387418273657623868726345";

        bigint bi(bignum);

        Assert::That(bi.to_string(), Equals(bignum) );
    }
};
