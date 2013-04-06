#ifndef ARG3_VARIANT_H_

#include <string>
#include <cmath>
#include <cstring>

using namespace std;

namespace arg3
{

    class variant
    {
    public:
        enum
        {
            BOOL, CHAR, UCHAR, WCHAR, SHORT, USHORT, INT, UINT, LONG, ULONG, LLONG, ULLONG, FLOAT, DOUBLE, LDOUBLE, POINTER,
            CSTRING, STRING, WCSTRING, WSTRING
        };
    private:
        static const int BASE = 0; // autodetect
        int type_;
        unsigned *refcount_;
        union var
        {
            //members
            int i;
            long l;
            long long ll;
            unsigned ui;
            unsigned long ul;
            unsigned long long ull;
            float f;
            double d;
            long double ld;
            const void *p;
            //initializers
            var(int i) : i(i) {}
            var(unsigned ui) : ui(ui) {}
            var(long l) : l(l) {}
            var(unsigned long ul) : ul(ul) {}
            var(float f) : f(f) {}
            var(double d) : d(d) {}
            var(long double ld) : ld(d) {}
            var(long long ll) : ll(ll) {}
            var(unsigned long long ull) : ull(ull) {}
            var(void *p) : p(p) {}
            var(const char *str) : p(str) {}
            var(const wchar_t *str) : p(str) {}
        } value_;

        template<typename T>
        T D(T def) const
        {
#ifdef ARG3_VARIANT_THROW_EXCEPTIONS
            throw illegal_argument();
#else
            return def;
#endif
        }

        template<typename T>
        T V(T val) const
        {
            if(numeric_limits<T>::max() == val)
                throw out_of_range("invalid conversion");

            return val;
        }

        template<typename T>
        T convert_numeric(T def) const
        {
            switch (type_)
            {
            case CHAR:
            case UCHAR:
            case WCHAR:
            case SHORT:
            case USHORT:
            case INT:
                if (value_.i <= numeric_limits<T>::max() && value_.i >= numeric_limits<T>::min())
                    return value_.i;
            case UINT:
                if (value_.ui < numeric_limits<T>::max())
                    return static_cast<int>(value_.ui);
            case LONG:
                if (value_.l <= numeric_limits<T>::max() && value_.l >= numeric_limits<T>::min())
                    return static_cast<int>(value_.l);
            case ULONG:
                if (value_.ul <= numeric_limits<T>::max())
                    return static_cast<int>(value_.ul);
            case LLONG:
                if (value_.ll <= numeric_limits<T>::max() && value_.ll >= numeric_limits<T>::min())
                    return static_cast<int>(value_.ll);
            case ULLONG:
                if (value_.ull <= numeric_limits<T>::max())
                    return static_cast<int>(value_.ull);
            case DOUBLE:
                if (value_.d <= numeric_limits<T>::max() && value_.d >= numeric_limits<T>::min())
                    return static_cast<int>(value_.d);
            case FLOAT:
                if (value_.f <= numeric_limits<T>::max() && value_.f >= numeric_limits<T>::min())
                    return static_cast<int>(value_.f);
            case LDOUBLE:
                if (value_.ld <= numeric_limits<T>::max() && value_.ld >= numeric_limits<T>::min())
                    return static_cast<int>(value_.ld);
            }
            return D(def);
        };

    public:

        // constructors
        variant();
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
        variant(void *p);
        variant(const char *str);
        variant(const wchar_t *str);
        variant(const string &str);
        variant(const wstring &str);

        // copy constructor
        variant(const variant &other);

        variant &operator=(const variant &other);

        ~variant();

        int type() const;

        // implicit cast operators
        operator string() const;

        operator int() const;

        operator long() const;

        operator long long() const;

        operator unsigned long() const;

        operator unsigned long long() const;

        operator double() const;

        operator float() const;

        operator bool() const;

        operator wstring() const;

        operator unsigned() const;

        // equality operators

        bool operator==(bool other) const;

        bool operator==(float other) const;

        bool operator==(const wstring &str) const;

        bool operator==(const string &str) const;

        bool operator==(unsigned long long ull) const;

        bool operator==(long long ll) const;

        bool operator==(long l) const;

        bool operator==(int i) const;

        bool operator==(unsigned ui) const;

        bool operator==(unsigned long ul) const;

        bool operator==(const variant &value) const;

        bool equals(const variant &value) const;

        // conversion methods
        string to_string(const string &def = "") const;

        const char *to_cstring(const char *def = NULL) const;

        const wchar_t *to_wcstring(const wchar_t *def = NULL) const;

        wstring to_wstring(const wstring &def = L"") const;

        bool is_string() const;

        bool is_wstring() const;

        bool is_numeric() const;

        bool is_real() const;

        int to_int(int def = 0) const;

        unsigned to_uint(unsigned def = 0) const;

        long to_long(long def = 0) const;

        unsigned long to_ulong(unsigned long def = 0) const;

        long long to_llong(long long def = 0) const;

        unsigned long long to_ullong(unsigned long long def = 0) const;

        double to_double(double def = numeric_limits<double>::quiet_NaN()) const;

        bool to_bool() const;

        float to_float(float def = numeric_limits<float>::quiet_NaN()) const;
    };

    // for streams

    ostream &operator<<(ostream &stream, const variant &v);

    // equality operators

    bool operator==(float f, const variant &v);
    bool operator==(const wstring &str, const variant &v);

    bool operator==(const string &str, const variant &v);

    bool operator==(unsigned long long ull, const variant &v);

    bool operator==(long long ll, const variant &v);
    bool operator==(long l, const variant &v);
    bool operator==(int i, const variant &v);

    bool operator==(unsigned ui, const variant &v);

    bool operator==(unsigned long ul, const variant &v);

    bool operator==(bool b, const variant &v) ;

    bool operator==(double d, const variant &v) ;
}

#endif
