#ifndef ARG3_TERMINAL_VT100_H_
#define ARG3_TERMINAL_VT100_H_

#include "base_terminal.h"
#include <string>
#include <sstream>
#include <map>

using namespace std;

namespace arg3
{
    namespace terminal
    {

        class csi_code
        {
        public:
            csi_code();
            string to_string() const;
            void add_value(int value);
            void set_prefix(char prefix);
            void set_command(char command);

        private:
            vector<int> values_;
            char prefix_;
            char command_;
        };

        class vt100 : public base_terminal
        {
        public:
            data_buffer parse(const data_buffer &input);
            const map<size_t, shared_ptr<csi_code>> codes() const;
        private:
            shared_ptr<csi_code> parse_csi_code( data_buffer &output, data_buffer::const_iterator &start, data_buffer::const_iterator end) const;
            map<size_t, shared_ptr<csi_code>> codes_;
        };

        constexpr static const data_type ESCAPE = '\033';

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
