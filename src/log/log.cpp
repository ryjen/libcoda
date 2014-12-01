#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstdarg>
#include "log.h"
#include "../string/str_util.h"

using namespace std;

namespace arg3
{
    const char *logNames[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "NONE"  };

    log_level log::minLevel_ = LOG_TRACE;

    log::log(log_level level, ostream &out) : level_(level), out_(out)
    {}

    ostream &log::header()
    {
        time_t current_time = time(NULL);
        struct tm *timeinfo = std::localtime(&current_time);
        char buffer[BUFSIZ + 1] = {0};
        strftime(buffer, BUFSIZ, "%F %T", timeinfo);
        out_ << "[" << logNames[level_] << "] " << buffer << ": ";
        return out_;
    }

    log &log::append(const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        append(format, args);
        va_end(args);
        return *this;
    }

    log &log::append(const char *const format, va_list args)
    {
        char buf[BUFSIZ + 1] = {0};

        size_t len = vsnprintf(buf, BUFSIZ, format, args);

        if (level_ >= minLevel_ && len > 0)
            header() << buf << std::endl;

        return *this;
    }

    void log::set_min_log_level(log_level lev)
    {
        minLevel_ = lev;
    }

    log_level log::lookup_log_level(const std::string &value)
    {
        for (log_level l = LOG_TRACE; l <= LOG_ERROR; l = static_cast<log_level>(static_cast<int>(l) + 1))
        {
            if (equals(value, logNames[l]))
                return l;
        }
        return minLevel_;
    }

    void log::debug(const string &value, ostream &out)
    {
        log(LOG_DEBUG, out).append(value);
    }

    void log::trace(const string &value, std::ostream &out)
    {
        log(LOG_TRACE, out).append(value);
    }
    void log::info(const string &value, ostream &out)
    {
        log(LOG_INFO, out).append(value);
    }
    void log::error(const string &value, ostream &out)
    {
        log(LOG_ERROR, out).append(value);
    }
    void log::warn(const string &value, ostream &out)
    {
        log(LOG_WARN, out).append(value);
    }

    void log::debug(const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        log(LOG_DEBUG, std::cout).append(format, args);
        va_end(args);
    }

    void log::trace(const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        log(LOG_TRACE, std::cout).append(format, args);
        va_end(args);
    }
    void log::info(const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        log(LOG_INFO, std::cout).append(format, args);
        va_end(args);
    }
    void log::error(const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        log(LOG_ERROR, std::cerr).append(format, args);
        va_end(args);
    }
    void log::warn(const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        log(LOG_WARN, std::cout).append(format, args);
        va_end(args);
    }

    void log::debug(std::ostream &out, const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        log(LOG_DEBUG, out).append(format, args);
        va_end(args);
    }

    void log::trace(std::ostream &out, const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        log(LOG_TRACE, out).append(format, args);
        va_end(args);
    }
    void log::info(std::ostream &out, const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        log(LOG_INFO, out).append(format, args);
        va_end(args);
    }
    void log::error(std::ostream &out, const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        log(LOG_ERROR, out).append(format, args);
        va_end(args);
    }
    void log::warn(std::ostream &out, const char *const format, ...)
    {
        va_list args;
        va_start(args, format);
        log(LOG_WARN, out).append(format, args);
        va_end(args);
    }
}
