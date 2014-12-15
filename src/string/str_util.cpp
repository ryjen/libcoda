#include <iterator>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <vector>
#include "str_util.h"
#include "config.h"
#include <sys/stat.h>

extern "C"
{
#ifdef WIN32
#include <Rpc.h>
#else
#ifdef HAVE_UUID_UUID_H
#include <uuid/uuid.h>
#endif
#endif
}

using namespace std;

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
        static char rfc822_specials[] = "()<>@,; : \\\"[]";

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
        char buf[BUFSIZ + 1] = {0};

        if (n == 1 || n == 0)
            return "first";
        else if (n == 2)
            return "second";
        else if (n == 3)
            return "third";
        else if (n % 10 == 1)
        {
            snprintf(buf, BUFSIZ, "%dst", n);
            return buf;
        }
        else if (n % 10 == 2)
        {
            snprintf(buf, BUFSIZ, "%dnd", n);
            return buf;
        }
        else if (n % 10 == 3)
        {
            snprintf(buf, BUFSIZ, "%drd", n);
            return buf;
        }
        else
        {
            snprintf(buf, BUFSIZ, "%dth", n);
            return buf;
        }
    }

    string join(const string &value, string::size_type count, const string &delimiter)
    {
        ostringstream buf;

        if (value.length() > 0)
        {
            for (string::size_type i = 0; i < count - 1; i++)
            {
                buf << value;
                buf << delimiter;
            }

            buf << value;
        }
        return buf.str();
    }

    string join(string::value_type value, string::size_type count, const string &delimiter)
    {
        ostringstream buf;

        if (count > 0)
        {
            for (string::size_type i = 0; i < count - 1; i++)
            {
                buf.put(value);
                buf << delimiter;
            }

            buf.put(value);
        }
        return buf.str();
    }

    vector<string> split(const string &s, const string &delim, const bool keep_empty)
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

    bool equals(const string &astr, const string &bstr, bool caseSensitive)
    {
        for (auto a = astr.cbegin(), b = bstr.cbegin();
                a != astr.cend() || b != bstr.cend(); a++, b++ )
        {
            if ( caseSensitive ? (*a != *b) : (tolower(*a) != tolower(*b)) )
                return false;
        }

        return true;
    }


    bool prefix(const string &astr, const string &bstr, bool caseSensitive)
    {
        if (astr.length() == 0)
        {
            return false;
        }

        for ( auto a = astr.cbegin(), b = bstr.cbegin();
                a != astr.cend(); a++, b++ )
        {
            if ( caseSensitive ? (*a != *b) : (tolower(*a) != tolower(*b) ) )
                return false;
        }

        return true;
    }

    bool suffix( const string &astr, const string &bstr, bool caseSensitive )
    {
        string::size_type sstr1, sstr2;

        sstr1 = astr.length();

        if (sstr1 == 0) return false;

        sstr2 = bstr.length();

        if ( sstr1 <= sstr2 && equals( astr, bstr.substr(sstr2 - sstr1), caseSensitive ) )
            return true;
        else
            return false;
    }

    bool contains( const string &astr, const string &bstr, bool caseSensitive )
    {
        int sstr1;
        int sstr2;
        int ichar;
        char c0;

        if ( (sstr1 = astr.length()) == 0 )
            return false;

        c0 = tolower(astr[0]);

        sstr2 = bstr.length();

        for ( ichar = 0; ichar <= sstr2 - sstr1; ichar++ )
        {
            if ( c0 == (caseSensitive ? bstr[ichar] : tolower(bstr[ichar]) ) && prefix( astr, bstr.substr(ichar), caseSensitive ) )
                return true;
        }

        return false;
    }

    namespace base64
    {
        static const string base64_chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";


        static inline bool is_base64(unsigned char c)
        {
            return (isalnum(c) || (c == '+') || (c == '/'));
        }

        string encode(const binary &value)
        {
            return encode(value.data(), value.size());
        }

        string encode(unsigned char const *bytes_to_encode, size_t in_len)
        {
            string ret;
            int i = 0;
            int j = 0;
            unsigned char char_array_3[3];
            unsigned char char_array_4[4];

            while (in_len--)
            {
                char_array_3[i++] = *(bytes_to_encode++);
                if (i == 3)
                {
                    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                    char_array_4[3] = char_array_3[2] & 0x3f;

                    for (i = 0; (i < 4) ; i++)
                        ret += base64_chars[char_array_4[i]];
                    i = 0;
                }
            }

            if (i)
            {
                for (j = i; j < 3; j++)
                    char_array_3[j] = '\0';

                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for (j = 0; (j < i + 1); j++)
                    ret += base64_chars[char_array_4[j]];

                while ((i++ < 3))
                    ret += '=';

            }

            return ret;

        }

        binary decode(const string &encoded_string)
        {
            size_t in_len = encoded_string.size();
            size_t i = 0;
            size_t j = 0;
            int in_ = 0;
            unsigned char char_array_4[4], char_array_3[3];
            binary ret;

            while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
            {
                char_array_4[i++] = encoded_string[in_];
                in_++;
                if (i == 4)
                {
                    for (i = 0; i < 4; i++)
                        char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

                    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                    for (i = 0; (i < 3); i++)
                        ret.push_back(char_array_3[i]);
                    i = 0;
                }
            }

            if (i)
            {
                for (j = i; j < 4; j++)
                    char_array_4[j] = 0;

                for (j = 0; j < 4; j++)
                    char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
            }

            return ret;
        }
    }

    time_t datetime(const std::string &s, const std::string &format)
    {
        struct tm tp;

        if (!strptime(s.c_str(), format.c_str(), &tp))
            return 0;

        return mktime(&tp);
    }


    int sprintf(std::string &ret, const char *fmt, ...)
    {
        char *buf;
        int bufsize;
        char *newbuf;
        size_t nextsize;
        int outsize;
        va_list args;

        bufsize = 0;
        outsize = 0;
        for (;;)
        {
            if (bufsize == 0)
            {
                bufsize = strlen(fmt);
                if ((buf = (char *)malloc(bufsize)) == NULL)
                {
                    return -1;
                }
            }
            else if ((newbuf = (char *)realloc(buf, nextsize)) != NULL)
            {
                buf = newbuf;
                bufsize = nextsize;
            }
            else
            {
                free(buf);
                return outsize;
            }

            va_start(args, fmt);

            outsize = vsnprintf(buf, bufsize, fmt, args);

            va_end(args);

            if (outsize == -1)
            {
                /* Clear indication that output was truncated, but no
                 * clear indication of how big buffer needs to be, so
                 * simply double existing buffer size for next time.
                 */
                nextsize = bufsize * 2;

            }
            else if (outsize == bufsize)
            {
                /* Output was truncated (since at least the \0 could
                 * not fit), but no indication of how big the buffer
                 * needs to be, so just double existing buffer size
                 * for next time.
                 */
                nextsize = bufsize * 2;

            }
            else if (outsize > bufsize)
            {
                /* Output was truncated, but we were told exactly how
                 * big the buffer needs to be next time. Add two chars
                 * to the returned size. One for the \0, and one to
                 * prevent ambiguity in the next case below.
                 */
                nextsize = outsize + 2;

            }
            else if (outsize == bufsize - 1)
            {
                /* This is ambiguous. May mean that the output string
                 * exactly fits, but on some systems the output string
                 * may have been trucated. We can't tell.
                 * Just double the buffer size for next time.
                 */
                nextsize = bufsize * 2;

            }
            else
            {
                /* Output was not truncated */
                break;
            }
        }
        ret = buf;
        free(buf);
        return outsize;
    }

    std::string &ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }

    // trim from end
    std::string &rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }

    // trim from both ends
    std::string &trim(std::string &s)
    {
        return ltrim(rtrim(s));
    }

    std::string generate_uuid()
    {
#ifdef WIN32
        UUID uuid;
        UuidCreate ( &uuid );

        unsigned char *str;
        UuidToStringA ( &uuid, &str );

        std::string s( ( char *) str );

        RpcStringFreeA ( &str );

        return s;
#else
#ifdef HAVE_LIBUUID
        char s[37] = {0};
        uuid_t uuid;
        uuid_generate_random ( uuid );
        uuid_unparse ( uuid, s );

        return s;
#else
        throw std::runtime_error("uuid library not available.");
#endif
#endif
    }

    bool dir_exists(const std::string &s)
    {
        struct stat info;

        if (stat( s.c_str(), &info ) != 0)
            return false;
        else if (info.st_mode & S_IFDIR)
            return true;
        else
            return false;
    }

    bool file_exists(const std::string &s)
    {
        struct stat info;

        if (stat( s.c_str(), &info ) != 0)
            return false;
        else
            return true;
    }
}
