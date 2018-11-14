#ifndef CODA_JSON_OBJECT_H
#define CODA_JSON_OBJECT_H

#include <complex>
#include <functional>
#include <limits>
#include <string>

struct json_object;

namespace coda {
  template <class T>
  typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
  almost_equal(T x, T y, int ulp) {
    // the machine epsilon has to be scaled to the magnitude of the larger value
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x - y) <= std::numeric_limits<T>::epsilon() *
                                  std::max(std::abs(x), std::abs(y)) * ulp;
  }

  namespace json {
    class array;
    class object_iterator;

    class object {
      friend class array;

      public:
      typedef object_iterator iterator;

      object(json_object *value);
      object();
      object(std::nullptr_t null);
      object(const std::string &value);
      object(const char *value);
      object(std::istream &is);
      object(int value);
      object(long long value);
      object(double value);
      explicit object(bool value);
      object(const object &object);
      object(object &&other);
      virtual ~object();
      object &operator=(const object &obj);
      object &operator=(object &&other);

      bool is_valid() const;

      int get_int(const std::string &key) const;
      long long get_int64(const std::string &key) const;
      bool get_bool(const std::string &key) const;
      double get_double(const std::string &key) const;
      std::string get_string(const std::string &key) const;
      array get_array(const std::string &key) const;
      object get(const std::string &key) const;
      size_t size() const;

      int type() const;

      bool contains(const std::string &key) const;

      void remove(const std::string &key);

      bool parse(const std::string &value);

      void set_int(const std::string &key, int value);
      void set_int64(const std::string &key, long long value);
      void set_bool(const std::string &key, bool value);
      void set_double(const std::string &key, double value);
      void set_string(const std::string &key, const std::string &value);
      void set_array(const std::string &key, const array &value);
      void set_null(const std::string &key);
      void set(const std::string &key, const object &value);

      int to_int() const;
      long long to_int64() const;
      bool to_bool() const;
      double to_double() const;
      std::string to_string() const;
      std::string to_json_string() const;

      operator int() const;
      operator long long() const;
      operator bool() const;
      operator double() const;
      operator std::string() const;

      bool is_int() const;
      bool is_bool() const;
      bool is_double() const;
      bool is_string() const;
      bool is_object() const;
      bool is_null() const;

      iterator begin();
      iterator end();
      iterator begin() const;
      iterator end() const;

      bool operator==(const object &other) const;
      bool operator!=(const object &other) const;

      friend bool operator==(const array &val, const object &other);

      void merge(const object &other);

      protected:
      void set_value(const std::string &key, json_object *obj);
      void add_value(const std::string &key, json_object *obj);
      void foreach (
          std::function<void(const char *key, const json_object *value)> funk)
          const;

      private:
      json_object *value_;
    };

    std::ostream &operator<<(std::ostream &out, const object &other);

    bool operator==(const std::string &val, const object &other);
    bool operator==(int val, const object &other);
    bool operator==(long long val, const object &other);
    bool operator==(double val, const object &other);
    bool operator==(bool val, const object &other);

    bool operator!=(const std::string &val, const object &other);
    bool operator!=(int val, const object &other);
    bool operator!=(long long val, const object &other);
    bool operator!=(double val, const object &other);
    bool operator!=(bool val, const object &other);
  } // namespace json
} // namespace coda

#include "object_iterator.h"

#endif
