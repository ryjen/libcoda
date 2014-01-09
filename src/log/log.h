#ifndef ARG3_LOG_H
#define ARG3_LOG_H

#include <iostream>
#include <string>

namespace arg3
{
    class log
    {
    public:
        typedef enum { TRACE, DEBUG, INFO, WARN, ERROR, NONE } level;

        static void trace(const std::string &value, std::ostream &out = std::cout);
        static void debug(const std::string &value, std::ostream &out = std::cout);
        static void info(const std::string &value, std::ostream &out = std::cout);
        static void error(const std::string &value, std::ostream &out = std::cerr);
        static void warn(const std::string &value, std::ostream &out = std::cout);

        log(level level = TRACE, std::ostream &out = std::cout);
        log(const log &other) = delete;
        log(log &&other) = delete;
        virtual ~log() = default;
        log &operator=(const log &other) = delete;
        log &operator=(log && other) = delete;

        template<typename T>
        log &write(const T &value)
        {
            if (level_ >= minLevel_)

                header() << value << std::endl;

            return *this;
        }

        static void set_min_log_level(level lev);

        static level lookup_log_level(const std::string &value);

        template<typename T>
        log &operator<<(const T &val)
        {
            if (level_ >= minLevel_)
                header() << val << std::endl;

            return *this;
        }

    protected:
        std::ostream &header();
    private:
        static level minLevel_;

        level level_;
        std::ostream &out_;
    };
}

#endif
