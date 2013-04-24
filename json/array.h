#ifndef ARG3_JSON_ARRAY_H_
#define ARG3_JSON_ARRAY_H_

#include <json/json.h>
#include <string>
#include "array_iterator.h"

using namespace std;

namespace arg3
{
    namespace json
    {
        class object;

        class array
        {
            friend class object;
        public:
            typedef array_iterator iterator;

            typedef reverse_iterator<iterator> reverse_iterator;

            array();
            array(const array &other);
            virtual ~array();
            array &operator=(const array &other);
            size_t size() const;
            void add(const object &value);
            void addInt(int32_t value);
            void addInt64(int64_t value);
            void addBool(bool value);
            void addDouble(double value);
            void addString(const std::string &value);
            void addArray(const array &value);
            bool empty() const;
            object operator[](size_t idx) const;
            object get(size_t idx) const;
            std::string getString(size_t idx) const;
            int32_t getInt(size_t idx) const;
            int64_t getInt64(size_t idx) const;
            bool getBool(size_t idx) const;
            double getDouble(size_t idx) const;
            array getArray(size_t idx) const;

            object front() const;
            object back() const;

            iterator begin() const;

            iterator end() const;

            reverse_iterator rbegin() const;

            reverse_iterator rend() const;

            iterator begin();

            iterator end();

            reverse_iterator rbegin();

            reverse_iterator rend();

            friend bool operator==(const array &val, const object &other);

            bool operator==(const array &other) const;
            bool operator!=(const array &other) const;

        protected:
            array(json_object *obj);
        private:
            json_object *value_;
            unsigned *references_;
        };
    }
}

#endif