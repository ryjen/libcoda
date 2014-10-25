#include <iomanip>
#include <iostream>
#include <ctime>
#include "log.h"
#include "../string/str_util.h"

using namespace std;

namespace arg3
{
    const char *logNames[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "NONE"  };

    log::level log::minLevel_ = log::TRACE;

    log::log(log::level level, ostream &out) : level_(level), out_(out)
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

    void log::set_min_log_level(level lev)
    {
        minLevel_ = lev;
    }

    log::level log::lookup_log_level(const std::string &value)
    {
        for (level l = TRACE; l <= ERROR; l = static_cast<level>(static_cast<int>(l) + 1))
        {
            if (equals(value, logNames[l]))
                return l;
        }
        return minLevel_;
    }

    void log::debug(const string &value, ostream &out)
    {
        log(DEBUG, out).write(value);
    }

    void log::trace(const string &value, std::ostream &out)
    {
        log(TRACE, out).write(value);
    }
    void log::info(const string &value, ostream &out)
    {
        log(INFO, out).write(value);
    }
    void log::error(const string &value, ostream &out)
    {
        log(ERROR, out).write(value);
    }
    void log::warn(const string &value, ostream &out)
    {
        log(WARN, out).write(value);
    }

}
