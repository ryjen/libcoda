#ifndef ARG3_JSON_ARRAY_ITERATOR_H_
#define ARG3_JSON_ARRAY_ITERATOR_H_

#include "object.h"
#include <string>
#include <iterator>

using namespace std;

namespace arg3
{
    namespace json
    {
        class object;
        class array;

        class array_iterator : public iterator<random_access_iterator_tag, object>
        {
            friend class array;

        public:
            typedef random_access_iterator_tag iterator_category;
            typedef typename iterator<random_access_iterator_tag, object>::value_type value_type;
            typedef typename iterator<random_access_iterator_tag, object>::difference_type difference_type;
            typedef typename iterator<random_access_iterator_tag, object>::reference reference;
            typedef typename iterator<random_access_iterator_tag, object>::pointer pointer;

            array_iterator(const array_iterator &other);

            virtual ~array_iterator();

            array_iterator &operator=(const array_iterator &other);

            reference operator*();

            pointer operator->();

            reference operator[](const difference_type &);

            array_iterator &operator++();

            array_iterator &operator--();

            array_iterator operator++(int);

            array_iterator operator--(int);

            array_iterator operator+(difference_type n);

            array_iterator operator-(difference_type n);

            array_iterator &operator+=(difference_type n);

            array_iterator &operator-=(difference_type n);

            bool operator==(const array_iterator &other) const;

            bool operator!=(const array_iterator &other) const;

            bool operator<(const array_iterator &other) const;

            bool operator<=(const array_iterator &other) const;

            bool operator>(const array_iterator &other) const;

            bool operator>=(const array_iterator &other) const;

            friend bool operator==(
                const array_iterator &r1,
                const array_iterator &r2);

            friend bool operator!=(
                const array_iterator &r1,
                const array_iterator &r2);

            friend bool operator<(
                const array_iterator &r1,
                const array_iterator &r2);

            friend bool operator>(
                const array_iterator &r1,
                const array_iterator &r2);

            friend bool operator<=(
                const array_iterator &r1,
                const array_iterator &r2);

            friend bool operator>=(
                const array_iterator &r1,
                const array_iterator &r2);

            friend difference_type operator+(
                const array_iterator &r1,
                const array_iterator &r2);

            friend difference_type operator-(
                const array_iterator &r1,
                const array_iterator &r2);

        private:
            json_object *value_;
            long pos_;
            value_type ref_;

            void set_ref(size_t);

            array_iterator(json_object *value, long pos);
        };

        bool operator==(const array_iterator &r1, const array_iterator &r2);

        bool operator!=(const array_iterator &r1, const array_iterator &r2);

        bool operator<(const array_iterator &r1, const array_iterator &r2);

        bool operator>(const array_iterator &r1, const array_iterator &r2);

        bool operator<=(const array_iterator &r1, const array_iterator &r2);

        bool operator>=(const array_iterator &r1, const array_iterator &r2);

        array_iterator::difference_type operator+(
            const array_iterator &r1,
            const array_iterator &r2);

        array_iterator::difference_type operator-(
            const array_iterator &r1, const array_iterator &r2);
    }
}

#endif

