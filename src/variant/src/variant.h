
#ifndef CODA_VARIANT_H
#define CODA_VARIANT_H

#include <cmath>
#include <cstring>
#include <functional>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include "binary.h"

namespace coda
{
    /*!
     * an exception thrown when the variant class cannot convert a value
     */
    class illegal_conversion : std::runtime_error
    {
       public:
        /*!
         * constructs illegal_conversion with a description
         * @param  what_arg what went wrong description
         */
        explicit illegal_conversion(const std::string &what_arg) : std::runtime_error(what_arg)
        {
        }

        /*!
         * default constructor
         */
        explicit illegal_conversion() : std::runtime_error("no conversion available")
        {
        }
    };

    /*!
     * a data type container
     */
    class variant
    {
       public:
        typedef enum { NULLTYPE, NUMBER, UNUMBER, REAL, BINARY, STRING, WSTRING, CHAR, WCHAR, BOOL, COMPLEX } types;

        static const char *const TYPE_NAMES[];

        /*!
         * an abstract base class to implement custom variant types
         */
        class complex
        {
           public:
            /*!
             * gets the size of the contained data
             * @return the size
             */
            virtual size_t size() const = 0;

            /*!
             * gets the hash code for this object
             * @return       the hash code value
             */
            virtual long hashcode() const = 0;

            /*
             * conversion methods, override to implement for a custom type
             */
            virtual std::string to_string() const = 0;
            virtual std::wstring to_wstring() const;
            virtual int to_int() const;
            virtual unsigned to_uint() const;
            virtual long to_long() const;
            virtual unsigned long to_ulong() const;
            virtual long long to_llong() const;
            virtual unsigned long long to_ullong() const;
            virtual double to_double() const;
            virtual long double to_ldouble() const;
            virtual bool to_bool() const;
            virtual float to_float() const;
            virtual const void *to_pointer() const;
            virtual binary to_binary() const;
            virtual char to_char() const;
            virtual unsigned char to_uchar() const;
            virtual wchar_t to_wchar() const;
            virtual const char *to_cstring() const;
            virtual const wchar_t *to_wcstring() const;

            /* cast operators */
            operator std::string() const;
            operator int() const;
            operator long() const;
            operator long long() const;
            operator unsigned long() const;
            operator unsigned long long() const;
            operator double() const;
            operator long double() const;
            operator float() const;
            operator bool() const;
            operator std::wstring() const;
            operator unsigned() const;
            operator char() const;
            operator unsigned char() const;
            operator wchar_t() const;
            operator const wchar_t *() const;
            operator const char *() const;
            operator binary() const;

            /*!
             * tests equality of this object to another
             */
            bool equals(const complex &other) const;
            bool operator==(const complex &other) const;
        };

       private:
        static const int BASE = 0;  // autodetect

        types type_;

        union {
            // members
            long long num_;
            unsigned long long unum_;
            long double real_;
            std::string str_;
            std::wstring wstr_;
            coda::binary ptr_;
            std::shared_ptr<complex> compl_;
        };

        size_t size_;

        /*! attempts to make the type T signed */
        template <typename T>
        using try_make_signed = typename std::conditional<std::is_integral<T>::value, std::make_signed<T>, std::common_type<T> >::type;

        /*! attempts to make the type T unsigned */
        template <typename T>
        using try_make_unsigned = typename std::conditional<std::is_integral<T>::value, std::make_unsigned<T>, std::common_type<T> >::type;

