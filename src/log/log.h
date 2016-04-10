#ifndef ARG3_LOG_H
#define ARG3_LOG_H

#include <iostream>
#include <string>

#ifndef __attribute__
#define __attribute__(x)
#endif

namespace arg3
{
    typedef enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_NONE } log_level;

    class log
    {
       public:
        static void trace(const std::string &value, std::ostream &out = std::cout);
        static void debug(const std::string &value, std::ostream &out = std::cout);
        static void info(const std::string &value, std::ostream &out = std::cout);
        static void error(const std::string &value, std::ostream &out = std::cerr);
        static void warn(const std::string &value, std::ostream &out = std::cout);

        static void trace(const char *const format, ...) __attribute__((format(printf, 1, 2)));
        static void debug(const char *const format, ...) __attribute__((format(printf, 1, 2)));
        static void info(const char *const format, ...) __attribute__((format(printf, 1, 2)));
        static void error(const char *const format, ...) __attribute__((format(printf, 1, 2)));
        static void warn(const char *const format, ...) __attribute__((format(printf, 1, 2)));

        static void trace(std::ostream &out, const char *const format, ...) __attribute__((format(printf, 1, 2)));
        static void debug(std::ostream &out, const char *const format, ...) __attribute__((format(printf, 1, 2)));
        static void info(std::ostream &out, const char *const format, ...) __attribute__((format(printf, 1, 2)));
        static void error(std::ostream &out, const char *const format, ...) __attribute__((format(printf, 1, 2)));
        static void warn(std::ostream &out, const char *const format, ...) __attribute__((format(printf, 1, 2)));

        log(log_level level = LOG_TRACE, std::ostream &out = std::cout);
        log(const arg3::log &other) = delete;
        log(arg3::log &&other) = delete;
        virtual ~log() = default;
        arg3::log &operator=(const arg3::log &other) = delete;
        arg3::log &operator=(arg3::log &&other) = delete;

        template <typename T>
        arg3::log &append(const T &value)
        {
            if (level_ >= minLevel_) header() << value << std::endl;

            return *this;
        }

        arg3::log &append(const char *value, ...) __attribute__((format(printf, 1, 2)));

        static void set_min_log_level(log_level lev);

        static log_level lookup_log_level(const std::string &value);

        template <typename T>
        arg3::log &operator<<(const T &val)
        {
            if (level_ >= minLevel_) header() << val << std::endl;

            return *this;
        }

       protected:
        std::ostream &header();

       private:
        static log_level minLevel_;
        arg3::log &append(const char *const format, va_list args);
        log_level level_;
        std::ostream &out_;
    };
}

#endif
