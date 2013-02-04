#ifndef _ARG3_STRINGS_H_
#define _ARG3_STRINGS_H_

#include <string>

using namespace std;

namespace arg3 {
	typedef basic_string<unsigned char> ustring;

    // checks if a cstring is null or empty
    bool nullstr(const char *);
    // uppercases the first letter
    string capitalize(const string &);
    int is_number(const string &);
    // true if string is a valid email address
    bool is_valid_email(const string &);
    // ordinal string of an integer. ex. 2 = 2nd, 14 = 14th
    string ordinal_string(int);

    string join(const string &str, size_t count, const string &delimiter = ",");
}

#endif