        /*!
         * converts a numeric value to the type T
         */
        template <typename T>
        T convert_numeric() const
        {
            switch (type_) {
                case BOOL:
                case CHAR:
                case WCHAR:
                case NUMBER: {
                    /* test if the desired type is unsigned */
                    if (std::is_unsigned<T>::value) {
                        /* cannot convert an signed value to unsigned */
                        if (num_ < 0) {
                            throw illegal_conversion();
                        }
                        /* check the range and cast the unsigned value */
                        if (static_cast<T>(num_) <= std::numeric_limits<T>::max() && static_cast<T>(num_) >= std::numeric_limits<T>::min()) {
                            return static_cast<T>(num_);
                        }
                    }
                    /* test signed ranges and cast the value */
                    else if (num_ <= std::numeric_limits<typename try_make_signed<T>::type>::max() &&
                             num_ >= std::numeric_limits<typename try_make_signed<T>::type>::min()) {
                        return static_cast<T>(num_);
                    }
                    break;
                }
                case UNUMBER: {
                    if (std::is_signed<T>::value) {
                        if (unum_ <= unsigned(std::numeric_limits<T>::max())) {
                            return static_cast<T>(unum_);
                        }
                    } else if (unum_ <= std::numeric_limits<typename try_make_unsigned<T>::type>::max() &&
                               unum_ >= std::numeric_limits<typename try_make_unsigned<T>::type>::min()) {
                        return static_cast<T>(unum_);
                    }
                    break;
                }
                case REAL:
                    if (real_ <= std::numeric_limits<T>::max() && real_ >= std::numeric_limits<T>::lowest()) {
                        return static_cast<T>(real_);
                    }
                    break;
                default:
                    break;
            }
            throw illegal_conversion();
        }

        /*!
         * a string function that accepts a base argument
         */
        template <class T>
        using str_base_fn = T (*)(const std::string &, size_t *, int);

        /*!
         * a wide string function that accepts a base argument
         */
        template <class T>
        using wstr_base_fn = T (*)(const std::wstring &, size_t *, int);

        /*!
         * a string function
         */
        template <class T>
        using str_fn = T (*)(const std::string &, size_t *);

        /*!
         * a wide string function
         */
        template <class T>
        using wstr_fn = T (*)(const std::wstring &, size_t *);

        /*!
         * attempts to convert to a numeric using a base
         */
        template <typename T, typename R>
        T convert_base(str_base_fn<R> strfunk, wstr_base_fn<R> wstrfunk, int base) const
        {
            if (is_numeric() || is_real()) {
                return convert_numeric<T>();
            }

            if (is_string()) {
                try {
                    return strfunk(str_, NULL, base);
                } catch (const std::exception &e) {
                    throw illegal_conversion(e.what());
                }
            }

            if (is_wstring()) {
                try {
                    return wstrfunk(wstr_, NULL, base);
                } catch (const std::exception &e) {
                    throw illegal_conversion(e.what());
                }
            }

            if (is_complex()) {
                try {
                    // TODO: need to test if complex type is a string or numeric
                    return strfunk(compl_->to_string(), NULL, base);
                } catch (const std::exception &e) {
                    throw illegal_conversion(e.what());
                }
            }

            throw illegal_conversion();
        }

        /*!
         * attempts to convert to a numeric
         */
        template <typename T, typename R>
        T convert(str_fn<R> strfunk, wstr_fn<R> wstrfunk) const
        {
            if (is_numeric() || is_real()) {
                return convert_numeric<T>();
            }

            if (is_string()) {
                try {
                    return strfunk(str_, NULL);
                } catch (const std::exception &e) {
                    throw illegal_conversion(e.what());
                }
            }

            if (is_wstring()) {
                try {
                    return wstrfunk(wstr_, NULL);
                } catch (const std::exception &e) {
                    throw illegal_conversion(e.what());
                }
            }

            if (is_complex()) {
                try {
                    // TODO: need to test if complex type is a string or numeric
                    return strfunk(compl_->to_string(), NULL);
                } catch (const std::exception &e) {
                    throw illegal_conversion(e.what());
                }
            }

            throw illegal_conversion();
        }

        /*!
         * copies a variant to this
         * @param  other the other variant
         * @return       a reference to this instance
         */
        variant &copy_value(const variant &other);

        /*!
         * moves a variant to this
         * @param  other the other variant
         * @return       a reference to this instance
         */
        variant &move_value(variant &&other);

