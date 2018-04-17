#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <json_object.h>
#include <json_tokener.h>
#include <linkhash.h>
#include <complex>
#include <sstream>
#include "array.h"
#include "exception.h"
#include "object.h"
#include "object_iterator.h"

using namespace std;

namespace coda
{
    namespace json
    {
        object::object() : value_(json_object_new_object())
        {
        }
        object::object(json_object *obj) : value_(NULL)
        {
            if (obj != NULL) {
                if (json_object_is_type(obj, json_type_array)) {
                    throw exception("object is an array");
                }

                value_ = json_object_get(obj);
            }
        }

        object::object(nullptr_t value) : value_(NULL)
        {
        }

        object::object(const string &value) : value_(json_object_new_string(value.c_str()))
        {
        }
        object::object(const char *value) : value_(json_object_new_string(value))
        {
        }
        object::object(istream &in) : value_(NULL)
        {
            std::ostringstream os;
            in >> os.rdbuf();

            value_ = json_tokener_parse(os.str().c_str());
        }
        object::object(long long value)

        {
#ifdef JSON_C_EXTENDED
            value_ = json_object_new_int64(value);
#else
            throw not_implemented_exception();
#endif
        }

        object::object(int value) : value_(json_object_new_int(value))
        {
        }
        object::object(bool value) : value_(json_object_new_boolean(value))
        {
        }
        object::object(double value) : value_(json_object_new_double(value))
        {
        }
        object::object(const object &value) : value_(NULL)
        {
            if (value.value_ != NULL) {
                value_ = json_object_get(value.value_);
            }
        }
        object::object(object &&other) : value_(other.value_)
        {
            other.value_ = NULL;
        }
        object::~object()
        {
            if (value_ != NULL) {
                json_object_put(value_);  // release object

                value_ = NULL;
            }
        }

        object &object::operator=(const object &obj)
        {
            if (obj.value_ != NULL) {
                if (value_ != NULL) {
                    json_object_put(value_);
                }
                value_ = json_object_get(obj.value_);
            }

            return *this;
        }

        object &object::operator=(object &&obj)
        {
            if (value_ != NULL) {
                json_object_put(value_);
            }
            value_ = obj.value_;

            obj.value_ = NULL;

            return *this;
        }

        bool object::parse(const string &value)
        {
            json_object *obj = json_tokener_parse(value.c_str());

            if (obj != NULL) {
                if (value_ != NULL) {
                    json_object_put(value_);
                }
                value_ = obj;
            }

            return obj != NULL;
        }

        bool object::contains(const string &key) const
        {
#ifdef JSON_C_EXTENDED
            return json_object_object_get_ex(value_, key.c_str(), NULL);
#else
            return json_object_object_get(value_, key.c_str()) != NULL;
#endif
        }

        void object::remove(const string &key)
        {
            json_object_object_del(value_, key.c_str());
        }

        int object::get_int(const std::string &key) const
        {
            json_object *obj;
#ifdef JSON_C_EXTENDED
            if (!json_object_object_get_ex(value_, key.c_str(), &obj)) throw exception("key does not exist");
#else
            obj = json_object_object_get(value_, key.c_str());
#endif
            return json_object_get_int(obj);
        }
        long long object::get_int64(const std::string &key) const
        {
#ifdef JSON_C_EXTENDED
            json_object *obj;
            if (!json_object_object_get_ex(value_, key.c_str(), &obj)) throw exception("key does not exist");
            long long value = json_object_get_int64(obj);
            return value;
#else
            throw not_implemented_exception();
#endif
        }
        bool object::get_bool(const std::string &key) const
        {
            json_object *obj;
#ifdef JSON_C_EXTENDED
            if (!json_object_object_get_ex(value_, key.c_str(), &obj)) throw exception("key does not exist");
#else
            obj = json_object_object_get(value_, key.c_str());
#endif
            return json_object_get_boolean(obj);
        }

        double object::get_double(const std::string &key) const
        {
            json_object *obj;
#ifdef JSON_C_EXTENDED
            if (!json_object_object_get_ex(value_, key.c_str(), &obj)) throw exception("key does not exist");
#else
            obj = json_object_object_get(value_, key.c_str());
#endif
            return json_object_get_double(obj);
        }

        std::string object::get_string(const std::string &key) const
        {
            json_object *obj;
#ifdef JSON_C_EXTENDED
            if (!json_object_object_get_ex(value_, key.c_str(), &obj)) throw exception("key does not exist");
#else
            obj = json_object_object_get(value_, key.c_str());
#endif
            const char *value = json_object_get_string(obj);
            return value == NULL ? "" : value;
        }

        array object::get_array(const std::string &key) const
        {
            json_object *obj;
#ifdef JSON_C_EXTENDED
            if (!json_object_object_get_ex(value_, key.c_str(), &obj)) throw exception("key does not exist");
#else
            obj = json_object_object_get(value_, key.c_str());
#endif
            return array(obj);
        }

        object object::get(const std::string &key) const
        {
            json_object *obj;
#ifdef JSON_C_EXTENDED
            if (!json_object_object_get_ex(value_, key.c_str(), &obj)) throw exception("key does not exist");
#else
            obj = json_object_object_get(value_, key.c_str());
#endif
            if (obj != NULL && json_object_is_type(obj, json_type_array)) throw exception("object is an array");

