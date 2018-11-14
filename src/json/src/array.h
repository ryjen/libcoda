#ifndef CODA_JSON_ARRAY_H
#define CODA_JSON_ARRAY_H

#include "array_iterator.h"
#include <string>

using namespace std;

namespace coda {
  namespace json {
    class object;

    class array {
      friend class object;

      public:
      typedef array_iterator iterator;

      typedef std::reverse_iterator<iterator> reverse_iterator;

      array();
      array(const array &other);
      array(array &&other);
      virtual ~array();
      array &operator=(const array &other);
      array &operator=(array &&other);
      size_t size() const;
      void add(const object &value);
      void add(size_t index, const object &value);
      void add_int(int value);
      void add_int(size_t index, int value);
      void add_int64(long long value);
      void add_int64(size_t index, long long value);
      void add_bool(bool value);
      void add_bool(size_t index, bool value);
      void add_double(double value);
      void add_double(size_t index, double value);
      void add_string(const std::string &value);
      void add_string(size_t index, const std::string &value);
      void add_array(const array &value);
      void add_array(size_t index, const array &value);
      bool empty() const;
      object operator[](size_t idx) const;
      object get(size_t idx) const;
      std::string get_string(size_t idx) const;
      int get_int(size_t idx) const;
      int64_t get_int64(size_t idx) const;
      bool get_bool(size_t idx) const;
      double get_double(size_t idx) const;
      array get_array(size_t idx) const;

      bool is_valid() const;

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
    };
  } // namespace json
} // namespace coda

#endif
