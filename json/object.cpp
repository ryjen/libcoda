#include "object.h"
#include "array.h"
#include "object_iterator.h"
#include "../math/util.h"
#include <sstream>

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

        object::object(istream &in) : value_(NULL), references_(NULL)
        {
            std::ostringstream os;
            in>>os.rdbuf();

            value_ = json_tokener_parse(os.str().c_str());
            references_ = new unsigned(0);
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

        object::object(object &&other) : value_(other.value_), references_(other.references_)
        {
            other.value_ = NULL;
            other.references_ = NULL;
        }

        object::~object()
        {
            if (references_)
            {
                if (*references_ == 0)
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
            if (this != &obj)
            {
                value_ = obj.value_;

                references_ = obj.references_;

                if (references_)
                    (*references_)++;
            }
            return *this;
        }

        object &object::operator=(object &&obj)
        {
            if (this != &obj)
            {
                value_ = obj.value_;

                references_ = obj.references_;

                obj.value_ = NULL;
                obj.references_ = NULL;
            }
            return *this;
        }

        bool object::parse(const string &value)
        {
            json_object *obj = json_tokener_parse(value.c_str());

            if (obj != NULL)
            {
                if (value_ != NULL)
                    json_object_put(value_);

                value_ = obj;
            }

            return obj != NULL;
        }

        bool object::contains(const string &key) const
        {
            return json_object_object_get_ex(value_, key.c_str(), NULL);
        }

        object object::remove(const string &key)
        {
            json_object *obj = json_object_get(json_object_object_get(value_, key.c_str()));
            json_object_object_del(value_, key.c_str());
            return object(obj);
        }

        int32_t object::getInt(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return json_object_get_int(obj);
        }

        int64_t object::getInt64(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return json_object_get_int64(obj);
        }
        bool object::getBool(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return json_object_get_boolean(obj);
        }

        double object::getDouble(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return json_object_get_double(obj);
        }

        std::string object::getString(const std::string &key) const
        {
            json_object *obj = json_object_object_get(value_, key.c_str());
            return json_object_get_string(obj);
        }

        array object::getArray(const std::string &key) const
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
            if (!isArray()) return object();

            json_object *obj = json_object_array_get_idx(value_, idx);

            return object(obj);
        }

        size_t object::size() const
        {
            if (isArray())
                return json_object_array_length(value_);

            if (isObject())
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
            if (contains(key))
                remove(key);

            json_object_object_add(value_, key.c_str(), obj);
        }

        void object::setInt(const std::string &key, int32_t value)
        {
            set_value(key, json_object_new_int(value));
        }

        void object::setInt64(const std::string &key, int64_t value)
        {
            set_value(key, json_object_new_int64(value));
        }
        void object::setBool(const std::string &key, bool value)
        {
            set_value(key, json_object_new_boolean(value));
        }
        void object::setDouble(const std::string &key, double value)
        {
            set_value(key, json_object_new_double(value));
        }
        void object::setString(const std::string &key, const std::string &value)
        {
            set_value(key, json_object_new_string(value.c_str()));
        }

        void object::setArray(const std::string &key, const array &value)
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

        void object::addInt(const std::string &key, int32_t value)
        {
            add_value(key, json_object_new_int(value));
        }

        void object::addInt64(const std::string &key, int64_t value)
        {
            add_value(key, json_object_new_int64(value));
        }
        void object::addBool(const std::string &key, bool value)
        {
            add_value(key, json_object_new_boolean(value));
        }
        void object::addDouble(const std::string &key, double value)
        {
            add_value(key, json_object_new_double(value));
        }
        void object::addString(const std::string &key, const std::string &value)
        {
            add_value(key, json_object_new_string(value.c_str()));
        }

        void object::addArray(const std::string &key, const array &value)
        {
            add_value(key, json_object_get(value.value_));
        }

        void object::add(const std::string &key, const object &value)
        {
            add_value(key, json_object_get(value.value_));
        }


        bool object::isInt() const
        {
            return json_object_is_type(value_, json_type_int);
        }

        bool object::isBool() const
        {
            return json_object_is_type(value_, json_type_boolean);
        }

        bool object::isDouble() const
        {
            return json_object_is_type(value_, json_type_double);
        }

        bool object::isString() const
        {
            return json_object_is_type(value_, json_type_string);
        }

        bool object::isArray() const
        {
            return json_object_is_type(value_, json_type_array);
        }

        bool object::isObject() const
        {
            return json_object_is_type(value_, json_type_object);
        }

        bool object::isNull() const
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

        int32_t object::toInt() const
        {
            return json_object_get_int(value_);
        }

        int64_t object::toInt64() const
        {
            return json_object_get_int64(value_);
        }

        bool object::toBool() const
        {
            return json_object_get_boolean(value_);
        }

        double object::toDouble() const
        {
            return json_object_get_double(value_);
        }

        string object::toString() const
        {
            return json_object_get_string(value_);
        }

        array object::toArray() const
        {
            if (isArray())
                return array(value_);
            else
                return array();
        }

        json_type object::type() const
        {
            return json_object_get_type(value_);
        }

        object::operator string() const
        {
            return toString();
        }

        bool object::operator==(const object &other) const
        {
            switch (type())
            {
            case json_type_null:
                return false;
            case json_type_int:
                return toInt64() == other.toInt64();
            case json_type_string:
                return toString() == other.toString();
            case json_type_double:
                return almost_equal(toDouble(), other.toDouble(), 8);
            case json_type_boolean:
                return toBool() == other.toBool();
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
            return other.toString() == val;
        }

        bool operator==(int32_t val, const object &other)
        {
            return other.toInt() == val;
        }
        bool operator==(int64_t val, const object &other)
        {
            return other.toInt64() == val;
        }

        bool operator==(double val, const object &other)
        {
            return almost_equal(other.toDouble(), val, 8);
        }

        bool operator==(bool val, const object &other)
        {
            return other.toBool() == val;
        }
        bool operator==(const array &val, const object &other)
        {
            return other.value_ == val.value_;
        }

    }
}