            return object(obj);
        }

        bool object::is_valid() const
        {
            return value_ != NULL;
        }
        void object::foreach (std::function<void(const char *key, const json_object *value)> funk) const
        {
            for (struct lh_entry *entry = json_object_get_object(value_)->head; entry; entry = entry->next) {
                const char *key = static_cast<const char *>(entry->k);
                const json_object *val = static_cast<const json_object *>(entry->v);

                funk(key, val);
            }
        }

        void object::merge(const object &other)
        {
            for (struct lh_entry *entry = json_object_get_object(other.value_)->head; entry; entry = entry->next) {
                const char *key = static_cast<const char *>(entry->k);
                json_object *val = static_cast<json_object *>(const_cast<void *>(entry->v));

                if (contains(key)) {
                    get(key).merge(object(val));
                } else {
                    set_value(key, val);
                }
            }
        }

        size_t object::size() const
        {
            if (is_object()) {
                size_t iCount = 0;

                foreach ([&iCount](const char *key, const json_object *value) { iCount++; })
                    ;

                return iCount;
            }

            return 0;
        }

        void object::set_value(const string &key, json_object *obj)
        {
            if (contains(key)) remove(key);

            json_object_object_add(value_, key.c_str(), obj);
        }

        void object::set_int(const std::string &key, int value)
        {
            json_object *obj = json_object_new_int(value);
            set_value(key, obj);
        }
        void object::set_int64(const std::string &key, long long value)
        {
#ifdef JSON_C_EXTENDED
            json_object *obj = json_object_new_int64(value);
            set_value(key, obj);
#else
            throw not_implemented_exception();
#endif
        }
        void object::set_bool(const std::string &key, bool value)
        {
            json_object *obj = json_object_new_boolean(value);
            set_value(key, obj);
        }
        void object::set_double(const std::string &key, double value)
        {
            json_object *obj = json_object_new_double(value);
            set_value(key, obj);
        }
        void object::set_string(const std::string &key, const std::string &value)
        {
            json_object *str = json_object_new_string(value.c_str());
            set_value(key, str);
        }

        void object::set_array(const std::string &key, const array &value)
        {
            set_value(key, json_object_get(value.value_));
        }

        void object::set_null(const std::string &key)
        {
            set_value(key, NULL);
        }
        void object::set(const std::string &key, const object &value)
        {
            set_value(key, json_object_get(value.value_));
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
        bool object::is_string() const
        {
            return json_object_is_type(value_, json_type_string);
        }
        bool object::is_object() const
        {
            return json_object_is_type(value_, json_type_object);
        }
        bool object::is_null() const
        {
            if (value_ == NULL) return true;

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
        int object::to_int() const
        {
            return json_object_get_int(value_);
        }
        long long object::to_int64() const
        {
#ifdef JSON_C_EXTENDED
            return json_object_get_int64(value_);
#else
            throw not_implemented_exception();
#endif
        }
        bool object::to_bool() const
        {
            return json_object_get_boolean(value_);
        }
        double object::to_double() const
        {
            return json_object_get_double(value_);
        }
        string object::to_string() const
        {
            const char *temp = json_object_get_string(value_);

            return temp == NULL ? "" : temp;
        }

        string object::to_json_string() const
        {
            const char *temp = json_object_to_json_string(value_);

            return temp == NULL ? "" : temp;
        }

        object::operator int() const
        {
            return to_int();
        }
        object::operator long long() const
        {
            return to_int64();
        }
        object::operator bool() const
        {
            return to_bool();
        }
        object::operator double() const
        {
            return to_double();
        }
        int object::type() const
        {
            if (value_ == NULL) return json_type_null;

            return json_object_get_type(value_);
        }

        object::operator string() const
        {
            return to_string();
        }
        bool object::operator==(const object &other) const
        {
            switch (type()) {
                case json_type_null:
                default:
                    return false;
                case json_type_int:
#ifdef JSON_C_EXTENDED
                    return to_int64() == other.to_int64();
#else
                    return to_int() == other.to_int();
#endif
                case json_type_string:
                    return to_string() == other.to_string();
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
        ostream &operator<<(ostream &out, const object &obj)
        {
            out << obj.to_string();
            return out;
        }

        bool operator==(const std::string &val, const object &other)
        {
            return other.to_string() == val;
        }
        bool operator==(int val, const object &other)
        {
            return other.to_int() == val;
        }
        bool operator==(long long val, const object &other)
        {
#ifdef JSON_C_EXTENDED
            return other.to_int64() == val;
#else
            throw not_implemented_exception();
#endif
        }
        bool operator==(double val, const object &other)
        {
            return almost_equal(other.to_double(), val, 8);
        }
        bool operator==(bool val, const object &other)
        {
            return other.to_bool() == val;
        }
        bool operator!=(const std::string &val, const object &other)
        {
            return !operator==(val, other);
        }
        bool operator!=(int val, const object &other)
        {
            return !operator==(val, other);
        }
        bool operator!=(long long val, const object &other)
        {
#ifdef JSON_C_EXTENDED
            return !operator==(val, other);
#else
            throw not_implemented_exception();
#endif
        }
        bool operator!=(double val, const object &other)
        {
            return !operator==(val, other);
        }
        bool operator!=(bool val, const object &other)
        {
            return !operator==(val, other);
        }
    }
}