        /*!
         * releases resources held by this instance
         */
        void cleanup();

       public:
        // constructors
        variant();
        variant(const std::nullptr_t &null);
        explicit variant(bool b);
        variant(char c);
        variant(unsigned char uc);
        variant(wchar_t wc);
        variant(short s);
        variant(unsigned short us);
        variant(int i);
        variant(unsigned ui);
        variant(long l);
        variant(unsigned long ul);
        variant(float f);
        variant(double d);
        variant(long double ld);
        variant(long long ll);
        variant(unsigned long long ull);
        variant(const binary &bin);
        variant(const char *str);
        variant(const wchar_t *str);
        variant(const std::string &str);
        variant(const std::wstring &str);
        explicit variant(const std::shared_ptr<complex> &c);

        // boilerplate
        variant(const variant &other);
        variant(variant &&other);
        variant &operator=(const variant &other);
        variant &operator=(variant &&other);
        virtual ~variant();

        // implicit cast operators
        operator std::string() const;
        operator int() const;
        operator long() const;
        operator long long() const;
        operator unsigned long() const;
        operator unsigned long long() const;
        operator double() const;
        operator long double() const;
        operator float() const;
        operator bool() const;
        operator std::wstring() const;
        operator unsigned() const;
        operator char() const;
        operator unsigned char() const;
        operator wchar_t() const;
        operator const wchar_t *() const;
        operator const char *() const;
        operator binary() const;

        // equality operators
        bool operator==(const std::nullptr_t &t) const;
        bool operator==(bool other) const;
        bool operator==(float other) const;
        bool operator==(double other) const;
        bool operator==(long double other) const;
        bool operator==(const std::wstring &str) const;
        bool operator==(const std::string &str) const;
        bool operator==(unsigned long long ull) const;
        bool operator==(long long ll) const;
        bool operator==(long l) const;
        bool operator==(int i) const;
        bool operator==(unsigned ui) const;
        bool operator==(unsigned long ul) const;
        bool operator==(const char *str) const;
        bool operator==(const wchar_t *str) const;
        bool operator==(const variant &value) const;
        bool operator==(const binary &bin) const;

        /* explicit for disambiguity sake */
        bool operator!=(const std::nullptr_t &t) const;
        bool operator!=(bool other) const;
        bool operator!=(float other) const;
        bool operator!=(double other) const;
        bool operator!=(long double other) const;
        bool operator!=(const std::wstring &str) const;
        bool operator!=(const std::string &str) const;
        bool operator!=(unsigned long long ull) const;
        bool operator!=(long long ll) const;
        bool operator!=(long l) const;
        bool operator!=(int i) const;
        bool operator!=(unsigned ui) const;
        bool operator!=(unsigned long ul) const;
        bool operator!=(const char *str) const;
        bool operator!=(const wchar_t *str) const;
        bool operator!=(const variant &value) const;
        bool operator!=(const binary &bin) const;
        /*!
         * tests if this instance is equal to another variant
         * @param  value the other variant
         * @return       true if the two objects are equal
         */
        bool equals(const variant &value) const;

        /*!
         * tests if this instance is a string
         * @return true if this is a string
         */
        bool is_string() const;

        /*!
         * tests if this instance is a wide string
         * @return true if this is a wide string
         */
        bool is_wstring() const;

        /*!
         * tests if this is a numeric value (int, long, double, etc)
         * @return true if this is numeric
         */
        bool is_numeric() const;

        /*!
         * tests if this is a real number
         * @return true if the value is a real number
         */
        bool is_real() const;

        /*!
         * tests if this is null
         * @return true if the value is null
         */
        bool is_null() const;

        /*!
         * tests if this is binary
         * @return true if the value is binary
         */
        bool is_binary() const;

        /*!
         * tests if this variant is using a custom type
         * @return true if this variant is custom
         */
        bool is_complex() const;

        /*!
         * gets the size of the value
         * @return the size
         */
        size_t size() const;

