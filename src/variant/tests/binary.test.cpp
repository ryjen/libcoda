#include <string>

#include <bandit/bandit.h>
#include <functional>
#include "binary.h"

using namespace bandit;

using namespace std;

using namespace rj;

using namespace snowhouse;

go_bandit([]() {

    describe("a binary value", []() {

        int* imem = nullptr;

        before_each([&imem]() {
            imem = (int*)malloc(sizeof(int));
            *imem = 18;
        });

        after_each([&imem]() {
            free(imem);
            imem = nullptr;
        });

        it("can be constructed", [&imem]() {
            binary bin;

            Assert::That(bin.is_null(), IsTrue());

            Assert::That(bin == nullptr, IsTrue());

            Assert::That(bin.is_transient(), IsFalse());

            binary other(imem, sizeof(int));

            Assert::That(other.is_null(), IsFalse());
            Assert::That(other.is_transient(), IsTrue());
        });

        it("can be copied", [&imem]() {
            binary bin(imem, sizeof(int));

            binary other(bin);

            Assert::That(other == bin, IsTrue());

            Assert::That(other.size() == bin.size(), IsTrue());

            other = bin;

            Assert::That(other == bin, IsTrue());

            Assert::That(other.size() == bin.size(), IsTrue());

        });

        it("can be moved", [&imem]() {
            binary bin(imem, sizeof(int));

            binary other(std::move(bin));

            Assert::That(other == imem, IsTrue());

            Assert::That(other.size() == sizeof(int), IsTrue());
        });
        it("can be move assigned", [&imem]() {
            binary bin(imem, sizeof(int));

            binary other;

            other = std::move(bin);

            Assert::That(other == imem, IsTrue());

            Assert::That(other.size() == sizeof(int), IsTrue());

        });

        it("can be a string", [&imem]() {
            binary bin;

            Assert::That(bin.to_string(), Equals("0x0"));

            binary other(imem, sizeof(int));

            char test[100] = {0};
            snprintf(test, 100, "%p", other.value());

            Assert::That(other.to_string(), Equals(string(test)));
        });
    });
});
