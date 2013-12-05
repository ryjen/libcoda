
#include <igloo/igloo.h>
#include "argument.h"

using namespace igloo;
using namespace arg3;

Context(argument_test)
{
    Spec(next)
    {
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
    }

    Spec(next_int)
    {
        argument arg("1234");

        Assert::That(arg.next_int(), Equals(1234));

        argument arg2("abcdef");

        AssertThrows(std::invalid_argument, arg.next_int());
    }

    Spec(peek)
    {
        argument argument("testing (1 2 3)");

        Assert::That(argument.peek(), Equals("testing"));

        Assert::That(argument.to_string(), Equals("testing (1 2 3)"));
    }

    Spec(empty)
    {
        argument argument("blah");

        argument.next();

        Assert::That(argument.empty(), Equals(true));
    }


    Spec(length)
    {
        argument arg("test 123");

        Assert::That(arg.length(), Equals(8));

        arg.next();

        Assert::That(arg.length(), Equals(3));
    }

    Spec(op_not)
    {
        argument arg("test");

        Assert::That(!arg, Equals(false));

        arg.next();

        Assert::That(!arg, Equals(true));
    }

    Spec(op_index)
    {
        argument arg("test");

        Assert::That(arg[1], Equals('e'));
    }

};
