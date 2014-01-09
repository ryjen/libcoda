#include <igloo/igloo.h>
#include "log.h"

using namespace igloo;

using namespace arg3;


Context(arg3log)
{
    Spec(lookup_log_level)
    {
        Assert::That(log::lookup_log_level("debug"), Equals(log::DEBUG));
    }
};
