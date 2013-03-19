#ifndef ARG3_JSON_OBJECT_ITERATOR_H_
#define ARG3_JSON_OBJECT_ITERATOR_H_

#include <iterator>

using namespace std;

namespace arg3
{
	namespace json
	{ 
		typedef pair<string,object> object_iterator_entry;

		class object_iterator : public iterator<input_iterator_tag, object_iterator_entry>
		{
			friend class object;
		public:

			typedef input_iterator_tag iterator_category;
		    typedef typename iterator<input_iterator_tag, object_iterator_entry>::value_type value_type;
		    typedef typename iterator<input_iterator_tag, object_iterator_entry>::difference_type difference_type;
		    typedef typename iterator<input_iterator_tag, object_iterator_entry>::reference reference;
		    typedef typename iterator<input_iterator_tag, object_iterator_entry>::pointer pointer;

		    object_iterator(const object_iterator &other);
		    virtual ~object_iterator();

		    object_iterator& operator=(const object_iterator &other);

			reference operator*();

            pointer operator->();

            object_iterator& operator++();

            object_iterator operator++(int);

            object_iterator operator+(difference_type n);

            object_iterator &operator+=(difference_type n);

            bool operator==(const object_iterator& other) const;

            bool operator!=(const object_iterator& other) const;
            
		private:
			struct lh_entry *entry_;

			value_type ref_;

			object_iterator(struct lh_entry *entry);

			reference get_ref();
		};
	}
}

#endif
