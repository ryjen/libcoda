#ifndef _ARG3_COLLECTIONS_H_
#define _ARG3_COLLECTIONS_H_

#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <list>
#include <iterator>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

namespace arg3
{

    template<typename K, typename V>
    string join(map<K, V> collection, const string &divider = ",", bool displayValues = false)
    {
        ostringstream buf;

        size_t size = collection.size();
        size_t count = 0;

for (auto & e : collection)
        {
            if (displayValues)
                buf << e.second;
            else
                buf << e.first;
            if (count++ < size - 1)
            {
                buf << ",";
            }
        }

        return buf.str();
    }
    template<typename K, typename V>
    string join(unordered_map<K, V> collection, const string &divider = ",", bool displayValues = false)
    {
        ostringstream buf;

        size_t size = collection.size();
        size_t count = 0;

for (auto & e : collection)
        {
            if (displayValues)
                buf << e.second;
            else
                buf << e.first;
            if (count++ < size - 1)
            {
                buf << ",";
            }
        }

        return buf.str();
    }
    template<typename T>
    string join(initializer_list<T> list, const string &delimiter = ",")
    {
        ostringstream buf;

        if (list.size() > 0)
        {
            ostream_iterator<T> it(buf, delimiter);

            copy(list.begin(), list.end() - 1, it);

            buf << *(list.end() - 1);
        }

        return buf.str();
    }

    template<typename T>
    string join(vector<T> list, const string &divider = ",")
    {
        ostringstream buf;

        if (list.size() > 0)
        {
            ostream_iterator<T> it(buf, divider.c_str());

            copy(list.begin(), list.end() - 1, it);

            buf << *(list.end() - 1);
        }

        return buf.str();
    }
}

#endif
