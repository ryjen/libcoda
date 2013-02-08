/**
 * variant.h
 * utility class for arbitrary values with type conversion
 * author: ryan jennings <c0der78@gmail.com>, www.arg3.com
 * project: github.com/c0der78/variant
 * license: free to use, please keep this header intact and submit changes on github
 */
#ifndef ARG3_VARIANT_H_
#define ARG3_VARIANT_H_

#include <string>
#include <iostream>
#include <limits>

using namespace std;

namespace arg3
{
	template<typename T>
    class variant_value
    {
    public:
        // storage type
        typedef std::basic_string<T> value_type;
    protected:
        static const int BASE = 0; // autodetect base
        // the value
        value_type m_value;
    public:
        // constructors
        variant_value() : m_value() {}
        variant_value(const variant_value &other) : m_value(other.m_value) {}
        variant_value(const value_type &value) : m_value(value) {}
        variant_value(const T *value) : m_value(value) {}
        variant_value(T value) : m_value(1, value) {}
        variant_value(int value) : variant_value(std::to_string(value)) {}
        variant_value(long value) : variant_value(std::to_string(value)) {}
        variant_value(long long value) : variant_value(std::to_string(value)) {}
        variant_value(unsigned value) : variant_value(std::to_string(value)) {}
        variant_value(unsigned long value) : variant_value(std::to_string(value)) {}
        variant_value(unsigned long long value) : variant_value(std::to_string(value)) {}
        variant_value(float value) : variant_value(std::to_string(value)) {}
        variant_value(double value) : variant_value(std::to_string(value)) {}
        variant_value(long double value) : variant_value(std::to_string(value)) {}
        variant_value(bool value) : variant_value(std::to_string(value?1:0)) {}

        variant_value &operator=(const variant_value &other) {
            if(this != &other) {
                m_value = other.m_value;
            }
            return *this;
        }
        // other methods
        bool empty() const {
            return m_value.empty();
        }

        // conversion methods
        value_type to_string() const {
            return m_value;
        }

        const T* to_cstring() const {
            return m_value.c_str();
        }

        T to_char() const {
            if(m_value.size() == 0)
                return '\0';
            return m_value[0];
        }

        // numeric conversions have four formats:
        // 1. numeric base with exception
        // 2. numeric base with default value (no exception)
        // 3. default base with exception
        // 4. default base with default value (no exception)

        // integers
        int base_int(int base) const {
            return std::stoi(m_value, NULL, base);
        }
        int base_int(int base, int defaultValue) const {
            try {
                return base_int(base);
            }
            catch(const std::exception &e) {
                return defaultValue;
            }
        }
        int to_int() const {
            return base_int(BASE);
        }
        int to_int(int defaultValue) const {
            return base_int(BASE, defaultValue);
        }

        // unsigned integers
        unsigned base_uint(int base) const {

            return static_cast<unsigned>(std::stoul(m_value, NULL, base));
        }
        unsigned base_uint(int base, unsigned defaultValue) const {
            try {
                return base_uint(base);
            }
            catch(const std::exception &e) {
                return defaultValue;
            }
        }
        unsigned to_uint() const {
            return base_uint(BASE);
        }
        unsigned to_uint(unsigned defaultValue) const {
            return base_uint(BASE, defaultValue);
        }

        // long integers
        long base_long(int base) const {
            return std::stol(m_value, NULL, base);
        }
        long base_long(int base, long defaultValue) const {
            try {
                return base_long(base);
            }
            catch(const std::exception &e) {
                return defaultValue;
            }
        }
        long to_long() const {
            return base_long(BASE);
        }
        long to_long(long defaultValue) const {
            return base_long(BASE, defaultValue);
        }

        // unsigned long integers
        unsigned long base_ulong(int base) const {
            return std::stoul(m_value, NULL, base);
        }
        unsigned long base_ulong(int base, unsigned long defaultValue) const {
            try {
                return base_ulong(base);
            }
            catch(const std::exception &e) {
                return defaultValue;
            }
        }
        unsigned long to_ulong() const {
            return base_ulong(BASE);
        }
        unsigned long to_ulong(unsigned long defaultValue) const {
            return base_ulong(BASE, defaultValue);
        }

        // long long integers
        long long base_llong(int base) const {
            return std::stoll(m_value, NULL, base);
        }
        long long base_llong(int base, long long defaultValue) const {
            try {
                return base_llong(base);
            }
            catch(const std::exception &e) {
                return defaultValue;
            }
        }
        long long to_llong() const {
            return base_llong(BASE);
        }
        long long to_llong(long long defaultValue) const {
            return base_llong(BASE, defaultValue);
        }

