#ifndef ARG3_TERMINAL_VT100_H_
#define ARG3_TERMINAL_VT100_H_

namespace arg3
{
    namespace terminal
    {
        class vt100 : public base_terminal
        {
        public:
            constexpr static const data_type ESCAPE = '\033';

            base_terminal::data_buffer parse(const data_buffer &input) const;
        private:
            void parse_parameter_tag( data_buffer &output, const data_buffer::iterator &start, const data_buffer::iterator &end) const;
            void parse_tag(data_buffer &output, const data_buffer::iterator &start, const data_buffer::iterator &end) const;
        };
    }
}

#endif