        /*!
         * gets the type of the value
         * @return the value type
         */
        types type() const;

        /*!
         * gets the name of the type
         * @return the value type name
         */
        std::string type_name() const;

        // conversion methods

        /*!
         * gets or converts a integer value
         * @param  def the default value if conversion fails
         * @return     the integer value
         */
        int to_int(const int def) const;

        /*!
         * gets or converts a integer value
         * Note: will throw illegal_conversion on error
         * @return the integer value
         */
        int to_int() const;

        /*!
         * gets or converts a unsigned value
         * @param  def the default value of conversion fails
         * @return     the unsigned value
         */
        unsigned to_uint(const unsigned def) const;

        /*!
         * gets or converts a unsigned value
         * Note: will throw illegal_conversion on error
         * @return the unsigned value
         */
        unsigned to_uint() const;

        /*!
         * gets or converts a long value
         * @param  def the default value if conversion fails
         * @return     the  long value
         */
        long to_long(const long def) const;

        /*!
         * gets or converts a long value
         * Note: will throw illegal_conversion on error
         * @return the long value
         */
        long to_long() const;

        /*!
         * gets or converts a unsigned long value
         * @param  def the default value if conversion fails
         * @return     the unsigned long value
         */
        unsigned long to_ulong(const unsigned long def) const;

        /*!
         * gets or converts a unsigned long value
         * Note: will throw illegal_conversion on error
         * @return the unsigned long value
         */
        unsigned long to_ulong() const;

        /*!
         * gets or converts a long long value
         * @param  def the default value if conversion fails
         * @return     the long long value
         */
        long long to_llong(const long long def) const;

        /*!
         * gets or converts a long long value
         * Note: will throw illegal_conversion on error
         * @return the long long value
         */
        long long to_llong() const;

        /*!
         * gets or converts a unsigned long long value
         * @param  def the default value if conversion fails
         * @return     the unsigned long long value
         */
        unsigned long long to_ullong(const unsigned long long def) const;

        /*!
         * gets or converts a unsigned long long value
         * Note: will throw illegal_conversion on error
         * @return the unsigned long long value
         */
        unsigned long long to_ullong() const;

        /*!
         * gets or converts a double value
         * @param  def the default value if conversion fails
         * @return     the double value
         */
        double to_double(const double def) const;

        /*!
         * gets or converts a double value
         * Note: will throw illegal_conversion on error
         * @return the double value
         */
        double to_double() const;

        /*!
         * gets or converts a long double value
         * @param  def the default value if conversion fails
         * @return     the long double value
         */
        long double to_ldouble(const long double def) const;

        /*!
         * gets or converts a long double value
         * Note: will throw illegal_conversion on error
         * @return the long double value
         */
        long double to_ldouble() const;

        /*!
         * gets or converts a boolean value
         * @return the boolean value
         */
        bool to_bool() const;

        /*!
         * gets or converts a float value
         * @param  def the default value if conversion fails
         * @return     the float value
         */
        float to_float(const float def) const;

        /*!
         * gets or converts a float value
         * Note: will throw illegal_conversion on error
         * @return the float value
         */
        float to_float() const;

        /*!
         * gets or converts a pointer value
         * Note: will throw illegal_conversion on error
         * @return the pointer value
         */
        const void *to_pointer() const;

        /*!
         * gets or converts a binary value
         * Note: will throw illegal_conversion on error
         * @return the binary value
         */
        binary to_binary() const;

        /*!
         * gets or converts a char value
         * @param  def the default value if conversion fails
         * @return     the char value
         */
        char to_char(const char def) const;

        /*!
         * gets or converts a char value
         * Note: will throw illegal_conversion on error
         * @return the char value
         */
        char to_char() const;

        /*!
         * gets or converts a unsigned char value
         * @param  def the default value if conversion fails
         * @return     the unsigned char
         */
        unsigned char to_uchar(const unsigned char def) const;

