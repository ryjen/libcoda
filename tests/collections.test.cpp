#include <string>

#include <bandit/bandit.h>
#include "../src/collections/collections.h"

using namespace coda;

using namespace bandit;

using namespace snowhouse;

go_bandit([]() {

    describe("collection utilities", []() {
        it("can join", []() {
            vector<int> ints = {4, 6, 23, 65, 343, 65, 123};

            string test = join(ints);

            Assert::That(test, Equals("4,6,23,65,343,65,123"));
        });
    });


});
