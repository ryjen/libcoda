#include <string>

#include <bandit/bandit.h>
#include "../src/log/log.h"

using namespace bandit;

using namespace coda;

using namespace snowhouse;

go_bandit([]() {

    describe("a log", []() {
        it("can lookup a log level", []() { 
                log::level::set("debug");
                Assert::That(log::level::valid(log::level::Debug), IsTrue()); 
        });
    });

});
