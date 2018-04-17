#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <json_object.h>
#include <cassert>

#include "array.h"
#include "exception.h"
#include "object.h"

using namespace std;

namespace coda
{
    namespace json
    {
        array::array() : value_(json_object_new_array())
        {
        }
        array::array(json_object *other) : value_(NULL)
        {
            if (other == NULL || !json_object_is_type(other, json_type_array)) {
                throw invalid_argument("object is not an array");
            }

            value_ = json_object_get(other);
        }

        array::array(const array &other) : value_(NULL)
        {
            if (other.value_ != NULL) {
                value_ = json_object_get(other.value_);
            }
        }

        array::array(array &&other) : value_(other.value_)
        {
            other.value_ = NULL;
        }

        array::~array()
        {
            if (value_ != NULL) {
                json_object_put(value_);
                value_ = NULL;
            }
        }

        array &array::operator=(const array &other)
        {
            if (value_ != NULL) {
                json_object_put(value_);
            }
            value_ = json_object_get(other.value_);

            return *this;
        }

        array &array::operator=(array &&other)
        {
            if (value_ != NULL) {
                json_object_put(value_);
            }
            value_ = other.value_;

            other.value_ = NULL;
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
        void array::add(size_t index, const object &value)
        {
            json_object_array_put_idx(value_, index, json_object_get(value.value_));
        }
        void array::add_string(const string &value)
        {
            json_object_array_add(value_, json_object_new_string(value.c_str()));
        }
        void array::add_string(size_t i, const string &value)
        {
            json_object_array_put_idx(value_, i, json_object_new_string(value.c_str()));
        }
        void array::add_int(int value)
        {
            json_object *obj = json_object_new_int(value);
            json_object_array_add(value_, obj);
        }
        void array::add_int(size_t i, int value)
        {
            json_object *obj = json_object_new_int(value);
            json_object_array_put_idx(value_, i, obj);
        }
        void array::add_int64(long long value)
        {
#ifdef JSON_C_EXTENDED
            json_object *obj = json_object_new_int64(value);
            json_object_array_add(value_, obj);
#else
            throw not_implemented_exception();
#endif
        }
        void array::add_int64(size_t i, long long value)
        {
#ifdef JSON_C_EXTENDED
            json_object *obj = json_object_new_int64(value);
            json_object_array_put_idx(value_, i, obj);
#else
            throw not_implemented_exception();
#endif
        }
        void array::add_double(double value)
        {
            json_object *obj = json_object_new_double(value);
            json_object_array_add(value_, obj);
        }
        void array::add_double(size_t i, double value)
        {
            json_object *obj = json_object_new_double(value);
            json_object_array_put_idx(value_, i, obj);
        }

        void array::add_bool(bool value)
        {
            json_object *obj = json_object_new_boolean(value);
            json_object_array_add(value_, obj);
        }
        void array::add_bool(size_t i, bool value)
        {
            json_object *obj = json_object_new_boolean(value);
            json_object_array_put_idx(value_, i, obj);
        }

        void array::add_array(const array &value)
        {
            json_object_array_add(value_, json_object_get(value.value_));
        }
        void array::add_array(size_t i, const array &value)
        {
            json_object_array_put_idx(value_, i, json_object_get(value.value_));
        }

        int32_t array::get_int(size_t idx) const
        {
            if (idx >= size()) {
                throw std::out_of_range("bad index for coda::json::array::get_int");
            }
            return json_object_get_int(json_object_array_get_idx(value_, idx));
        }
        int64_t array::get_int64(size_t idx) const
        {
            if (idx >= size()) {
                throw std::out_of_range("bad index for coda::json::array::get_int64");
            }
#ifdef JSON_C_EXTENDED
            return json_object_get_int64(json_object_array_get_idx(value_, idx));
#else
            throw not_implemented_exception();
#endif
        }
        string array::get_string(size_t idx) const
        {
            const char *temp = NULL;

            if (idx >= size()) {
                throw std::out_of_range("bad index for coda::json::array::get_string");
            }
            temp = json_object_get_string(json_object_array_get_idx(value_, idx));

            if (temp == NULL) {
                return string();
            }

            return temp;
        }

        bool array::get_bool(size_t idx) const
        {
            if (idx >= size()) {
                throw std::out_of_range("bad index for coda::json::array::get_bool");
            }

            return json_object_get_boolean(json_object_array_get_idx(value_, idx));
        }
        double array::get_double(size_t idx) const
        {
            if (idx >= size()) {
                throw std::out_of_range("bad index for coda::json::array::get_double");
            }
            return json_object_get_double(json_object_array_get_idx(value_, idx));
        }

        array array::get_array(size_t idx) const
        {
            json_object *obj = NULL;

            if (idx >= size()) {
                throw std::out_of_range("bad index for coda::json::array::get_array");
            }
            obj = json_object_array_get_idx(value_, idx);

            return array(obj);
        }

        bool array::empty() const
        {
            assert(value_ != NULL);

            return json_object_array_length(value_) == 0;
        }

        object array::operator[](size_t idx) const
        {
            return get(idx);
        }

        object array::get(size_t idx) const
        {
            if (idx >= size()) {
                throw std::out_of_range("bad index for coda::json::array");
            }
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

        bool array::operator==(const array &other) const
        {
            return value_ == other.value_;
        }

        bool array::operator!=(const array &other) const
        {
            return value_ != other.value_;
        }

        bool array::is_valid() const
        {
            return value_ != NULL;
        }
    }
}
