//
// Created by Ryan Jennings on 2018-03-26.
//
#include "color.h"
#include <sstream>
#include <vector>

namespace rj
{
    namespace terminal
    {

        // color related functions
        namespace color
        {
            // colorizes a string
            std::string colorize(const std::vector<Value> &colors, const std::string &value, bool reset)
            {
                std::ostringstream buf;

                buf << "\033[";

                for (auto it = colors.begin(); it != colors.end(); ++it) {
                    buf << *it;
                    if (it != --colors.end()) {
                        buf << ";";
                    }
                }
                buf << "m" << value;

                if (reset) {
                    buf << color::CLEAR;
                }
                return buf.str();
            }

            std::string B(const std::string &value)
            {
                return colorize({fg::BLACK}, value, true);
            }

            std::string r(const std::string &value)
            {
                return colorize({fg::RED}, value, true);
            }

            std::string g(const std::string &value)
            {
                return colorize({fg::GREEN}, value, true);
            }

            std::string y(const std::string &value)
            {
                return colorize({fg::YELLOW}, value, true);
            }

            std::string b(const std::string &value)
            {
                return colorize({fg::BLUE}, value, true);
            }

            std::string m(const std::string &value)
            {
                return colorize({fg::MAGENTA}, value, true);
            }

            std::string c(const std::string &value)
            {
                return colorize({fg::CYAN}, value, true);
            }

            std::string w(const std::string &value)
            {
                return colorize({fg::WHITE}, value, true);
            }
        }
    }
}
