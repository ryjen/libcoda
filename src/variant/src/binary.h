#ifndef RJ_BINARY_H_
#define RJ_BINARY_H_

#include <stdlib.h>
#include <cstring>
#include <ostream>

namespace rj
{
    /*!
     * Represents a chunk of binary data.
     * Maintains its own copy of the data and performs its own memory management.
     */
    class binary
    {
        friend std::ostream &operator<<(std::ostream &out, const binary &value);

       public:
        /*! allocator function */
        typedef void *(*alloc_fn)(size_t);
        /*! copy function */
        typedef void *(*copy_fn)(void *, const void *, size_t);
        /*! free function */
        typedef void (*free_fn)(void *);
        /*! compare function */
        typedef int (*cmp_fn)(const void *, const void *, size_t);

       private:
        void *val_;
        size_t sz_;
        alloc_fn alloc_;
        copy_fn copy_;
        free_fn free_;
        cmp_fn cmp_;

        void copy_mem(const void *p, size_t sz, alloc_fn construct, copy_fn copy);

       public:
        /*!
         * default constructor
         */
        binary();
        /*!
         * @param p   the binary data
         * @param sz  the size of the binary data
         * @param construct the allocator function (default: malloc)
         * @param copy the copy function (default: memcpy)
         * @param destroy the free function (default: free)
         * @param compare the compare function (default: memcmp)
         */
        binary(const void *p, size_t sz, alloc_fn construct = malloc, copy_fn copy = memcpy, free_fn destroy = free, cmp_fn compare = memcmp);

        /* boilerplate */
        binary(const binary &p);
        binary(binary &&p);
        virtual ~binary();
        binary &operator=(const binary &p);
        binary &operator=(binary &&p);

        /*!
         * gets the size of the data
         * @return the size
         */
        size_t size() const;

        /*!
         * gets the data pointer
         * @return a pointer to the data
         */
        void *value() const;

        /*!
         * tests if this instance is empty
         * @return true if the data pointer is null
         */
        bool is_null() const;

        /*!
         * tests if this data will free itself
         * @return true if deallocation will occur
         */
        bool is_transient() const;

        /*!
         * a string representation (hex of the pointer)
         * @return the hex string
         */
        std::string to_string() const;

        /* equality operators */
        bool operator==(const binary &p) const;
        bool operator==(const void *p) const;
        bool operator==(const std::nullptr_t &null) const;
    };

    /*!
     * standard output stream operator
     */
    std::ostream &operator<<(std::ostream &out, const binary &value);

    /* equality operators */
    bool operator==(const void *ptr, const rj::binary &other);
    bool operator==(const std::nullptr_t &null, const rj::binary &other);

    /*!
     * gets a string representation of a binary object
     * @param  p the binary object
     * @return   the hex string of the pointer
     */
    std::string to_string(const rj::binary &p);
}

#endif
