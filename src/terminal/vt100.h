#ifndef ARG3_TERMINAL_VT100_H_
#define ARG3_TERMINAL_VT100_H_

#include "base_terminal.h"
#include <string>
#include <sstream>

using namespace std;

namespace arg3
{
    namespace terminal
    {
        class vt100 : public base_terminal
        {
        public:

            data_buffer parse(const data_buffer &input);
        private:
            void parse_parameter_tag( data_buffer &output, const data_buffer::const_iterator &start, const data_buffer::const_iterator &end) const;
            void parse_tag(data_buffer &output, const data_buffer::const_iterator &start, const data_buffer::const_iterator &end) const;
        };

        class attribute
        {
        public:
            attribute(initializer_list<int> values);
            string to_string() const;
        private:
            vector<int> values_;
        };

        constexpr static const base_terminal::data_type ESCAPE = '\033';

        // Attributes
        constexpr static int RESET = 0;
        constexpr static int BRIGHT = 1;
        constexpr static int DIM = 2;
        constexpr static int UNDERSCORE = 4;
        constexpr static int BLINK = 5;
        constexpr static int REVERSE = 7;
        constexpr static int HIDDEN = 8;

        // Foreground Colors
        constexpr static int BLACK = 30;
        constexpr static int RED = 31;
        constexpr static int GREEN = 32;
        constexpr static int YELLOW = 33;
        constexpr static int BLUE = 34;
        constexpr static int MAGENTA = 35;
        constexpr static int CYAN = 36;
        constexpr static int WHITE = 37;

        // Background Colours
        constexpr static int BACKGROUND_ADD = 10;
    }
}

#endif
