#include <algorithm>
#include "buffer.h"

using namespace std;

namespace arg3
{
    buffer::buffer() {}

    buffer::buffer(const buffer &other)
    {
        buf_ << other.buf_.str();
    }

    buffer &buffer::operator=(const buffer &other)
    {
        buf_.clear();
        buf_ << other.buf_.str();
        return *this;
    }
	
    void buffer::clear() {
	buf_.clear();
    }

    buffer &buffer::writeln()
    {
        buf_ << endl;
        return *this;
    }

    buffer::operator string() const
    {
        return buf_.str();
    }

    std::string buffer::to_string() const
    {
        return buf_.str();
    }

    bool buffer::empty() const
    {
        return buf_.str().empty();
    }

    size_t buffer::length() const
    {
        return buf_.str().length();
    }

    buffer &buffer::remove(size_t start, size_t end)
    {
        string str = buf_.str();

        string temp = str.substr(0, start);

        if (end != string::npos)
        {
            string endStr = str.substr(end);
            temp = temp.append(endStr);
        }

        buf_.clear();

        buf_ << temp;

        return *this;
    }

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
