#include <iomanip>
#include <iostream>
#include <ctime>
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
        log(LOG_DEBUG, out).write(value);
    }

    void log::trace(const string &value, std::ostream &out)
    {
        log(LOG_TRACE, out).write(value);
    }
    void log::info(const string &value, ostream &out)
    {
        log(LOG_INFO, out).write(value);
    }
    void log::error(const string &value, ostream &out)
    {
        log(LOG_ERROR, out).write(value);
    }
    void log::warn(const string &value, ostream &out)
    {
        log(LOG_WARN, out).write(value);
    }

}
