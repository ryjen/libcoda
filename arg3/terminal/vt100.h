#ifndef ARG3_TERMINAL_VT100_H_
#define ARG3_TERMINAL_VT100_H_

#include "base_terminal.h"

namespace arg3
{
    namespace terminal
    {
        class vt100 : public base_terminal
        {
        public:
            constexpr static const data_type ESCAPE = '\033';

            data_buffer parse(const data_buffer &input);
        private:
            void parse_parameter_tag( data_buffer &output, const data_buffer::const_iterator &start, const data_buffer::const_iterator &end) const;
            void parse_tag(data_buffer &output, const data_buffer::const_iterator &start, const data_buffer::const_iterator &end) const;
        };
    }
}

#endif
