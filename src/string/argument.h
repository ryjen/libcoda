#ifndef CODA_ARGUMENT_H_
#define CODA_ARGUMENT_H_

#include <string>

namespace coda
{
    /*
     * basically a string tokenizer thats aware of quotes/parenthesis
     */
    class argument
    {
       private:
        std::string str_;

       protected:
        size_t next(std::string &) const;

       public:
        argument(const std::string &);
        argument();
        argument(const argument &other);
        argument(argument &&other);
        argument &operator=(const argument &other);
        argument &operator=(argument &&other);
        virtual ~argument();

        //! peek at the next argument
        /*!
         * @returns string the next available argument
         *
         * Notes: will not remove the argument from the original
         */
        std::string peek() const;
        //! gets the next argument
        /*!
         * @returns string the next argument
         *
         * Notes: will remove the argument from the original
         */
        std::string next();

        long next_number();
        double next_real();
        bool next_bool();
        operator const std::string &();
        bool empty() const;
        bool operator!() const;
        char operator[](int) const;
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

    argument operator"" _arg(const char *cstr, size_t len);

    bool operator==(const std::string &a1, const argument &a2);
    bool operator!=(const std::string &a1, const argument &a2);
    bool operator==(const char *const a1, const argument &a2);
    bool operator!=(const char *const a1, const argument &a2);
}

#endif
