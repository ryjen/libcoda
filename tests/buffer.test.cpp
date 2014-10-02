#include <bandit/bandit.h>
#include "../src/string/buffer.h"

using namespace bandit;
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

go_bandit([]()
{

    describe("a buffer", []()
    {
        it("has a copy constructor", []()
        {
            buffer buf;

            buf.write("lorum ipsum");

            buffer other(buf);

            Assert::That(other.to_string(), Equals("lorum ipsum"));
        });

        it("can be copy assigned", []()
        {
            buffer buf;

            buf.write("lorum ipsum");

            buffer other;

            other = buf;

            Assert::That(other.to_string(), Equals("lorum ipsum"));
        });

        it("can write a line", []()
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
        });

        it("can be empty", []()
        {
            buffer buf;

            Assert::That(buf.empty(), Equals(true));

            buf.write("lorum ipsum");

            Assert::That(buf.empty(), Equals(false));
        });

        it("can write", []()
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
        });

        it("can read a line", []()
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
        });

        it("can test for input", []()
        {
            test_buffer buf;

            buf.writeln("lorum ipsum");

            buf.read_to_buffer();

            Assert::That(buf.has_input(), Equals(true));

            buf.readln();

            Assert::That(buf.has_input(), Equals(false));
        });

        it("can get input", []()
        {
            test_buffer buf;

            Assert::That(buf.input().size(), Equals(0));

            buf.writeln("lorum ipsum");

            buf.read_to_buffer();

            auto input = buf.input();

            Assert::That(input.size(), Equals(13));
        });

        it("can append", []()
        {
            buffer buf;

            buf.write("test").write("ing").write(" ").write("1 2 3");

            Assert::That(buf.to_string(), Equals("testing 1 2 3"));
        });

        it("can test for output", []()
        {
            test_buffer buf;

            Assert::That(buf.has_output(), Equals(false));

            buf.writeln("lorum ipsum");

            Assert::That(buf.has_output(), Equals(true));
        });

        it("can get output", []()
        {
            test_buffer buf;

            Assert::That(buf.output().size(), Equals(0));

            buf.writeln("lorum ipsum");

            Assert::That(buf.output().size(), Equals(13));
        });

        it("can left shift output", []()
        {
            buffer buf;

            buf << "testing";

            buf << " " << "1 2 3" << "\n";

            Assert::That(buf.to_string(), Equals("testing 1 2 3\n"));
        });

        it("can be cast to a string", []()
        {
            buffer buf;

            buf << "testing";

            std::string temp = buf;

            Assert::That(temp, Equals("testing"));
        });

        it("can be constructed from a string", []()
        {
            buffer buf("testing 1 2 3");

            Assert::That(buf.to_string(), Equals("testing 1 2 3"));
        });

        it("can remove output", []()
        {
            buffer buf("testing 1 2 3");

            buf.remove(buf.length() - 2);

            Assert::That(buf.to_string(), Equals("testing 1 2"));
	
	    buf.clear();

            buf << "testing 1 2 3";

            buf.remove(buf.length() - 4, buf.length() - 2);

            Assert::That(buf.to_string(), Equals("testing 1 3"));
        });
    });


});

