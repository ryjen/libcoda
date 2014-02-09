#include "buffered_io.h"

using namespace std;

namespace arg3
{
    string buffered_reader::readln()
    {
        if (buffer_.empty()) return string();

        /* find a new line character */
        auto pos = find_first_of(buffer_.begin(), buffer_.end(), NEWLINE.begin(), NEWLINE.end());

        if (pos == buffer_.end())
        {
            string temp(buffer_.begin(), buffer_.end());

            buffer_.clear();

            return temp;
        }

        string temp(buffer_.begin(), pos);

        /* Skip all new line characters */
        while (pos != buffer_.end() && find(NEWLINE.begin(), NEWLINE.end(), *pos) != NEWLINE.end())
        {
            pos++;
        }

        buffer_.erase(buffer_.begin(), pos);

        return temp;
    }

    bool buffered_reader::has_input() const
    {
        return !buffer_.empty();
    }

    const buffered_data &buffered_reader::input() const
    {
        return buffer_;
    }

    buffered_data &buffered_reader::input()
    {
        return buffer_;
    }

    bool buffered_writer::has_output() const
    {
        return !buffer_.empty();
    }

    const buffered_data &buffered_writer::output() const
    {
        return buffer_;
    }

    buffered_data &buffered_writer::output()
    {
        return buffer_;
    }

    buffered_writer &buffered_writer::writeln(const string &value)
    {
        buffer_.insert(buffer_.end(), value.begin(), value.end());
        buffer_.insert(buffer_.end(), NEWLINE.begin(), NEWLINE.end());
        return *this;
    }

    buffered_writer &buffered_writer::writeln(const buffered_data &value)
    {
        buffer_.insert(buffer_.end(), value.begin(), value.end());
        buffer_.insert(buffer_.end(), NEWLINE.begin(), NEWLINE.end());
        return *this;
    }

    buffered_writer &buffered_writer::writeln()
    {
        buffer_.insert(buffer_.end(), NEWLINE.begin(), NEWLINE.end());
        return *this;
    }

    buffered_writer &buffered_writer::write(const string &value)
    {
        buffer_.insert(buffer_.end(), value.begin(), value.end());
        return *this;
    }


    buffered_writer &buffered_writer::write(const buffered_data &value)
    {
        buffer_.insert(buffer_.end(), value.begin(), value.end());
        return *this;
    }
}