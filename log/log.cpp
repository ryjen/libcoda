#include <iomanip>
#include <iostream>
#include <ctime>
#include "log.h"
#include "../string/string.h"

using namespace std;

namespace arg3
{
    const char *logNames[] = { "TRACE", "DEBUG","INFO","WARN","ERROR",   };

    log::level log::minLevel_ = log::TRACE;

    log::log(log::level level, ostream &out) : level_(level), out_(out)
    {}

    ostream &log::header()
    {
        time_t current_time = time(NULL);

        out_ << "[" << logNames[level_] << "] " << std::put_time(std::localtime(&current_time), "%F %T") << ": ";

        return out_;
    }

    void log::setMinLogLevel(level lev)
    {
        minLevel_ = lev;
    }

    log::level log::lookupLogLevel(const std::string &value)
    {
        for(level l = TRACE; l <= ERROR; l++) {
            if(iequals(value, logNames[l]))
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