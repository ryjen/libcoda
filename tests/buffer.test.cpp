#include <igloo/igloo.h>
#include "../src/string/buffer.h"

using namespace igloo;
using namespace arg3;


class test_buffer : public buffered_reader, public buffered_writer
{
public:
    bool read_to_buffer()
    {
        input().insert(input().begin(), output().begin(), output().end());
        output().clear();
        return true;
    }
    bool write_from_buffer()
    {
        output().insert(output().begin(), input().begin(), input().end());
        input().clear();
        return true;
    }
};

Context(buffer_test)
{
    Spec(copy_constructor)
    {
        buffer buf;

        buf.write("lorum ipsum");

        buffer other(buf);

        Assert::That(other.to_string(), Equals("lorum ipsum"));
    }

    Spec(move_constructor)
    {
        buffer buf;

        buf.writeln("test");

        buffer other = std::move(buf);

        Assert::That(other.to_string(), Equals("test\n"));

        Assert::That(buf.empty(), Equals(true));

    }

    Spec(copy_assignment)
    {
        buffer buf;

        buf.write("lorum ipsum");

        buffer other;

        other = buf;

        Assert::That(other.to_string(), Equals("lorum ipsum"));
    }

    Spec(writeln)
    {
        test_buffer buf;

        buf.writeln("lorum ipsum");

        Assert::That(buf.output().size(), Equals(13));

        buf.output().clear();

        buffered_data data = {'h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd' };

        buf.writeln(data);

        Assert::That(buf.output().size(), Equals(data.size() + 2));

        buf.writeln();

        Assert::That(buf.output().size(), Equals(data.size() + 4));

        buffer buf2;

        buf2.writeln("test");

        Assert::That(buf2.to_string(), Equals("test\n"));

        buf2.writeln();

        Assert::That(buf2.to_string(), Equals("test\n\n"));
    }

    Spec(empty)
    {
        buffer buf;

        Assert::That(buf.empty(), Equals(true));

        buf.write("lorum ipsum");

        Assert::That(buf.empty(), Equals(false));
    }

    Spec(write)
    {
        buffer buf;

        buf.write("test");

        Assert::That(buf.to_string(), Equals("test"));

        test_buffer testBuf;

        testBuf.write("lorum ipsum");

        Assert::That(testBuf.output().size(), Equals(11));

        buffered_data data = { 't', 'e', 's', 't', 'i', 'n', 'g' };

        testBuf.write(data);

        Assert::That(testBuf.output().size(), Equals(18));
    }

    Spec(readln)
    {
        test_buffer buf;

        buf.writeln("lorum ipsum");

        buf.writeln("testing 1234");

        buf.read_to_buffer();

        std::string test = buf.readln();

        Assert::That(test, Equals("lorum ipsum"));

        test = buf.readln();

        Assert::That(test, Equals("testing 1234"));

        test = buf.readln();

        Assert::That(test.empty(), Equals(true));

        buf.write("test");

        buf.read_to_buffer();

        Assert::That(buf.readln(), Equals("test"));
    }

    Spec(has_input)
    {
        test_buffer buf;

        buf.writeln("lorum ipsum");

        buf.read_to_buffer();

        Assert::That(buf.has_input(), Equals(true));

        buf.readln();

        Assert::That(buf.has_input(), Equals(false));
    }

    Spec(input)
    {
        test_buffer buf;

        Assert::That(buf.input().size(), Equals(0));

        buf.writeln("lorum ipsum");

        buf.read_to_buffer();

        auto input = buf.input();

        Assert::That(input.size(), Equals(13));
    }

    Spec(append)
    {
        buffer buf;

        buf.write("test").write("ing").write(" ").write("1 2 3");

        Assert::That(buf.to_string(), Equals("testing 1 2 3"));
    }

    Spec(has_output)
    {
        test_buffer buf;

        Assert::That(buf.has_output(), Equals(false));

        buf.writeln("lorum ipsum");

        Assert::That(buf.has_output(), Equals(true));
    }

    Spec(output)
    {
        test_buffer buf;

        Assert::That(buf.output().size(), Equals(0));

        buf.writeln("lorum ipsum");

        Assert::That(buf.output().size(), Equals(13));
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
