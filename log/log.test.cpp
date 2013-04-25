#include <igloo/igloo.h>
#include "log.h"

using namespace igloo;

using namespace arg3;


Context(arg3log)
{
    Spec(lookupLogLevel)
    {
        Assert::That(log::lookupLogLevel("debug"), Equals(log::DEBUG));
    }
};
