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
        string mStr;
    protected:
        size_t next(string &) const;
    public:
        argument(const string &);
        virtual ~argument();
        string peek() const;
        string next();
        int nextInt();
        double nextDouble();
        int64_t nextInt64();
        bool nextBool();
        operator const string &();
        bool empty() const;
        bool operator ! () const;
        char operator[] (int) const;
        size_t length() const;
        string to_string() const;
    };

}

#endif
