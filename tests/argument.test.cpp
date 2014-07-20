
#include <igloo/igloo.h>
#include "../src/string/argument.h"
#include "../src/math/util.h"

using namespace igloo;
using namespace arg3;
using namespace std;

Context(argument_test)
{
    Spec(string_constructor)
    {
        string test = "lorum ipsum";

        argument arg(test);

        Assert::That(arg, Equals("lorum ipsum"));
    }

    Spec(move_constructor)
    {
        argument arg("lorum ipsum");

        argument other = std::move(arg);

        AssertThat(other, Equals("lorum ipsum"));

        AssertThat(!arg, Equals(true));
    }

    Spec(assignment)
    {
        argument arg = "lorum ipsum";

        argument other;

        other = arg;

        Assert::That(other, Equals("lorum ipsum"));
    }

    Spec(assignment_move)
    {
        argument arg("lorum ipsum");

        argument other = std::move(arg);

        Assert::That(other, Equals("lorum ipsum"));

        Assert::That(!arg, Equals(true));
    }
    Spec(can_copy)
    {
        argument arg("lorum ipsum");

        argument other(arg);

        Assert::That(other, Equals("lorum ipsum"));
    }

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

    Spec(next_double)
    {
        argument arg("1.1234");

        double value = arg.next_double();

        Assert::That(almost_equal(value, 1.1234, 1), Equals(true));
    }

    Spec(next_int64)
    {
        argument arg("1234123412341234");

        int64_t value = arg.next_int64();

        int64_t check = 1234123412341234LL;

        Assert::That(value, Equals(check));
    }

    Spec(next_bool)
    {
        argument arg("true");

        Assert::That(arg.next_bool(), Equals(true));

        arg = "0";

        Assert::That(arg.next_bool(), Equals(false));
    }

    Spec(string_cast)
    {
        argument arg("lorum ipsum");

        string test = arg;

        Assert::That(test, Equals("lorum ipsum"));
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

    Spec(equality_operator)
    {
        argument arg("test");

        Assert::That("test" == arg, Equals(true));

        Assert::That(arg == "test" , Equals(true));

        Assert::That("test" != arg, Equals(false));

        Assert::That(arg != "test", Equals(false));

        string test = "test";

        Assert::That(arg == test, Equals(true));

        Assert::That(arg != test, Equals(false));

        Assert::That(test != arg, Equals(false));

        argument other("test");

        Assert::That(arg == other, Equals(true));

        Assert::That(arg != other, Equals(false));
    }

    Spec(equality)
    {
        argument arg("lorum ipsum");

        Assert::That(arg.equals("lorum ipsum"), Equals(true));

        Assert::That(arg.equals("lorum IPSUM", true), Equals(false));

        Assert::That(arg.equals("lorum IPSUM", false), Equals(true));
    }

    Spec(prefix)
    {
        argument arg("lorum ipsum");

        Assert::That(arg.prefix("lorum"), Equals(true));

        Assert::That(arg.prefix("ipsum"), Equals(false));
    }
};