        /*!
         * gets or converts a unsigned char value
         * Note: will throw illegal_conversion on error
         * @return the unsigned char value
         */
        unsigned char to_uchar() const;

        /*!
         * gets or converts a wide char value
         * @param  def the default value if conversion fails
         * @return     the wide char value
         */
        wchar_t to_wchar(const wchar_t def) const;

        /*!
         * gets or converts a wide char value
         * Note: will throw illegal_conversion on error
         * @return the wide char value
         */
        wchar_t to_wchar() const;

        /*!
         * gets or converts a string value
         * @param  def the default value if conversion fails
         * @return     the string value
         */
        std::string to_string(const std::string &def) const;

        /*!
         * gets or converts a string value
         * Note: will throw illegal_conversion on error
         * @return the string value
         */
        std::string to_string() const;

        /*!
         * gets or converts a c-string value
         * @param  def the default value if conversion fails
         * @return     the c-string value
         */
        const char *to_cstring(const char *def) const;

        /*!
         * gets or converts a c-string value
         * Note: will throw illegal_conversion on error
         * @return the c-string value
         */
        const char *to_cstring() const;

        /*!
         * gets or converts a wide c-string value
         * @param  def the default value if conversion fails
         * @return     the wide c-string value
         */
        const wchar_t *to_wcstring(const wchar_t *def) const;

        /*!
         * gets or converts a wide c-string
         * Note: will throw illegal_conversion on error
         * @return the wide c-string value
         */
        const wchar_t *to_wcstring() const;

        /*!
         * gets or converts a wide string
         * @param  def the default value if conversion fails
         * @return     the wide string value
         */
        std::wstring to_wstring(const std::wstring &def) const;

        /*!
         * gets or converts a wide string
         * Note: will throw illegal_conversion on error
         * @return the wide string value
         */
        std::wstring to_wstring() const;

        /*!
         * gets the custom value associated with this variant
         */
        std::shared_ptr<complex> to_complex() const;
    };

    /*!
     * output stream operator
     */
    std::ostream &operator<<(std::ostream &stream, const variant &v);
    std::ostream &operator<<(std::ostream &out, const variant::complex &v);

    // equality operators
    bool operator==(const std::nullptr_t &n, const variant &v);
    bool operator==(float f, const variant &v);
    bool operator==(const std::wstring &str, const variant &v);
    bool operator==(const std::string &str, const variant &v);
    bool operator==(unsigned long long ull, const variant &v);
    bool operator==(long long ll, const variant &v);
    bool operator==(long l, const variant &v);
    bool operator==(int i, const variant &v);
    bool operator==(unsigned ui, const variant &v);
    bool operator==(unsigned long ul, const variant &v);
    bool operator==(bool b, const variant &v);
    bool operator==(double d, const variant &v);
    bool operator==(long double ld, const variant &v);
    bool operator==(const binary &bin, const variant &v);
    bool operator==(const variant::complex &c, const variant &v);

    /* explicit for disambiguity sake */
    bool operator!=(const std::nullptr_t &n, const variant &v);
    bool operator!=(float f, const variant &v);
    bool operator!=(const std::wstring &str, const variant &v);
    bool operator!=(const std::string &str, const variant &v);
    bool operator!=(unsigned long long ull, const variant &v);
    bool operator!=(long long ll, const variant &v);
    bool operator!=(long l, const variant &v);
    bool operator!=(int i, const variant &v);
    bool operator!=(unsigned ui, const variant &v);
    bool operator!=(unsigned long ul, const variant &v);
    bool operator!=(bool b, const variant &v);
    bool operator!=(double d, const variant &v);
    bool operator!=(long double ld, const variant &v);
    bool operator!=(const binary &bin, const variant &v);
    bool operator!=(const variant::complex &c, const variant &v);

    /*!
     * gets a string representation of the variant
     * @param  value the variant object
     * @return       a string
     */
    std::string to_string(const variant &value);
    std::string to_string(const variant::complex &value);
}

#endif
