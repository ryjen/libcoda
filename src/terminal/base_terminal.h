#ifndef CODA_TERMINAL_BASE_TERMINAL_H_
#define CODA_TERMINAL_BASE_TERMINAL_H_

#include <functional>
#include <vector>

using namespace std;

namespace coda
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
