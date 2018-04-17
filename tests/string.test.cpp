#include <string>

#include <bandit/bandit.h>
#include <algorithm>
#include "string/util.h"

using namespace bandit;

using namespace coda;

using namespace snowhouse;

go_bandit([]() {

    describe("string utils", []() {

        it("can test for numbers", []() {
            Assert::That(is_number("45"), Equals(1));
            Assert::That(is_number("4.5"), Equals(2));
            Assert::That(is_number("-4.5"), Equals(2));
            Assert::That(is_number("-45"), Equals(1));

            Assert::That(is_number("asdf"), Equals(0));

            Assert::That(is_number(""), Equals(0));
        });

        it("can test for emails", []() {
            Assert::That(is_valid_email("info@ryan-jennings.net"), Equals(true));
            Assert::That(is_valid_email("ryan.jennings@email.net"), Equals(true));
            Assert::That(is_valid_email("ryan@blah"), Equals(false));
            Assert::That(is_valid_email("@blah.com"), Equals(false));
            Assert::That(is_valid_email("ryan@"), Equals(false));
            Assert::That(is_valid_email("ryan.jennings.net"), Equals(false));
            Assert::That(is_valid_email("\"ryan.jennings\"@email.com"), Equals(true));
            Assert::That(is_valid_email("\"ryan\".jennings@email.com"), Equals(true));
        });

        it("can make a number ordinal", []() {
            Assert::That(ordinal_string(1), Equals("first"));
            Assert::That(ordinal_string(2), Equals("second"));
            Assert::That(ordinal_string(3), Equals("third"));
            Assert::That(ordinal_string(4), Equals("4th"));
            Assert::That(ordinal_string(17), Equals("17th"));
            Assert::That(ordinal_string(21), Equals("21st"));
            Assert::That(ordinal_string(22), Equals("22nd"));
            Assert::That(ordinal_string(23), Equals("23rd"));
        });


        it("can capitalize", []() {

            Assert::That(capitalize("fooBAR"), Equals("Foobar"));

            Assert::That(capitalize(""), Equals(""));
        });


        it("can test for an empty string", []() {
            Assert::That(nullstr(""), Equals(true));
            Assert::That(nullstr(0), Equals(true));
            Assert::That(nullstr("test"), Equals(false));
        });

        it("can test for case insensitive equality", []() {
            Assert::That(equals("ABC", "abc"), Equals(true));

            Assert::That(equals("DEF", "ghi"), Equals(false));
        });

        it("can encode and decode base64", []() {
            string testStr = "hello, world";
            binary binStr(testStr.begin(), testStr.end());
            string encStr = "aGVsbG8sIHdvcmxk";

            Assert::That(base64::encode(binStr), Equals(encStr));

            binary decStr = base64::decode(encStr);

            Assert::That(std::equal(decStr.begin(), decStr.end(), binStr.begin()), Equals(true));
        });

        it("can join", []() {
            string test = coda::join("abc", 3, ",");

            Assert::That(test, Equals("abc,abc,abc"));

            test = coda::join('Z', 3, "-");

            Assert::That(test, Equals("Z-Z-Z"));
        });

        it("can split", []() {
            auto parts = coda::split("abc,123,xyz", ",", true);

            Assert::That(parts.size(), Equals(3));

            Assert::That(parts[0], Equals("abc"));
            Assert::That(parts[1], Equals("123"));
            Assert::That(parts[2], Equals("xyz"));

            parts = coda::split("abc//123//xyz", "/", true);

            Assert::That(parts.size(), Equals(5));

            Assert::That(parts[0], Equals("abc"));
            Assert::That(parts[1], Equals(""));
            Assert::That(parts[2], Equals("123"));
            Assert::That(parts[3], Equals(""));
            Assert::That(parts[4], Equals("xyz"));

            parts = coda::split("abc,123,xyz", "", true);

            Assert::That(parts.size(), Equals(1));

            Assert::That(parts[0], Equals("abc,123,xyz"));
        });

        it("can test for a prefix", []() {
            std::string test = "abc123";

            Assert::That(coda::prefix("abc", test), Equals(true));

            Assert::That(coda::prefix("123", test), Equals(false));

            Assert::That(coda::prefix("", test), Equals(false));
        });

        it("can test for a suffix", []() {
            std::string test = "abc123";

            Assert::That(coda::suffix("abc", test), Equals(false));
            Assert::That(coda::suffix("123", test), Equals(true));
            Assert::That(coda::suffix("", test), Equals(false));
        });

        it("can test for string contents", []() {
            std::string test = "abc123";

            Assert::That(coda::contains("bc12", test), Equals(true));

            Assert::That(coda::contains("asd", test), Equals(false));

            Assert::That(coda::contains("", test), Equals(false));
        });
    });


});
