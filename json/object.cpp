#include "object.h"
#include "array.h"
#include "object_iterator.h"
#include "../math/util.h"

using namespace std;

namespace arg3
{
    namespace json
    {
        object::object() : value_(json_object_new_object()), references_(new unsigned(0))
        {
        }

        object::object(json_object *obj) : value_(obj), references_(NULL)
        {

        }

        object::object(const string &value) : value_(json_object_new_string(value.c_str())), references_(new unsigned(0))
        {

        }

        object::object(int64_t value) : value_(json_object_new_int64(value)), references_(new unsigned(0))
        {

        }

        object::object(int32_t value) : value_(json_object_new_int(value)), references_(new unsigned(0))
        {

        }

        object::object(bool value) : value_(json_object_new_boolean(value)), references_(new unsigned(0))
        {

        }

        object::object(double value) : value_(json_object_new_double(value)), references_(new unsigned(0))
        {

        }

        object::object(const object &value) : value_(value.value_), references_(value.references_)
        {
            if(references_)
                (*references_)++;
        }

        object::~object()
        {
            if(references_)
            {
                if(*references_ == 0)
                {
                    json_object_put(value_);

                    delete references_;

                    value_ = NULL;

                    references_ = NULL;
                }
                else
                {
                    (*references_)--;
                }
            }
        }

        object &object::operator=(const object &obj)
        {
            if(this != &obj)
            {
                value_ = obj.value_;

                references_ = obj.references_;

                if(references_)
                    (*references_)++;
            }
            return *this;
        }

        bool object::parse(const string &value)
        {
            json_object *obj = json_tokener_parse(value.c_str());

            if(obj != NULL)
            {
                if(value_ != NULL)
                    json_object_put(value_);

                value_ = obj;
            }

            return obj != NULL;
        }

        bool object::contains(const string &key) const
        {
            return json_object_object_get_ex(value_, key.c_str(), NULL);
        }

        void object::remove(const string &key)
        {
            json_object_object_del(value_, key.c_str());
        }

        int32_t object::get_int(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return json_object_get_int(obj);
        }

        int64_t object::get_int64(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return json_object_get_int64(obj);
        }
        bool object::get_bool(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return json_object_get_boolean(obj);
        }

        double object::get_double(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return json_object_get_double(obj);
        }

        std::string object::get_str(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return json_object_get_string(obj);
        }

        array object::get_array(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return array(obj);
        }

        object object::get(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return object(obj);
        }

        object object::get(size_t idx) const
        {
            if(!is_array()) return object();

            json_object *obj = json_object_array_get_idx(value_, idx);

            return object(obj);
        }

        size_t object::size() const
        {
            if(is_array())
                return json_object_array_length(value_);

            if(is_obj())
            {
                size_t iCount = 0;

                json_object_object_foreach(value_, key, val)
                {
                    iCount++;
                }

                return iCount;
            }

            return 0;
        }

        void object::set_value(const string &key, json_object *obj)
        {
            if(contains(key))
                remove(key);

            json_object_object_add(value_, key.c_str(), obj);
        }

        void object::set_int(const std::string &key, int32_t value)
        {
            set_value(key, json_object_new_int(value));
        }

        void object::set_int64(const std::string &key, int64_t value)
        {
            set_value(key, json_object_new_int64(value));
        }
        void object::set_bool(const std::string &key, bool value)
        {
            set_value(key, json_object_new_boolean(value));
        }
        void object::set_double(const std::string &key, double value)
        {
            set_value(key, json_object_new_double(value));
        }
        void object::set_str(const std::string &key, const std::string &value)
        {
            set_value(key, json_object_new_string(value.c_str()));
        }

        void object::set_array(const std::string &key, const array &value)
        {
            set_value(key, json_object_get(value.value_));
        }

        void object::set(const std::string &key, const object &value)
        {
            set_value(key, json_object_get(value.value_));
        }



        void object::add_value(const string &key, json_object *obj)
        {
            json_object_object_add(value_, key.c_str(), obj);
        }

        void object::add_int(const std::string &key, int32_t value)
        {
            add_value(key, json_object_new_int(value));
        }

        void object::add_int64(const std::string &key, int64_t value)
        {
            add_value(key, json_object_new_int64(value));
        }
        void object::add_bool(const std::string &key, bool value)
        {
            add_value(key, json_object_new_boolean(value));
        }
        void object::add_double(const std::string &key, double value)
        {
            add_value(key, json_object_new_double(value));
        }
        void object::add_str(const std::string &key, const std::string &value)
        {
            add_value(key, json_object_new_string(value.c_str()));
        }

        void object::add_array(const std::string &key, const array &value)
        {
            add_value(key, json_object_get(value.value_));
        }

        void object::add(const std::string &key, const object &value)
        {
            add_value(key, json_object_get(value.value_));
        }


        bool object::is_int() const
        {
            return json_object_is_type(value_, json_type_int);
        }

        bool object::is_bool() const
        {
            return json_object_is_type(value_, json_type_boolean);
        }

        bool object::is_double() const
        {
            return json_object_is_type(value_, json_type_double);
        }

        bool object::is_str() const
        {
            return json_object_is_type(value_, json_type_string);
        }

        bool object::is_array() const
        {
            return json_object_is_type(value_, json_type_array);
        }

        bool object::is_obj() const
        {
            return json_object_is_type(value_, json_type_object);
        }

        bool object::is_null() const
        {
            return json_object_is_type(value_, json_type_null);
        }

        object::iterator object::begin()
        {
            return object_iterator(json_object_get_object(value_)->head);
        }

        object_iterator object::end()
        {
            return object_iterator(NULL);
        }

        object_iterator object::begin() const
        {
            return object_iterator(json_object_get_object(value_)->head);
        }

        object_iterator object::end() const
        {
            return object_iterator(NULL);
        }

        int32_t object::to_int() const
        {
            return json_object_get_int(value_);
        }

        int64_t object::to_int64() const
        {
            return json_object_get_int64(value_);
        }

        bool object::to_bool() const
        {
            return json_object_get_boolean(value_);
        }

        double object::to_double() const
        {
            return json_object_get_double(value_);
        }

        string object::to_str() const
        {
            return json_object_get_string(value_);
        }

        array object::to_array() const
        {
            if(is_array())
                return array(value_);
            else
                return array();
        }

        json_type object::type() const
        {
            return json_object_get_type(value_);
        }

        bool object::operator==(const object &other) const
        {
            switch(type())
            {
            case json_type_null:
                return false;
            case json_type_int:
                return to_int64() == other.to_int64();
            case json_type_string:
                return to_str() == other.to_str();
            case json_type_double:
                return almost_equal(to_double(), other.to_double(), 8);
            case json_type_boolean:
                return to_bool() == other.to_bool();
            case json_type_object:
            case json_type_array:
                return value_ == other.value_;
            }
        }

        bool object::operator!=(const object &other) const
        {
            return !operator==(other);
        }



        bool operator==(const std::string &val, const object &other)
        {
            return other.to_str() == val;
        }

        bool operator==(int32_t val, const object &other)
        {
            return other.to_int() == val;
        }
        bool operator==(int64_t val, const object &other)
        {
            return other.to_int64() == val;
        }

        bool operator==(double val, const object &other)
        {
            return almost_equal(other.to_double(), val, 8);
        }

        bool operator==(bool val, const object &other)
        {
            return other.to_bool() == val;
        }
        bool operator==(const array &val, const object &other)
        {
            return other.value_ == val.value_;
        }

    }
}
