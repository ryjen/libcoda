#ifndef ARG3_ARGUMENT_H_
#define ARG3_ARGUMENT_H_

#include <string>

using namespace std;

namespace arg3
{
    /*
     * basically a string tokenizer
     */
    class argument
    {
    private:
        string str_;
    protected:
        size_t next(string &) const;
    public:
        argument(const string &);
        argument(const char *);
        argument();
        argument(const argument &other);
        argument(argument &&other);
        argument &operator=(const argument &other);
        argument &operator=(argument && other);
        virtual ~argument();
        string peek() const;
        string next();
        int next_int();
        double next_double();
        int64_t next_int64();
        bool next_bool();
        operator const string &();
        bool empty() const;
        bool operator ! () const;
        char operator[] (int) const;
        size_t length() const;
        string to_string() const;

        bool equals(const string &arg, bool caseSensitive = false) const;
        bool prefix(const string &arg, bool caseSensitive = false) const;
    };
}

#endif
