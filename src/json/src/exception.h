#ifndef CODA_JSON_EXCEPTION_H
#define CODA_JSON_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace coda
{
    namespace json
    {
        class exception : public std::logic_error
        {
           public:
            exception(const std::string &what) : std::logic_error(what)
            {
            }

            exception(exception &&other) : std::logic_error(other)
            {
            }

            exception(const exception &other) : std::logic_error(other)
            {
            }

            virtual ~exception()
            {
            }

            exception &operator=(const exception &e)
            {
                std::exception::operator=(e);
                return *this;
            }

            exception &operator=(exception &&e)
            {
                std::exception::operator=(std::move(e));
                return *this;
            }
        };

        class not_implemented_exception : public exception
        {
           public:
            not_implemented_exception() : exception("not implemented")
            {
            }
        };
    }
}

#endif
