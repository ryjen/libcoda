#include "vt100.h"

namespace arg3
{
    namespace terminal
    {
        base_terminal::data_buffer vt100::parse(const data_buffer &input)
        {
            data_buffer buf;

            for (auto pos = input.begin(); pos != input.end(); pos++)
            {
                if (*pos != ESCAPE)
                {
                    buf.push_back(*pos);
                    continue;
                }

                if (++pos == input.end())
                    break;

                if (*pos == '[')
                {
                    parse_parameter_tag(buf, pos + 1, input.end());
                }
                else
                {
                    parse_tag(buf, pos, input.end());
                }
            }

            return buf;
        }

        void vt100::parse_parameter_tag( data_buffer &output, const data_buffer::const_iterator &start, const data_buffer::const_iterator &end) const
        {

        }

        void vt100::parse_tag(data_buffer &output, const data_buffer::const_iterator &start, const data_buffer::const_iterator &end) const
        {}


        attribute::attribute(initializer_list<int> values) : values_(values)
        {}

        string attribute::to_string() const
        {
            ostringstream buf;

            buf << ESCAPE;
            buf << "[";

            for (int i = 0, size = values_.size(); i < size; i++)
            {
                buf << values_[i];

                if (i + 1 == size)
                    buf << "m";
                else
                    buf << ";";
            }

            return buf.str();
        }
    }
}
