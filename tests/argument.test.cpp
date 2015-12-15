
#include <bandit/bandit.h>
#include "../src/string/argument.h"
#include "../src/math/util.h"

using namespace bandit;
using namespace arg3;
using namespace std;

go_bandit([]() {

    describe("an argument", []() {
        it("can be constructed from a string", []() {
            string test = "lorum ipsum";

            argument arg(test);

            Assert::That(arg, Equals("lorum ipsum"));
        });

        it("can be moved into another", []() {
            argument arg("lorum ipsum");

            argument other = std::move(arg);

            AssertThat(other, Equals("lorum ipsum"));

            AssertThat(!arg, Equals(true));
        });

        it("can be assigned", []() {
            argument arg = "lorum ipsum"_a;

            argument other;

            other = arg;

            Assert::That(other, Equals("lorum ipsum"));
        });

        it("can be move assigned", []() {
            argument arg("lorum ipsum");

            argument other = std::move(arg);

            Assert::That(other, Equals("lorum ipsum"));

            Assert::That(!arg, Equals(true));
        });

        it("can be copied", []() {
            argument arg("lorum ipsum");

            argument other(arg);

            Assert::That(other, Equals("lorum ipsum"));
        });

        it("can be broken into parts", []() {
            argument argument("\"this\" 'is a' test (1 2 3)");

            string arg = argument.next();

            Assert::That(arg, Equals("this"));

            arg = argument.next();

            Assert::That(arg, Equals("is a"));

            arg = argument.next();

            Assert::That(arg, Equals("test"));

            arg = argument.next();

            Assert::That(arg, Equals("1 2 3"));

            Assert::That(argument.empty(), Equals(true));
        });

        it("can find integers", []() {
            argument arg("1234");

            Assert::That(arg.next_int(), Equals(1234));

            argument arg2("abcdef");

            AssertThrows(std::invalid_argument, arg.next_int());
        });

        it("can find doubles", []() {
            argument arg("1.1234");

            double value = arg.next_double();

            Assert::That(almost_equal(value, 1.1234, 1), Equals(true));
        });

        it("can find int64 types", []() {
            argument arg("1234123412341234");

            int64_t value = arg.next_int64();

            int64_t check = 1234123412341234LL;

            Assert::That(value, Equals(check));
        });

        it("can find a boolean", []() {
            argument arg("true");

            Assert::That(arg.next_bool(), Equals(true));

            arg = "0"_a;

            Assert::That(arg.next_bool(), Equals(false));
        });

        it("can cast to a string", []() {
            argument arg("lorum ipsum");

            string test = arg;

            Assert::That(test, Equals("lorum ipsum"));
        });

        it("can peek at the next part", []() {
            argument argument("testing (1 2 3)");

            Assert::That(argument.peek(), Equals("testing"));

            Assert::That(argument.to_string(), Equals("testing (1 2 3)"));
        });

        it("can be empty", []() {
            argument argument("blah");

            argument.next();

            Assert::That(argument.empty(), Equals(true));
        });


        it("has a length", []() {
            argument arg("test 123");

            Assert::That(arg.length(), Equals(8));

            arg.next();

            Assert::That(arg.length(), Equals(3));
        });

        it("has a not operator", []() {
            argument arg("test");

            Assert::That(!arg, Equals(false));

            arg.next();

            Assert::That(!arg, Equals(true));
        });

        it("can be indexed", []() {
            argument arg("test");

            Assert::That(arg[1], Equals('e'));
        });

        it("has equlity", []() {
            argument arg("test");

            Assert::That("test" == arg, Equals(true));

            Assert::That(arg == "test", Equals(true));

            Assert::That("test" != arg, Equals(false));

            Assert::That(arg != "test", Equals(false));

            string test = "test";

            Assert::That(arg == test, Equals(true));

            Assert::That(arg != test, Equals(false));

            Assert::That(test != arg, Equals(false));

            argument other("test");

            Assert::That(arg == other, Equals(true));

            Assert::That(arg != other, Equals(false));
        });

        it("has case equality", []() {
            argument arg("lorum ipsum");

            Assert::That(arg.equals("lorum ipsum"), Equals(true));

            Assert::That(arg.equals("lorum IPSUM", true), Equals(false));

            Assert::That(arg.equals("lorum IPSUM", false), Equals(true));
        });

        it("can test for prefixes", []() {
            argument arg("lorum ipsum");

            Assert::That(arg.prefix("lorum"), Equals(true));

            Assert::That(arg.prefix("ipsum"), Equals(false));
        });

        it("can have literal", []() {
            auto arg = "lorum ipsum"_a;

            AssertThat(arg.next(), Equals("lorum"));

        });

    });


});
