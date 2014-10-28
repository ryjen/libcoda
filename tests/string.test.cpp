#include <bandit/bandit.h>
#include "../src/string/str_util.h"
#include <algorithm>

using namespace bandit;

using namespace arg3;

go_bandit([]()
{

    describe("string utils", []()
    {

        it("can test for numbers", []()
        {
            Assert::That(is_number("45"), Equals(1));
            Assert::That(is_number("4.5"), Equals(2));
            Assert::That(is_number("-4.5"), Equals(2));
            Assert::That(is_number("-45"), Equals(1));

            Assert::That(is_number("asdf"), Equals(0));

            Assert::That(is_number(""), Equals(0));
        });

        it("can test for emails", []()
        {
            Assert::That(is_valid_email("c0der78@gmail.com"), Equals(true));
            Assert::That(is_valid_email("ryan.jennings@arg3.net"), Equals(true));
            Assert::That(is_valid_email("ryan@blah"), Equals(false));
            Assert::That(is_valid_email("@blah.com"), Equals(false));
            Assert::That(is_valid_email("ryan@"), Equals(false));
            Assert::That(is_valid_email("ryan.jennings.net"), Equals(false));
            Assert::That(is_valid_email("\"ryan.jennings\"@email.com"), Equals(true));
            Assert::That(is_valid_email("\"ryan\".jennings@email.com"), Equals(true));
        });

        it("can make a number ordinal", []()
        {
            Assert::That(ordinal_string(1), Equals("first"));
            Assert::That(ordinal_string(2), Equals("second"));
            Assert::That(ordinal_string(3), Equals("third"));
            Assert::That(ordinal_string(4), Equals("4th"));
            Assert::That(ordinal_string(17), Equals("17th"));
            Assert::That(ordinal_string(21), Equals("21st"));
            Assert::That(ordinal_string(22), Equals("22nd"));
            Assert::That(ordinal_string(23), Equals("23rd"));
        });


        it("can capitalize", []()
        {

            Assert::That(capitalize("fooBAR"), Equals("Foobar"));

            Assert::That(capitalize(""), Equals(""));
        });


        it("can test for an empty string", []()
        {
            Assert::That(nullstr(""), Equals(true));
            Assert::That(nullstr(0), Equals(true));
            Assert::That(nullstr("test"), Equals(false));
        });

        it("can test for case insensitive equality", []()
        {
            Assert::That(equals("ABC", "abc"), Equals(true));

            Assert::That(equals("DEF", "ghi"), Equals(false));
        });

        it("can encode and decode base64", []()
        {
            string testStr = "hello, world";
            binary binStr(testStr.begin(), testStr.end());
            string encStr = "aGVsbG8sIHdvcmxk";

            Assert::That(base64::encode(binStr), Equals(encStr));

            binary decStr = base64::decode(encStr);

            Assert::That(std::equal(decStr.begin(), decStr.end(), binStr.begin()), Equals(true));
        });

        it("can sprintf", []()
        {
            string buf;

            int ret = sprintf(buf, "%s %d $%.2f", "Harry", 1234, 12.344546);

            Assert::That(ret > 0, Equals(true));

            Assert::That(buf, Equals("Harry 1234 $12.34"));
        });

        it("can join", []()
        {
            string test = arg3::join("abc", 3, ",");

            Assert::That(test, Equals("abc,abc,abc"));

            test = arg3::join('Z', 3, "-");

            Assert::That(test, Equals("Z-Z-Z"));
        });

        it("can split", []()
        {
            auto parts = arg3::split("abc,123,xyz", ",", true);

            Assert::That(parts.size(), Equals(3));

            Assert::That(parts[0], Equals("abc"));
            Assert::That(parts[1], Equals("123"));
            Assert::That(parts[2], Equals("xyz"));

            parts = arg3::split("abc//123//xyz", "/", true);

            Assert::That(parts.size(), Equals(5));

            Assert::That(parts[0], Equals("abc"));
            Assert::That(parts[1], Equals(""));
            Assert::That(parts[2], Equals("123"));
            Assert::That(parts[3], Equals(""));
            Assert::That(parts[4], Equals("xyz"));

            parts = arg3::split("abc,123,xyz", "", true);

            Assert::That(parts.size(), Equals(1));

            Assert::That(parts[0], Equals("abc,123,xyz"));
        });

        it("can test for a prefix", []()
        {
            std::string test = "abc123";

            Assert::That(arg3::prefix("abc", test), Equals(true));

            Assert::That(arg3::prefix("123", test), Equals(false));

            Assert::That(arg3::prefix("", test), Equals(false));
        });

        it("can test for a suffix", []()
        {
            std::string test = "abc123";

            Assert::That(arg3::suffix("abc", test), Equals(false));
            Assert::That(arg3::suffix("123", test), Equals(true));
            Assert::That(arg3::suffix("", test), Equals(false));
        });

        it("can test for string contents", []()
        {
            std::string test = "abc123";

            Assert::That(arg3::contains("bc12", test), Equals(true));

            Assert::That(arg3::contains("asd", test), Equals(false));

            Assert::That(arg3::contains("", test), Equals(false));
        });
    });


});

