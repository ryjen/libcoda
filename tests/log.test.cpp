#include <string>

#include <bandit/bandit.h>
#include "../src/log/log.h"

using namespace bandit;

using namespace rj;

using namespace snowhouse;

go_bandit([]() {

    describe("a log", []() {
        it("can lookup a log level", []() { Assert::That(log::lookup_log_level("debug"), Equals(LOG_DEBUG)); });
    });

});
