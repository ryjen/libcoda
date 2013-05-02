#ifndef ARG3_DLM_BIG_INT_H
#define ARG3_DLM_BIG_INT_H

#include <cstdint>
#include <cassert>
#include <ostream>
#include <algorithm>
#include <cstring>

namespace arg3
{

    class bigint
    {
    public:   // public constants
        static uint32_t const MAX_CAPACITY = 1024;

    private:  // private member variables
        // let x = sum_{i = 0}^{size - 1} (array[i] * (2^32)^i)
        // *ths == (flipped ? ~x : x);
        uint32_t *array;
        // array[size - 1] must not be 0,
        // and assume that array[x] == 0 for all x >= size
        uint32_t size;
        uint32_t capacity;
        bool flipped;
    public:   // public member functions
        bigint();

        explicit bigint(const char *x);

        bigint(int32_t x);

        bigint(uint32_t x);

        bigint(const bigint &x);

        virtual ~bigint();

        std::string to_string() const;

        bigint &operator= (const bigint &x);

        bool operator== (int32_t x) const;

        bool operator== (uint32_t x) const;

        bool operator== (const bigint &x) const;

        bigint operator~ () const;

        bigint &flip();

        bool operator!= (const bigint &x) const;

        bigint &operator&= (const bigint &x);

        bigint operator& (const bigint &x) const;

        bigint &operator|= (const bigint &x);

        bigint operator| (const bigint &x) const;

        bigint &operator^= (const bigint &x);

        bigint operator^ (const bigint &x) const;

        bigint &operator>>= (int x);

        bigint operator>> (int x) const;

        bigint &operator<<= (int x);

        bigint operator<< (int x) const;

        void reserve(uint32_t n);

    private:  // private member functions
        bigint &init();

        bigint &trim();

    private: // private static functions
        static uint32_t char2int(char x);

    public: // friends
        friend std::ostream &operator<< (std::ostream &, const bigint &);
        template<class T> friend bool operator== (const T &, const bigint &);
    };

    template<class T>
    bool operator== (const T &a, const bigint &b)
    {
        return b == a;
    }

}

#endif // #ifndef _STIMIM_BIG_INT_
