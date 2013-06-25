#include "argument.h"
#include "string.h"

using namespace std;

namespace arg3
{

    argument::argument(const string &str) : str_(str)
    {}

    argument::argument(const char *str) : str_(str)
    {}

    argument::~argument()
    {}

    argument::argument(const argument &other) : str_(other.str_)
    {}

    argument::argument(argument &&other) : str_(std::move(other.str_))
    {
    }

    argument &argument::operator=(const argument &other)
    {
        if(this != &other)
        {
            str_ = other.str_;
        }
        return *this;
    }

    argument &argument::operator=(argument &&other)
    {
        if(this != &other)
        {
            str_ = std::move(other.str_);
        }
        return *this;
    }

    /**
     * gets the next argument
     */
    size_t argument::next(string &arg) const
    {
        char cEnd;

        size_t pos = str_.find_first_not_of(' ');

        cEnd = ' ';

        if ( str_[pos] == '\'' || str_[pos] == '"'
                || str_[pos] == '(' )
        {
            if ( str_[pos] == '(' )
            {
                cEnd = ')';
                pos++;
            }
            else
            {
                cEnd = str_[pos++];
            }
        }

        while ( pos < str_.length() )
        {
            if ( str_[pos] == cEnd )
            {
                pos++;
                break;
            }

            arg += str_[pos++];
        }

        pos = str_.find_first_not_of(' ', pos);

        return pos;
    }

    string argument::peek() const
    {
        string arg;

        next(arg);

        return arg;
    }

    string argument::next()
    {
        string arg;

        auto pos = next(arg);

        if (pos == string::npos)
        {
            str_.clear();
        }
        else
        {
            str_ = str_.substr(pos);
        }

        return arg;
    }
    int argument::nextInt()
    {
        return stoi(next());
    }
    double argument::nextDouble()
    {
        return stod(next());
    }
    int64_t argument::nextInt64()
    {
        return stoll(next());
    }
    bool argument::nextBool()
    {
        string arg = next();

        return arg == "true" || arg == "1";
    }

    argument::operator const string &()
    {
        return str_;
    }

    bool argument::empty() const
    {
        return str_.length() == 0;
    }

    size_t argument::length() const
    {
        return str_.length();
    }

    string argument::to_string() const
    {
        return str_;
    }

    char argument::operator [] (int index) const
    {
        return str_[index];
    }

    bool argument::operator ! () const
    {
        return empty();
    }

    bool argument::equals(const string &arg, bool caseSensitive) const {
        return arg3::equals(str_, arg, caseSensitive);
    }

    bool argument::prefix(const string &arg, bool caseSensitive) const {
        return arg3::prefix(str_, arg, caseSensitive);
    }
}
