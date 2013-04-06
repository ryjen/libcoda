#ifndef ARG3_JSON_EXCEPTION_H_
#define ARG3_JSON_EXCEPTION_H_

#include <exception>
#include <string>

namespace arg3
{
    namespace json
    {
        class exception : public std::logic_error
        {
        public:
            exception(const std::string &what) : std::logic_error(what)
            {}
        };
    }
}

#endif
