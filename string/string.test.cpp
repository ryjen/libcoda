#include <igloo/igloo.h>
#include "string.h"
#include <algorithm>

using namespace igloo;

using namespace arg3;


Context(arg3strings)
{

    Spec(isNumber)
    {
        Assert::That(is_number("45"), Equals(1));
        Assert::That(is_number("4.5"), Equals(2));
        Assert::That(is_number("-4.5"), Equals(2));
        Assert::That(is_number("-45"), Equals(1));

        Assert::That(is_number("asdf"), Equals(0));
    }

    Spec(isValidEmail)
    {
        Assert::That(is_valid_email("c0der78@gmail.com"), Equals(true));
        Assert::That(is_valid_email("ryan.jennings@arg3.net"), Equals(true));
        Assert::That(is_valid_email("ryan@blah"), Equals(false));
        Assert::That(is_valid_email("@blah.com"), Equals(false));
        Assert::That(is_valid_email("ryan@"), Equals(false));
        Assert::That(is_valid_email("ryan.jennings.net"), Equals(false));
    }

    Spec(ordinalString)
    {
        Assert::That(ordinal_string(1), Equals("first"));
        Assert::That(ordinal_string(2), Equals("second"));
        Assert::That(ordinal_string(3), Equals("third"));
        Assert::That(ordinal_string(4), Equals("4th"));
        Assert::That(ordinal_string(17), Equals("17th"));
        Assert::That(ordinal_string(21), Equals("21st"));
        Assert::That(ordinal_string(22), Equals("22nd"));
        Assert::That(ordinal_string(23), Equals("23rd"));
    }


    Spec(testCapitalize)
    {

        Assert::That(capitalize("fooBAR"), Equals("Foobar"));
    }


    Spec(testNullstr)
    {
        Assert::That(nullstr(""), Equals(true));
        Assert::That(nullstr(0), Equals(true));
        Assert::That(nullstr("test"), Equals(false));
    }

    Spec(testInsensitiveEquals)
    {
        Assert::That(equals("ABC", "abc"), Equals(true));

        Assert::That(equals("DEF", "ghi"), Equals(false));
    }

    Spec(testBase64)
    {
        string testStr = "hello, world";
        binary binStr(testStr.begin(), testStr.end());
        string encStr = "aGVsbG8sIHdvcmxk";

        Assert::That(base64::encode(binStr), Equals(encStr));

        binary decStr = base64::decode(encStr);

        Assert::That(std::equal(decStr.begin(), decStr.end(), binStr.begin()), Equals(true));
    }
};
