#ifndef ARG3_ARGUMENT_H_
#define ARG3_ARGUMENT_H_

#include <string>

namespace arg3
{
    /*
     * basically a string tokenizer
     */
    class argument
    {
    private:
        std::string str_;
    protected:
        size_t next(std::string &) const;
    public:
        argument(const std::string &);
        argument(const char *);
        argument();
        argument(const argument &other);
        argument(argument &&other);
        argument &operator=(const argument &other);
        argument &operator=(argument && other);
        virtual ~argument();
        std::string peek() const;
        std::string next();
        int next_int();
        double next_double();
        int64_t next_int64();
        bool next_bool();
        operator const std::string &();
        bool empty() const;
        bool operator ! () const;
        char operator[] (int) const;
        size_t length() const;
        std::string to_string() const;

        bool equals(const std::string &arg, bool caseSensitive = false) const;
        bool prefix(const std::string &arg, bool caseSensitive = false) const;

        bool operator==(const std::string &arg) const;
        bool operator!=(const std::string &arg) const;
        bool operator==(const char *const arg) const;
        bool operator!=(const char *const arg) const;
        bool operator==(const argument &arg) const;
        bool operator!=(const argument &arg) const;
    };

    bool operator==(const std::string &a1, const argument &a2);
    bool operator!=(const std::string &a1, const argument &a2);
    bool operator==(const char *const a1, const argument &a2);
    bool operator!=(const char *const a1, const argument &a2);
}

#endif
