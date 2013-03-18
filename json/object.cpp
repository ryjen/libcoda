#include "object.h"
#include "array.h"
#include "object_iterator.h"

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

		void object::set_int(const std::string &key, int32_t value)
		{
			json_object_object_add(value_, key.c_str(), json_object_new_int(value));
		}

		void object::set_int64(const std::string &key, int64_t value)
		{
			json_object_object_add(value_, key.c_str(), json_object_new_int64(value));
		}
		void object::set_bool(const std::string &key, bool value)
		{
			json_object_object_add(value_, key.c_str(), json_object_new_boolean(value));
		}
		void object::set_double(const std::string &key, double value)
		{
			json_object_object_add(value_, key.c_str(), json_object_new_double(value));
		}
		void object::set_str(const std::string &key, const std::string &value)
		{
			json_object_object_add(value_, key.c_str(), json_object_new_string(value.c_str()));
		}

		void object::set_array(const std::string &key, const array &value)
		{
			json_object_object_add(value_, key.c_str(), json_object_get(value.value_));
		}

		void object::set(const std::string &key, const object &value)
		{
			json_object_object_add(value_, key.c_str(), json_object_get(value.value_));
		}

		bool object::is_int() const {
			return json_object_is_type(value_, json_type_int);
		}

		bool object::is_bool() const {
			return json_object_is_type(value_, json_type_boolean);
		}

		bool object::is_double() const {
			return json_object_is_type(value_, json_type_double);
		}

		bool object::is_str() const {
			return json_object_is_type(value_, json_type_string);
		}

		bool object::is_array() const {
			return json_object_is_type(value_, json_type_array);
		}

		bool object::is_obj() const {
			return json_object_is_type(value_, json_type_object);
		}

		bool object::is_null() const {
			return json_object_is_type(value_, json_type_null);
		}

		object::iterator object::begin() {
			return object_iterator(json_object_get_object(value_)->head);
		}

		object_iterator object::end() {
			return object_iterator(NULL);
		}

		object_iterator object::begin() const
		{
			return object_iterator(json_object_get_object(value_)->head);
		}

		object_iterator object::end() const {
			return object_iterator(NULL);
		}

		int32_t object::to_int() const {
			return json_object_get_int(value_);
		}

		int64_t object::to_int64() const {
			return json_object_get_int64(value_);
		}

		bool object::to_bool() const {
			return json_object_get_boolean(value_);
		}

		double object::to_double() const {
			return json_object_get_double(value_);
		}

		string object::to_str() const {
			return json_object_get_string(value_);
		}

		array object::to_array() const {
			if(is_array())
				return array(value_);
			else
				return array();
		}
	}
}
