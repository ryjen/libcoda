#include <iterator>
#include <sstream>
#include <algorithm>
#include "string.h"
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

    string join(const string &value, string::size_type count, const string &delimiter)
    {
        ostringstream buf;

        if (value.length() > 0)
        {
            ostream_iterator<string::value_type> it(buf, delimiter.c_str());

            for (string::size_type i = 0; i < count - 1; i++)
                copy(value.begin(), value.end(), it);

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
                buf.put(',');
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

    bool equals(const string& astr, const string& bstr, bool caseSensitive)
    {
        for (auto a = astr.cbegin(), b = bstr.cbegin();
                a != astr.cend() || b != bstr.cend(); a++, b++ )
        {
            if ( tolower(*a) != tolower(*b) )
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
            if ( tolower(*a) != tolower(*b) )
                return false;
        }

        return true;
    }

    bool suffix( const string &astr, const string &bstr, bool caseSensitive )
    {
        string::size_type sstr1, sstr2;

        sstr1 = astr.length();
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
            return true;

        c0 = tolower(astr[0]);

        sstr2 = bstr.length();

        for ( ichar = 0; ichar <= sstr2 - sstr1; ichar++ )
        {
            if ( c0 == tolower(bstr[ichar]) && prefix( astr, bstr.substr(ichar), caseSensitive ) )
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


        static inline bool is_base64(unsigned char c) {
            return (isalnum(c) || (c == '+') || (c == '/'));
        }

        string encode(const binary &value) {
            return encode(value.data(), value.size());
        }

        string encode(unsigned char const* bytes_to_encode, size_t in_len) {
            string ret;
            int i = 0;
            int j = 0;
            unsigned char char_array_3[3];
            unsigned char char_array_4[4];

            while (in_len--) {
                char_array_3[i++] = *(bytes_to_encode++);
                if (i == 3) {
                    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                    char_array_4[3] = char_array_3[2] & 0x3f;

                    for(i = 0; (i <4) ; i++)
                        ret += base64_chars[char_array_4[i]];
                    i = 0;
                }
            }

            if (i)
            {
                for(j = i; j < 3; j++)
                    char_array_3[j] = '\0';

                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for (j = 0; (j < i + 1); j++)
                    ret += base64_chars[char_array_4[j]];

                while((i++ < 3))
                    ret += '=';

            }

            return ret;

        }

        binary decode(const string &encoded_string) {
            size_t in_len = encoded_string.size();
            size_t i = 0;
            size_t j = 0;
            int in_ = 0;
            unsigned char char_array_4[4], char_array_3[3];
            binary ret;

            while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
                char_array_4[i++] = encoded_string[in_];
                in_++;
                if (i ==4) {
                    for (i = 0; i <4; i++)
                        char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

                    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                    for (i = 0; (i < 3); i++)
                        ret.push_back(char_array_3[i]);
                    i = 0;
                }
            }

            if (i) {
                for (j = i; j <4; j++)
                    char_array_4[j] = 0;

                for (j = 0; j <4; j++)
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
}
