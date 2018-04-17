#include <iomanip>
#include <iostream>
#include <sstream>

#include "bigint.h"

using namespace std;

namespace coda
{
    bigint operator"" _bi(char c)
    {
        return bigint(c);
    }
    bigint operator"" _bi(const char *str, size_t sz)
    {
        return bigint(string(str).substr(0, sz).c_str());
    }
    bigint operator"" _bi(const char *cstr)
    {
        return bigint(cstr);
    }

    bigint::bigint()
    {
        init();
    }

    bigint::bigint(const char *x)
    {
        init();

        int len = strlen(x);

        if (len > 0) {
            reserve((len - 1) / 8 + 1);

            for (uint32_t i = 0; i < capacity; ++i) {
                array[i] = 0;
            }

            for (int i = 0, j = len - 1; j >= 0; ++i, --j) {
                array[i / 8] |= (bigint::char2int(x[j])) << ((i & 7) * 4);
            }
            size = (len - 1) / 8 + 1;
        }
    }

    bigint::bigint(int32_t x)
    {
        init();
        if (x >= 0) {
            if (x != 0) {
                reserve(1);
                array[0] = (uint32_t)x;
                size = 1;
            }
        } else {
            flipped = true;
            if (~x != 0) {
                reserve(1);
                array[0] = (uint32_t)~x;
                size = 1;
            }
        }
    }

    bigint::bigint(uint32_t x)
    {
        init();
        if (x != 0) {
            reserve(1);
            array[0] = x;
            size = 1;
        }
    }

    bigint::bigint(const bigint &x)
    {
        init();
        *this = x;
    }

    bigint::bigint(bigint &&x)
    {
        init();
        *this = std::move(x);
    }

    bigint::~bigint()
    {
        if (array) delete[] array;
    }

    bigint &bigint::operator=(const bigint &x)
    {
        reserve(x.size);
        for (uint32_t i = 0; i < x.size; ++i) {
            array[i] = x.array[i];
        }
        size = x.size;
        flipped = x.flipped;
        return *this;
    }
    bigint &bigint::operator=(bigint &&x)
    {
        if (this != &x) {
            array = std::move(x.array);
            size = x.size;
            flipped = x.flipped;
            capacity = x.capacity;
        }
        return *this;
    }
    bool bigint::operator==(int32_t x) const
    {
        if (x < 0) {
            return flipped && this->operator==(~x);
        }

        if (size == 0) {
            return x == 0;
        }

        return size == 1 && array[0] == (uint32_t)x;
    }

    bool bigint::operator==(uint32_t x) const
    {
        if (flipped)  // *this has infinitly many leading 1s
        {
            return false;
        }
        if (size == 0) {
            return x == 0;
        }
        return size == 1 && array[0] == x;
    }

    bool bigint::operator==(const bigint &x) const
    {
        if (size != x.size || flipped != x.flipped) {
            return false;
        }
        for (uint32_t i = 0; i < size; ++i) {
            if (array[i] != x.array[i]) {
                return false;
            }
        }
        return true;
    }

    bigint bigint::operator~() const
    {
        bigint tmp(*this);
        return tmp.flip();
    }

    bigint &bigint::flip()
    {
        flipped = !flipped;
        return *this;
    }

    bool bigint::operator!=(const bigint &x) const
    {
        return !(this->operator==(x));
    }

    bigint &bigint::operator&=(const bigint &x)
    {
        if (flipped) {
            // ~x & y = ~(x | ~y);
            this->flip();
            *this |= ~x;
            return this->flip();
        }
        if (x.flipped) {
            for (uint32_t i = 0, n = std::min(size, x.size); i < n; ++i) {
                array[i] &= ~x.array[i];
            }
        } else {
            size = std::min(size, x.size);
            for (uint32_t i = 0; i < size; ++i) {
                array[i] &= x.array[i];
            }
        }

        return this->trim();
    }

    bigint bigint::operator&(const bigint &x) const
    {
        bigint tmp(*this);
        return (tmp &= x);
    }

    bigint &bigint::operator|=(const bigint &x)
    {
        if (flipped) {
            this->flip();
            *this &= ~x;
            return this->flip();
        }

        if (x.flipped) {
            if (size < x.size) {
                reserve(x.size);
            }
            size = x.size;
            for (size_t i = 0; i < size; ++i) {
                array[i] = ~(array[i] | ~x.array[i]);
            }
            flipped = true;
        } else {
            if (size < x.size) {
                reserve(x.size);
                size = x.size;
            }
            for (uint32_t i = 0, n = std::min(size, x.size); i < n; ++i) {
                array[i] |= x.array[i];
            }
        }

        return this->trim();
    }

