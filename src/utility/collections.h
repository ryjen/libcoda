#ifndef CODA_COLLECTIONS_H
#define CODA_COLLECTIONS_H

#include <algorithm>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

namespace coda
{
    template <typename K, typename V>
    string join(map<K, V> collection, bool displayValues = false, const string &divider = ",")
    {
        ostringstream buf;

        size_t size = collection.size();
        size_t count = 0;

        for (auto &e : collection) {
            if (displayValues) {
                buf << e.second;
            } else {
                buf << e.first;
            }
            if (count++ < size - 1) {
                buf << ",";
            }
        }

        return buf.str();
    }
    template <typename K, typename V>
    string join(unordered_map<K, V> collection, bool displayValues = false, const string &divider = ",")
    {
        ostringstream buf;

        size_t size = collection.size();
        size_t count = 0;

        for (auto &e : collection) {
            if (displayValues) {
                buf << e.second;
            } else {
                buf << e.first;
            }
            if (count++ < size - 1) {
                buf << ",";
            }
        }

        return buf.str();
    }
    template <typename T>
    string join(initializer_list<T> list, const string &delimiter = ",")
    {
        ostringstream buf;

        if (list.size() > 0) {
            ostream_iterator<T> it(buf, delimiter);

            copy(list.begin(), list.end() - 1, it);

            buf << *(list.end() - 1);
        }

        return buf.str();
    }

    template <typename T>
    string join(vector<T> list, const string &divider = ",")
    {
        ostringstream buf;

        if (list.size() > 0) {
            ostream_iterator<T> it(buf, divider.c_str());

            copy(list.begin(), list.end() - 1, it);

            buf << *(list.end() - 1);
        }

        return buf.str();
    }
}

#endif
