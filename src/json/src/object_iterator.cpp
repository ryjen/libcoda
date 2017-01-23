#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <json_object.h>
#include <linkhash.h>
#include "object.h"

namespace rj
{
    namespace json
    {
        object_iterator::object_iterator(struct lh_entry *entry) : entry_(entry)
        {
        }

        object_iterator::object_iterator(const object_iterator &other) : entry_(other.entry_)
        {
        }
        object_iterator::object_iterator(object_iterator &&other) : entry_(other.entry_)
        {
            other.entry_ = NULL;
        }
        object_iterator::~object_iterator()
        {
        }

        object_iterator &object_iterator::operator=(const object_iterator &other)
        {
            entry_ = other.entry_;

            return *this;
        }
        object_iterator &object_iterator::operator=(object_iterator &&other)
        {
            entry_ = other.entry_;

            other.entry_ = NULL;

            return *this;
        }

        bool object_iterator::is_valid() const
        {
            return entry_ != NULL;
        }

        object_iterator::reference object_iterator::get_ref()
        {
            if (entry_ == NULL) {
                static value_type nil;
                return nil;
            }

            ref_ = make_pair(string(static_cast<char *>(entry_->k)), object(static_cast<json_object *>(const_cast<void *>(entry_->v))));

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


        object_iterator &object_iterator::operator++()
        {
            if (entry_ != NULL) entry_ = entry_->next;
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
            for (difference_type i = 0; i < n; i++) ++(tmp);
            return tmp;
        }


        object_iterator &object_iterator::operator+=(difference_type n)
        {
            for (difference_type i = 0; i < n; i++) operator++();
            return *this;
        }


        bool object_iterator::operator==(const object_iterator &other) const
        {
            return entry_ == other.entry_;
        }


        bool object_iterator::operator!=(const object_iterator &other) const
        {
            return entry_ != other.entry_;
        }
    }
}
