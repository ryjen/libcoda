#include "array.h"
#include "object.h"
#include "exception.h"

using namespace std;

namespace arg3
{
    namespace json
    {
        array::array() : value_(json_object_new_array()), references_(new unsigned(0))
        {

        }
        array::array(json_object *other) : value_(other), references_(NULL)
        {
            if(!json_object_is_type(value_, json_type_array))
                throw exception("object is not an array");
        }

        array::array(const array &other) : value_(other.value_), references_(other.references_)
        {
            if (references_)
            {
                (*references_)++;
            }
        }

        array::~array()
        {
            if (references_)
            {
                if (*references_ == 0)
                {
                    json_object_put(value_);
                    delete references_;
                    references_ = 0;
                }
                else
                {
                    (*references_)--;
                }
            }
        }

        array &array::operator=(const array &other)
        {
            if (this != &other)
            {
                value_ = other.value_;
                references_ = other.references_;

                if (references_)
                    (*references_)++;
            }

            return *this;
        }

        size_t array::size() const
        {
            return json_object_array_length(value_);
        }

        void array::add(const object &value)
        {
            json_object_array_add(value_, json_object_get(value.value_));
        }

        void array::addString(const string &value)
        {
            json_object_array_add(value_, json_object_new_string(value.c_str()));
        }

        void array::addInt(int32_t value)
        {
            json_object_array_add(value_, json_object_new_int(value));
        }

        void array::addInt64(int64_t value)
        {
            json_object_array_add(value_, json_object_new_int64(value));
        }

        void array::addDouble(double value)
        {
            json_object_array_add(value_, json_object_new_double(value));
        }

        void array::addBool(bool value)
        {
            json_object_array_add(value_, json_object_new_boolean(value));
        }

        void array::addArray(const array &value)
        {
            json_object_array_add(value_, json_object_get(value.value_));
        }

        int32_t array::getInt(size_t idx) const
        {
            return json_object_get_int(json_object_array_get_idx(value_, idx));
        }

        int64_t array::getInt64(size_t idx) const
        {
            return json_object_get_int64(json_object_array_get_idx(value_, idx));
        }

        string array::getString(size_t idx) const
        {
            return json_object_get_string(json_object_array_get_idx(value_, idx));
        }

        double array::getDouble(size_t idx) const
        {
            return json_object_get_double(json_object_array_get_idx(value_, idx));
        }

        array array::getArray(size_t idx) const
        {
            json_object *obj = json_object_array_get_idx(value_, idx);

            if (json_object_is_type(obj, json_type_array))
                return array(obj);
            else
                return array();
        }

        bool array::empty() const
        {
            return json_object_array_length(value_) == 0;
        }

        object array::operator[](size_t idx) const
        {
            return get(idx);
        }

        object array::get(size_t idx) const
        {
            return json_object_array_get_idx(value_, idx);
        }

        object array::front() const
        {
            return get(0);
        }

        object array::back() const
        {
            return get(size() - 1);
        }

        array::iterator array::begin() const
        {
            return iterator(value_, 0);
        }

        array::iterator array::end() const
        {
            return iterator(value_, json_object_array_length(value_));
        }

        array::reverse_iterator array::rbegin() const
        {
            return reverse_iterator(end());
        }

        array::reverse_iterator array::rend() const
        {
            return reverse_iterator(begin());
        }

        array::iterator array::begin()
        {
            return iterator(value_, 0);
        }

        array::iterator array::end()
        {
            return iterator(value_, json_object_array_length(value_));
        }

        array::reverse_iterator array::rbegin()
        {
            return reverse_iterator(end());
        }

        array::reverse_iterator array::rend()
        {
            return reverse_iterator(begin());
        }

        bool array::operator==(const array &other) const {
            return value_ == other.value_;
        }

        bool array::operator!=(const array &other) const {
            return value_ != other.value_;
        }
    }
}

