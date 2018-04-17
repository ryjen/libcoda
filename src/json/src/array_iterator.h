#ifndef CODA_JSON_ARRAY_ITERATOR_H
#define CODA_JSON_ARRAY_ITERATOR_H

#include <iterator>
#include <string>
#include "object.h"

using namespace std;

struct json_object;

namespace coda
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

            array_iterator(array_iterator &&other);

            virtual ~array_iterator();

            array_iterator &operator=(const array_iterator &other);

            array_iterator &operator=(array_iterator &&other);

            value_type operator*() const;
            reference operator*();

            pointer operator->();

            value_type operator[](const difference_type &) const;

            array_iterator &operator++();

            array_iterator &operator--();

            array_iterator operator++(int);

            array_iterator operator--(int);

            array_iterator operator+(difference_type n) const;

            array_iterator operator-(difference_type n) const;

            array_iterator &operator+=(difference_type n);

            array_iterator &operator-=(difference_type n);

            bool operator==(const array_iterator &other) const;

            bool operator!=(const array_iterator &other) const;

            bool operator<(const array_iterator &other) const;

            bool operator<=(const array_iterator &other) const;

            bool operator>(const array_iterator &other) const;

            bool operator>=(const array_iterator &other) const;

           private:
            json_object *value_;
            long pos_;
            value_type ref_;

            void set_ref(size_t);

            array_iterator(json_object *value, long pos);
        };
    }
}

#endif
