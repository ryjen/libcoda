#ifndef ARG3_TERMINAL_BASE_TERMINAL_H_
#define ARG3_TERMINAL_BASE_TERMINAL_H_

#include <vector>
#include <functional>

using namespace std;

namespace arg3
{
    namespace terminal
    {
        typedef char data_type;
        typedef vector<data_type> data_buffer;

        class base_terminal
        {
           public:
            virtual data_buffer parse(const data_buffer &input) = 0;

           private:
        };
    }
}

#endif
