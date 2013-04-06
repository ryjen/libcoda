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
            void add_int(int32_t value);
            void add_int64(int64_t value);
            void add_bool(bool value);
            void add_double(double value);
            void add_str(const std::string &value);
            void add_array(const array &value);
            bool empty() const;
            object operator[](size_t idx) const;
            object get(size_t idx) const;
            std::string get_str(size_t idx) const;
            int32_t get_int(size_t idx) const;
            int64_t get_int64(size_t idx) const;
            bool get_bool(size_t idx) const;
            double get_double(size_t idx) const;
            array get_array(size_t idx) const;

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

        protected:
            array(json_object *obj);
        private:
            json_object *value_;
            unsigned *references_;
        };
    }
}

#endif