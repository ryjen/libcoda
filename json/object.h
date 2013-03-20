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

			int32_t get_int(const std::string &key) const;
			int64_t get_int64(const std::string &key) const;
			bool get_bool(const std::string &key) const;
			double get_double(const std::string &key) const;
			std::string get_str(const std::string &key) const;
			array get_array(const std::string &key) const;
			object get(const std::string &key) const;

			object get(size_t idx) const;
			size_t size() const;

			json_type type() const;

			bool contains(const std::string &key) const;

			void remove(const std::string &key);

			bool parse(const std::string &value);

			void set_int(const std::string &key, int32_t value);
			void set_int64(const std::string &key, int64_t value);
			void set_bool(const std::string &key, bool value);
			void set_double(const std::string &key, double value);
			void set_str(const std::string &key, const std::string &value);
			void set_array(const std::string &key, const array &value);
			void set(const std::string &key, const object &value);

			void add_int(const std::string &key, int32_t value);
			void add_int64(const std::string &key, int64_t value);
			void add_bool(const std::string &key, bool value);
			void add_double(const std::string &key, double value);
			void add_str(const std::string &key, const std::string &value);
			void add_array(const std::string &key, const array &value);
			void add(const std::string &key, const object &value);

			int32_t to_int() const;
			int64_t to_int64() const;
			bool to_bool() const;
			double to_double() const;
			std::string to_str() const;
			array to_array() const;

			bool is_int() const;
			bool is_bool() const;
			bool is_double() const;
			bool is_str() const;
			bool is_array() const;
			bool is_obj() const;
			bool is_null() const;

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