    bigint bigint::operator|(const bigint &x) const
    {
        bigint tmp(*this);
        return (tmp |= x);
    }

    bigint &bigint::operator^=(const bigint &x)
    {
        // ~x ^ ~y = x ^  y
        // ~x ^  y = x ^ ~y
        if (flipped) {
            this->flip();
            return (*this ^= ~x);
        }

        if (size < x.size) {
            reserve(x.size);
            size = x.size;
        }

        for (size_t i = 0; i < x.size; ++i) {
            array[i] ^= x.array[i];
        }
        flipped = x.flipped;
        return this->trim();
    }

    bigint bigint::operator^(const bigint &x) const
    {
        bigint tmp(*this);
        return (tmp ^= x);
    }

    bigint &bigint::operator>>=(int x)
    {
        if (x > 0 && size > 0) {
            int a = x % 32;
            size_t b = x / 32;
            if (b > 0) {
                for (size_t i = b; i < size; ++i) {
                    array[i - b] = array[i];
                }
                if (b < size) {
                    size -= b;
                } else {
                    size = 0;
                    return *this;
                }
            }

            if (a > 0) {
                // uint32_t mask = (1 << a) - 1;

                for (size_t i = 0; i < size - 1; ++i) {
                    array[i] = (array[i] >> a) | (array[i + 1] << (32 - a));
                }
                array[size - 1] = array[size - 1] >> a;
            }
        }

        return this->trim();
    }

    bigint bigint::operator>>(int x) const
    {
        bigint tmp(*this);
        return (tmp >>= x);
    }

    bigint &bigint::operator<<=(int x)
    {
        if (x > 0 && size > 0) {
            int a = x % 32;
            int b = x / 32;

            if (a > 0) {
                uint32_t sz = size;
                if (array[size - 1] >> (32 - a)) {
                    reserve(size + 1);
                    array[size] = array[size - 1] >> (32 - a);
                    sz = size + 1;
                }

                for (int i = size - 1; i > 0; --i) {
                    array[i] = (array[i - 1] >> (32 - a)) | (array[i] << a);
                }

                array[0] <<= a;

                size = sz;
            }

            if (b > 0) {
                reserve(size + b);
                size += b;

                for (int i = size - 1; i >= b; --i) {
                    array[i] = array[i - b];
                }

                for (int i = 0; i < b; ++i) {
                    array[i] = 0;
                }
            }
        }
        return this->trim();
    }

    bigint bigint::operator<<(int x) const
    {
        bigint tmp(*this);
        return (tmp <<= x);
    }

    void bigint::reserve(uint32_t n)
    {
        assert(n <= MAX_CAPACITY);

        if (capacity < n) {
            uint32_t c = capacity;
            while (c < n) {
                if (c < 16) {
                    ++c;
                } else {
                    c *= 2;
                }
            }

            uint32_t *a = new uint32_t[c];
            for (uint32_t i = 0; i < size; ++i) {
                a[i] = array[i];
            }

            delete[] array;
            array = a;
            capacity = c;
        }

        for (uint32_t i = size; i < n; ++i) {
            array[i] = 0;
        }
        return;
    }

    bigint &bigint::init()
    {
        flipped = false;
        array = NULL;
        size = 0;
        capacity = 0;
        return *this;
    }

    bigint &bigint::trim()
    {
        for (; size > 0 && array[size - 1] == 0; --size)
            ;
        return *this;
    }

    // private static functions
    uint32_t bigint::char2int(char x)
    {
        if ('0' <= x && x <= '9') {
            return x - '0';
        }
        if ('a' <= x && x <= 'f') {
            return x - 'a' + 10;
        }
        if ('A' <= x && x <= 'F') {
            return x - 'A' + 10;
        }
        throw "A heximal digit can only be one of '0-9a-fA-F'!";
    }

    string bigint::to_string() const
    {
        ostringstream buf;

        if (flipped) {
            for (auto i = size - 1; i > 0; --i) {
                buf << hex << setw(8) << setfill('1') << ~array[i];
            }
            buf << hex << setw(8) << setfill('1') << ~array[0];
        } else {
            for (auto i = size - 1; i > 0; --i) {
                buf << hex << setw(8) << setfill('0') << array[i];
            }
            buf << hex << setw(8) << setfill('0') << array[0];
        }

        string temp = buf.str();

        auto pos = temp.begin();

        while (pos != temp.end() && *pos == (flipped ? '1' : '0')) {
            ++pos;
        }

        if (pos != temp.begin())
            return string(pos, temp.end());
        else
            return temp;
    }
}
