#include <iterator>
#include <sstream>
#include <algorithm>
#include "strings.h"
#include "../format/format.h"

namespace arg3
{
    bool nullstr(const char *str)
    {
        return !str || !*str;
    }

    /*
     * Returns an initial-capped string.
     */
    string capitalize( const string &str )
    {
        string buf;

        if (str.length() == 0)
            return buf;

        for ( size_t i = 0; i < str.length(); i++ )
            buf += tolower(str[i]);

        buf[0] = toupper(buf[0]);
        return buf;
    }
    /*
     * Credit: http://www.secureprogramming.com/?action=view&feature=recipes&recipeid=3
     */
    bool is_valid_email(const string &address)
    {
        int count = 0;
        string::const_iterator c, domain;
        static char rfc822_specials[] = "()<>@,;:\\\"[]";

        /* first we validate the name portion (name@domain) */
        for (c = address.cbegin();  c  != address.cend();  c++)
        {
            if (*c == '\"' && (c == address.begin() || *(c - 1) == '.' || *(c - 1) ==
                               '\"'))
            {
                while (*++c)
                {
                    if (*c == '\"') break;
                    if (*c == '\\' && (*++c == ' ')) continue;
                    if (*c < ' ' || *c >= 127) return 0;
                }
                if (!*c++) return 0;
                if (*c == '@') break;
                if (*c != '.') return 0;
                continue;
            }
            if (*c == '@') break;
            if (*c <= ' ' || *c >= 127) return 0;
            if (strchr(rfc822_specials, *c)) return 0;
        }
        if (c == address.begin() || *(c - 1) == '.') return 0;

        /* next we validate the domain portion (name@domain) */
        if ((domain = ++c) == address.cend()) return 0;
        do
        {
            if (*c == '.')
            {
                if (c == domain || *(c - 1) == '.') return 0;
                count++;
            }
            if (*c <= ' ' || *c >= 127) return 0;
            if (strchr(rfc822_specials, *c)) return 0;
        }
        while (++c != address.cend());

        return (count >= 1);
    }

    /*
     * Return true if an argument is completely numeric.
     */
    int is_number ( const string &arg )
    {
        bool precision = false;
        auto c = arg.cbegin();

        if ( c == arg.cend() )
            return 0;

        if ( *c == '+' || *c == '-' )
            c++;

        for ( ; c != arg.cend(); c++ )
        {
            if ( *c == '.' )
            {
                precision = true;
                continue;
            }

            if ( !isdigit( *c ) )
                return 0;
        }

        return precision ? 2 : 1;
    }

    string ordinal_string(int n)
    {
        if (n == 1 || n == 0)
            return "first";
        else if (n == 2)
            return "second";
        else if (n == 3)
            return "third";
        else if (n % 10 == 1)
            return format("{0}st") << n;
        else if (n % 10 == 2)
            return format("{0}nd") << n;
        else if (n % 10 == 3)
            return format("{0}rd") << n;
        else
            return format("{0}th") << n;
    }

    string join(const string& value, string::size_type count, const string &delimiter)
    {
        ostringstream buf;

        if(value.length() > 0)
        {
            ostream_iterator<string::value_type> it(buf, delimiter.c_str());

            for(string::size_type i = 0; i < count-1; i++)
                copy(value.begin(), value.end(), it);

            buf << value;
        }
        return buf.str();
    }

    string join(string::value_type value, string::size_type count, const string &delimiter)
    {
        ostringstream buf;

        if(count > 0)
        {
            for(string::size_type i = 0; i < count-1; i++)
            {
                buf.put(value);
                buf.put(',');
            }

            buf.put(value);
        }
        return buf.str();
    }

    vector<string> split(const string& s, const string& delim, const bool keep_empty)
    {
        vector<string> result;
        if (delim.empty())
        {
            result.push_back(s);
            return result;
        }
        string::const_iterator substart = s.begin(), subend;
        while (true)
        {
            subend = search(substart, s.end(), delim.begin(), delim.end());
            string temp(substart, subend);
            if (keep_empty || !temp.empty())
            {
                result.push_back(temp);
            }
            if (subend == s.end())
            {
                break;
            }
            substart = subend + delim.size();
        }
        return result;
    }
}
