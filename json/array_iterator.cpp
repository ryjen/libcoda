#include "array_iterator.h"
#include "object.h"

namespace arg3
{
    namespace json
    {

        array_iterator::array_iterator(const array_iterator &other) : value_(other.value_), pos_(other.pos_), ref_(json_object_array_get_idx(value_, pos_))
        {

        }


        array_iterator::array_iterator(json_object *value, long pos) : value_(value), pos_(pos), ref_(json_object_array_get_idx(value_, pos_))
        {

        }


        array_iterator::~array_iterator()
        {

        }


        array_iterator &array_iterator::operator=(const array_iterator &other)
        {
            if (this != &other)
            {
                value_ = other.value_;
                pos_ = other.pos_;
                ref_ = other.ref_;
            }
            return *this;
        }


        array_iterator::reference array_iterator::operator*()
        {

            return ref_;
        }


        array_iterator::pointer array_iterator::operator->()
        {
            return &ref_;
        }


        array_iterator::reference array_iterator::operator[](const difference_type &idx)
        {
            return ref_;
        }

        void array_iterator::set_ref(size_t pos)
        {
            ref_ = object(json_object_array_get_idx(value_, pos));
        }

        array_iterator &array_iterator::operator++()
        {
            set_ref(++pos_);
            return *this;
        }


        array_iterator &array_iterator::operator--()
        {
            set_ref(--pos_);
            return *this;
        }


        array_iterator array_iterator::operator++(int)
        {
            array_iterator temp(*this);
            set_ref(++pos_);
            return temp;
        }


        array_iterator array_iterator::operator--(int)
        {
            array_iterator temp(*this);
            set_ref(--pos_);
            return temp;
        }


        array_iterator array_iterator::operator+(difference_type n)
        {
            array_iterator temp(*this);
            temp.pos_ += n;
            temp.set_ref(temp.pos_);
            return temp;
        }


        array_iterator array_iterator::operator-(difference_type n)
        {
            array_iterator temp(*this);
            temp.pos_ -= n;
            temp.set_ref(temp.pos_);
            return temp;
        }


        array_iterator &array_iterator::operator+=(difference_type n)
        {
            pos_ += n;
            set_ref(pos_);
            return *this;
        }


        array_iterator &array_iterator::operator-=(difference_type n)
        {
            pos_ -= n;
            set_ref(pos_);
            return *this;
        }


        bool array_iterator::operator==(const array_iterator &other) const
        {
            return pos_ == other.pos_ && json_object_array_length(value_) == json_object_array_length(other.value_);
        }


        bool array_iterator::operator!=(const array_iterator &other) const
        {

            return !(operator==(other));
        }


        bool array_iterator::operator<(const array_iterator &other) const
        {

            return pos_ < other.pos_;
        }


        bool array_iterator::operator<=(const array_iterator &other) const
        {
            return pos_ <= other.pos_;
        }


        bool array_iterator::operator>(const array_iterator &other) const
        {
            return pos_ > other.pos_;
        }


        bool array_iterator::operator>=(const array_iterator &other) const
        {
            return pos_ >= other.pos_;
        }


        bool operator==(const array_iterator &r1, const array_iterator &r2)
        {
            return r1.operator == (r2);
        }


        bool operator!=(const array_iterator &r1, const array_iterator &r2)
        {
            return r1.operator != (r2);
        }


        bool operator<(const array_iterator &r1, const array_iterator &r2)
        {
            return r1.operator < (r2);
        }


        bool operator>(const array_iterator &r1, const array_iterator &r2)
        {
            return r1.operator > (r2);
        }


        bool operator<=(const array_iterator &r1, const array_iterator &r2)
        {
            return r1.operator <= (r2);
        }


        bool operator>=(const array_iterator &r1, const array_iterator &r2)
        {
            return r1.operator >= (r2);
        }


        array_iterator::difference_type operator+(
            const array_iterator &r1,
            const array_iterator &r2)
        {

            return r1.pos_ + r2.pos_;
        }


        array_iterator::difference_type operator-(
            const array_iterator &r1, const array_iterator &r2)
        {
            return r1.pos_ - r2.pos_;
        }

    }
}