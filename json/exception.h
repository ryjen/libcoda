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

            exception(exception &&other) : std::logic_error(other)
            {}

            exception(const exception &other) : std::logic_error(other)
            {}

            virtual ~exception() {}

            exception &operator=(const exception &e) {
                std::exception::operator=(e);
                return *this;
            }

            exception &operator=(exception &&e) {
                std::exception::operator=(std::move(e));
                return *this;
            }
        };
    }
}

#endif
