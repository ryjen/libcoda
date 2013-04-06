#ifndef ARG3_JSON_OBJECT_H_
#define ARG3_JSON_OBJECT_H_

#include <json/json.h>
#include <string>

namespace arg3
{
    namespace json
    {
        class array;
        class object_iterator;

        class object
        {
            friend class array;
        public:
            typedef object_iterator iterator;

            object(json_object *value);
            object();
            object(const std::string &value);
            object(int32_t value);
            object(int64_t value);
            object(double value);
            object(bool value);
            object(const object &object);
            virtual ~object();
            object &operator=(const object &obj);

            int32_t getInt(const std::string &key) const;
            int64_t getInt64(const std::string &key) const;
            bool getBool(const std::string &key) const;
            double getDouble(const std::string &key) const;
            std::string getString(const std::string &key) const;
            array getArray(const std::string &key) const;
            object get(const std::string &key) const;

            object get(size_t idx) const;
            size_t size() const;

            json_type type() const;

            bool contains(const std::string &key) const;

            void remove(const std::string &key);

            bool parse(const std::string &value);

            void setInt(const std::string &key, int32_t value);
            void setInt64(const std::string &key, int64_t value);
            void setBool(const std::string &key, bool value);
            void setDouble(const std::string &key, double value);
            void setString(const std::string &key, const std::string &value);
            void setArray(const std::string &key, const array &value);
            void set(const std::string &key, const object &value);

            void addInt(const std::string &key, int32_t value);
            void addInt64(const std::string &key, int64_t value);
            void addBool(const std::string &key, bool value);
            void addDouble(const std::string &key, double value);
            void addString(const std::string &key, const std::string &value);
            void addArray(const std::string &key, const array &value);
            void add(const std::string &key, const object &value);

            int32_t toInt() const;
            int64_t toInt64() const;
            bool toBool() const;
            double toDouble() const;
            std::string toString() const;
            array toArray() const;

            bool isInt() const;
            bool isBool() const;
            bool isDouble() const;
            bool isString() const;
            bool isArray() const;
            bool isObject() const;
            bool isNull() const;

            iterator begin();
            iterator end();
            iterator begin() const;
            iterator end() const;

            bool operator==(const object &other) const;
            bool operator!=(const object &other) const;

            friend bool operator==(const array &val, const object &other);
        protected:
            void set_value(const std::string &key, json_object *obj);
            void add_value(const std::string &key, json_object *obj);
        private:
            json_object *value_;
            unsigned *references_;
        };

        bool operator==(const std::string &val, const object &other);
        bool operator==(int32_t val, const object &other);
        bool operator==(int64_t val, const object &other);
        bool operator==(double val, const object &other);
        bool operator==(bool val, const object &other);
        bool operator==(const array &val, const object &other);
    }
}

#include "object_iterator.h"

#endif
