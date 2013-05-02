#include "argument.h"

using namespace std;

namespace arg3
{

    argument::argument(const string &str) : mStr(str)
    {}

    argument::~argument()
    {}

    /**
     * gets the next argument
     */
    size_t argument::next(string &arg) const
    {
        char cEnd;

        size_t pos = mStr.find_first_not_of(' ');

        cEnd = ' ';

        if ( mStr[pos] == '\'' || mStr[pos] == '"'
                || mStr[pos] == '(' )
        {
            if ( mStr[pos] == '(' )
            {
                cEnd = ')';
                pos++;
            }
            else
            {
                cEnd = mStr[pos++];
            }
        }

        while ( pos < mStr.length() )
        {
            if ( mStr[pos] == cEnd )
            {
                pos++;
                break;
            }

            arg += mStr[pos++];
        }

        pos = mStr.find_first_not_of(' ', pos);

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
            mStr = string();
        }
        else
        {
            mStr = mStr.substr(pos);
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
        return mStr;
    }

    bool argument::empty() const
    {
        return mStr.length() == 0;
    }

    size_t argument::length() const
    {
        return mStr.length();
    }

    string argument::to_string() const
    {
        return mStr;
    }

    char argument::operator [] (int index) const
    {
        return mStr[index];
    }

    bool argument::operator ! () const
    {
        return empty();
    }

}
