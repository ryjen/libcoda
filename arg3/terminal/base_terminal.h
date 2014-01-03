#ifndef ARG3_TERMINAL_BASE_TERMINAL_H_
#define ARG3_TERMINAL_BASE_TERMINAL_H_

namespace arg3
{
    namespace terminal
    {
        class base_terminal
        {
        public:
            typedef char data_type;
            typedef vector<data_type> data_buffer;

            virtual data_buffer parse(const data_buffer &input) = 0;
        private:
        }
    }
}

#endif
