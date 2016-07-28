#include "vt100.h"
#include <iostream>

namespace rj
{
    namespace terminal
    {
        data_buffer vt100::parse(const data_buffer &input)
        {
            data_buffer buf;

            for (auto pos = input.begin(); pos != input.end(); pos++) {
                if (*pos != ESCAPE) {
                    buf.push_back(*pos);
                    continue;
                }

                if (++pos == input.end()) break;

                auto code = parse_csi_code(buf, pos, input.end());

                if (code != nullptr) {
                    codes_[buf.size()] = code;
                }
            }

            return buf;
        }

        const map<size_t, shared_ptr<csi_code>> vt100::codes() const
        {
            return codes_;
        }

        shared_ptr<csi_code> vt100::parse_csi_code(data_buffer &output, data_buffer::const_iterator &start, data_buffer::const_iterator end) const
        {
            shared_ptr<csi_code> code = make_shared<csi_code>();

            if (*start > 32 && *start <= 47) {
                code->set_prefix(*start++);
            }

            auto &s = ++start;

            for (auto &last = s; s != end; ++s) {
                if (*s >= 64 && *s <= 126) {
                    if (last != s) {
                        string value(last, s);
                        try {
                            code->add_value(stoi(value));
                        } catch (const std::exception &e) {
                            std::cerr << "invalid csi code " << value << std::endl;
                        }
                    }
                    code->set_command(*s);
                    start = s;
                    return code;
                }

                if (*s == ';') {
                    if (last != s) {
                        string value(last, s);
                        try {
                            code->add_value(stoi(value));
                        } catch (const std::exception &e) {
                            std::cerr << "invalid csi code " << value << endl;
                        }
                        last = s;
                    }
                    continue;
                }


                if (*s < '0' || *s > '9') {
                    return nullptr;
                }
            }

            if (start != s) {
                start = s;
            }

            return nullptr;
        }

        csi_code::csi_code() : prefix_(0), command_(0)
        {
        }

        csi_code::~csi_code()
        {
        }

        void csi_code::add_value(int value)
        {
            values_.push_back(value);
        }

        void csi_code::set_prefix(char prefix)
        {
            prefix_ = prefix;
        }

        void csi_code::set_command(char command)
        {
            command_ = command;
        }

        string csi_code::to_string() const
        {
            ostringstream buf;

            buf << ESCAPE;

            if (prefix_ != 0) {
                buf << prefix_;
            }

            for (int i = 0, size = values_.size(); i < size; i++) {
                buf << values_[i];

                if (i + 1 < size) {
                    buf << ';';
                }
            }

            buf << command_;

            return buf.str();
        }
    }
}
