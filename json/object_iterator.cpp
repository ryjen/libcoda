
#include "object.h"

namespace arg3
{
	namespace json
	{
		object_iterator::object_iterator(struct lh_entry *entry) : entry_(entry)
		{

		}

        object_iterator::object_iterator(const object_iterator &other) : entry_(other.entry_)
        {

        }

        object_iterator::~object_iterator()
        {

        }

        object_iterator &object_iterator::operator=(const object_iterator &other)
        {
            if(this != &other)
            {
                entry_ = other.entry_;
            }

            return *this;
        }

		object_iterator::reference object_iterator::get_ref()
		{
			if(entry_ == NULL)
				return ref_;

			ref_ = make_pair(string(static_cast<char*>(entry_->k)), object(static_cast<json_object*>(const_cast<void*>(entry_->v))));

            return ref_;
		}

		object_iterator::reference object_iterator::operator*()
		{
			return get_ref();
		}

        object_iterator::pointer object_iterator::operator->()
        {
        	return &get_ref();
        }

        
        object_iterator& object_iterator::operator++()
        {
        	if(entry_ != NULL)
	        	entry_ = entry_->next;
        	return *this;
        }

        
        object_iterator object_iterator::operator++(int)
        {
        	object_iterator temp(*this);

        	++(*this);

        	return temp;
        }

        
        object_iterator object_iterator::operator+(difference_type n)
        {
            object_iterator tmp(*this);
            for (difference_type i = 0; i < n; i++)
                ++(tmp);
            return tmp;
        }

        
        object_iterator &object_iterator::operator+=(difference_type n)
        {
            for (difference_type i = 0; i < n; i++)
                operator++();
            return *this;
        }

        
        bool object_iterator::operator==(const object_iterator& other) const
        {
        	return entry_ == other.entry_;
        }

        
        bool object_iterator::operator!=(const object_iterator& other) const
        {
        	return entry_ != other.entry_;
        }


        
        bool operator==(const object_iterator& r1, const object_iterator& r2)
        {
        	return r1.operator==(r2);
        }

        
        bool operator!=(const object_iterator& r1, const object_iterator& r2)
        {
        	return r1.operator!=(r2);
        }
        
	}
}