        // unsigned long long integers
        unsigned long long base_ullong(int base) const {
            return std::stoull(m_value, NULL, base);
        }
        unsigned long long base_ullong(int base, unsigned long long defaultValue) const {
            try {
                return base_ullong(base);
            }
            catch(const std::exception &e) {
                return defaultValue;
            }
        }
        unsigned long long to_ullong() const {
            return base_ullong(BASE);
        }
        unsigned long long to_ullong(unsigned long long defaultValue) const {
            return base_ullong(BASE, defaultValue);
        }

        // boolean
        bool to_bool() const {
            return m_value != "false" && to_int(0) != 0;
        }
        bool to_bool(bool defaultValue) const {
            try {
                return to_bool();
            }
            catch(const std::exception &e) {
                return defaultValue;
            }
        }


        // double
        double to_double() const {
            return std::stod(m_value);
        }

        double to_double(double defaultValue) const {
            try {
                return to_double();
            }
            catch(const std::exception &e) {
                return defaultValue;
            }
        }

        // long double
        long double to_ldouble() const {
            return std::stold(m_value);
        }
        long double to_ldouble(long double defaultValue) const {
            try {
                return to_ldouble();
            }
            catch(const std::exception &e) {
                return defaultValue;
            }
        }

        // floats
        float to_float() const {
            return std::stof(m_value);
        }

        float to_float(float defaultValue) const {
            try {
                return to_float();
            }
            catch(const std::exception &e) {
                return defaultValue;
            }
        }


        // cast operators
        operator value_type() const {
            return to_string();
        }
        operator const T *() const {
            return to_cstring();
        }
        operator T() const {
            return to_char();
        }
        operator unsigned() const {
            return to_uint();
        }
        operator int() const {
            return to_int();
        }
        operator long() const {
            return to_long();
        }
        operator unsigned long() const {
            return to_ulong();
        }
        operator long long() const {
            return to_llong();
        }
        operator unsigned long long() const {
            return to_ullong();
        }
        operator bool() const {
            return to_bool();
        }
        operator double() const {
            return to_double();
        }
        operator long double() const {
            return to_ldouble();
        }
        operator float() const {
            return to_float();
        }

        // append operators
        // custom types should define a std::to_string function
        template<typename V>
        variant_value<T> &operator <<(const V &value) {
            m_value.append(std::to_string(value));
            return *this;
        }

        // equality
        bool equals(const variant_value<T> &value) const {
            return m_value == value.m_value;
        }

        bool operator==(const variant_value<T> &value) const {
            return equals(value);
        }
    };

    // type definitions
    typedef variant_value<char> variant;
    typedef variant_value<wchar_t> wvariant;

    // global stream operator
    template<typename T>
    ostream& operator<<(ostream& stream, const variant_value<T>& v) {
        stream << v.to_cstring();
        return stream;
    }

    // global equality operators
    template<typename T>
    bool operator==(const typename variant_value<T>::value_type &lhs, const variant_value<T> &v) {
        return lhs == v.to_string();
    }

    template<typename T>
    bool operator==(const T* lhs, const variant_value<T> &v) {
        return variant_value<T>(lhs) == v;
    }

    template<typename T>
    bool operator==(T lhs, const variant_value<T> &v) {
        return lhs == v.to_char();
    }

    template<typename T>
    bool operator==(long lhs, const variant_value<T> &v) {
        return lhs == v.to_long();
    }

    template<typename T>
    bool operator==(unsigned long lhs, const variant_value<T> &v) {
        return lhs == v.to_ulong();
    }

    template<typename T>
    bool operator==(int lhs, const variant_value<T> &v) {
        return lhs == v.to_int();
    }

    template<typename T>
    bool operator==(unsigned lhs, const variant_value<T> &v) {
        return lhs == v.to_uint();
    }

    template<typename T>
    bool operator==(long long lhs, const variant_value<T> &v) {
        return lhs == v.to_llong();
    }

    template<typename T>
    bool operator==(unsigned long long lhs, const variant_value<T> &v) {
        return lhs == v.to_ullong();
    }

    template<typename T>
    bool operator==(float lhs, const variant_value<T> &v) {
        return lhs == v.to_float();
    }

    template<typename T>
    bool operator==(double lhs, const variant_value<T> &v) {
        return lhs == v.to_double();
    }

    template<typename T>
    bool operator==(long double lhs, const variant_value<T> &v) {
        return lhs == v.to_ldouble();
    }

    template<typename T>
    bool operator==(bool lhs, const variant_value<T> &v) {
        return lhs == v.to_bool();
    } 
}

#endif
