#include "log.h"
#include <cstdarg>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

namespace coda {
    namespace log {

        namespace output {
            std::ostream &stream = std::cout;

            std::ostream &print(std::ostream &os) { return os; }

            std::string timeinfo() {
                time_t current_time = time(nullptr);
                struct tm *timeinfo = std::localtime(&current_time);
                char buffer[BUFSIZ + 1] = {0};
                strftime(buffer, BUFSIZ, "%F %T", timeinfo);
                return buffer;
            }

            bool __enable_color = false;

            void enable_color(bool value) { __enable_color = value; }

        }

        namespace level {

            const char *NAMES[] = {"UNKN",  "ERROR", "WARN", "INFO",
                                   "DEBUG", "TRACE", nullptr
                                  };

            const char *COLORS[] = {"",           "\033[1;31m", "\033[1;33m", "\033[1;32m",
                                    "\033[1;36m", "\033[1;37m", nullptr
                                   };

            const char *CLEAR = "\033[0m";

            Type __current_log_level = Info;

            bool valid(Type value) { return (value <= __current_log_level); }

            void set(const std::string &name) {
                int i = 0;

                if (name.empty()) {
                    return;
                }

                for (; NAMES[i] != nullptr; i++) {
                    if (!strcasecmp(name.c_str(), NAMES[i])) {
                        __current_log_level = (Type)i;
                    }
                }
            }

            void set(Type type) {
                __current_log_level = type;
            }

            std::string format(Type level) {
                std::string buf("  ");

                if (output::__enable_color) {
                    buf += COLORS[level];
                }

                buf += NAMES[level];

                if (output::__enable_color) {
                    buf += CLEAR;
                }

                buf += timeinfo();
                buf += ": ";
                return buf;
            }
        } 
    } 
} 
