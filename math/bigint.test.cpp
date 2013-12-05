#include <igloo/igloo.h>
#include "bigint.h"

using namespace igloo;
using namespace arg3;

Context(bigint_test)
{
    Spec(literal_test)
    {

        bigint bi = 34098792871928374019287305239874052938465018273192387418273657623868726345_bi;

        Assert::That(bi.to_string(), Equals("34098792871928374019287305239874052938465018273192387418273657623868726345") );
    }
};
