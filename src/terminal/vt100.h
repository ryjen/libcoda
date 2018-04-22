#ifndef CODA_TERMINAL_VT100_H_
#define CODA_TERMINAL_VT100_H_

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include "base_terminal.h"

using namespace std;

namespace coda
{
    namespace terminal
    {
        class csi_code
        {
           public:
            csi_code() noexcept;
            csi_code(const csi_code &other) = default;
            csi_code(csi_code &&other) = default;
            ~csi_code() noexcept;
            csi_code &operator=(const csi_code &other) = default;
            csi_code &operator=(csi_code &&other) = default;
            string to_string() const;
            void add_value(int value);
            void set_prefix(char prefix) noexcept;
            void set_command(char command) noexcept;

           private:
            vector<int> values_;
            char prefix_;
            char command_;
        };

        class vt100 : public base_terminal
        {
           public:
            data_buffer parse(const data_buffer &input);
            const map<size_t, shared_ptr<csi_code>> codes() const noexcept;

           private:
            shared_ptr<csi_code> parse_csi_code(data_buffer &output, data_buffer::const_iterator &start, data_buffer::const_iterator end) const;
            map<size_t, shared_ptr<csi_code>> codes_;
        };

        constexpr static const data_type ESCAPE = '\033';

    }
}

#endif
