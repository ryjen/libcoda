#include "vt100.h"

base_terminal::data_buffer vt100::parse(const data_buffer &input) const
{
    data_buffer buf;

    for (auto pos = input.begin(); pos != input.end(); pos++)
    {
        if (*pos != ECAPE)
        {
            buf.push_back(*pos);
            continue;
        }

        if (++pos == input.end())
            break;

        if (*pos == '[')
        {
            parse_parameter_tag(buf, pos, input.end());
        }
        else
        {
            parse_tag(buf, pos, intput.end());
        }
    }

    return buf;
}

void vt100::parse_parameter_tag( data_buffer &output, const data_buffer::iterator &start, const data_buffer::iterator &end) const
{}

void vt100::parse_tag(data_buffer &output, const data_buffer::iterator &start, const data_buffer::iterator &end) const
{}
