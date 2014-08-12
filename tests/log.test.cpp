#include <bandit/bandit.h>
#include "../src/log/log.h"

using namespace bandit;

using namespace arg3;

go_bandit([]()
{

    describe("a log", []()
    {
        it("can lookup a log level", []()
        {
            Assert::That(log::lookup_log_level("debug"), Equals(log::DEBUG));
        });
    });

});
