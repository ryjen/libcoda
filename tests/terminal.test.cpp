#include <string>

#include <bandit/bandit.h>
#include "../src/terminal/vt100.h"

using namespace bandit;

using namespace coda;

using namespace snowhouse;

go_bandit([]() {

    describe("a vt100 terminal", []() {
        it("can parse csi codes", []() {
            coda::terminal::vt100 term;

            std::string s = "\033[1;33mHello\033[0m, \033[1;32mWorld\033[0m!";

            vector<coda::terminal::data_type> bytes(s.begin(), s.end());

            auto t = term.parse(bytes);

            AssertThat(term.codes().size(), Equals(4));

            AssertThat(string(t.begin(), t.end()), Equals("Hello, World!"));
        });
    });

});
