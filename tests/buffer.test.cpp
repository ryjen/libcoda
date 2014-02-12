#include <igloo/igloo.h>
#include "../src/string/buffer.h"

using namespace igloo;
using namespace arg3;


Context(buffer_test)
{
    Spec(write)
    {
        buffer buf;

        buf.write("test");

        Assert::That(buf.to_string(), Equals("test"));
    }

    Spec(writeln)
    {
        buffer buf;

        buf.writeln("test");

        Assert::That(buf.to_string(), Equals("test\n"));
    }

    Spec(append)
    {
        buffer buf;

        buf.write("test").write("ing").write(" ").write("1 2 3");

        Assert::That(buf.to_string(), Equals("testing 1 2 3"));
    }

    Spec(append_operator)
    {
        buffer buf;

        buf << "testing";

        buf << " " << "1 2 3" << "\n";

        Assert::That(buf.to_string(), Equals("testing 1 2 3\n"));
    }

    Spec(string_operator)
    {
        buffer buf;

        buf << "testing";

        std::string temp = buf;

        Assert::That(temp, Equals("testing"));
    }

    Spec(string_constructor)
    {
        buffer buf = "testing 1 2 3";

        Assert::That(buf.to_string(), Equals("testing 1 2 3"));
    }

    Spec(remove)
    {
        buffer buf = "testing 1 2 3";

        buf.remove(buf.length() - 2);

        Assert::That(buf.to_string(), Equals("testing 1 2"));

        buf = "testing 1 2 3";

        buf.remove(buf.length() - 4, buf.length() - 2);

        Assert::That(buf.to_string(), Equals("testing 1 3"));
    }
};
