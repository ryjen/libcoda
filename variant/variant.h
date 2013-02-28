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
        int m_type;
        unsigned *m_refcount;
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
        } m_value;

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
        T convert_numeric(T def) const
        {
            switch (m_type)
            {
            case CHAR:
            case UCHAR:
            case WCHAR:
            case SHORT:
            case USHORT:
            case INT:
                if (m_value.i <= numeric_limits<T>::max() && m_value.i >= numeric_limits<T>::min())
                    return m_value.i;
            case UINT:
                if (m_value.ui < numeric_limits<T>::max())
                    return static_cast<int>(m_value.ui);
            case LONG:
                if (m_value.l <= numeric_limits<T>::max() && m_value.l >= numeric_limits<T>::min())
                    return static_cast<int>(m_value.l);
            case ULONG:
                if (m_value.ul <= numeric_limits<T>::max())
                    return static_cast<int>(m_value.ul);
            case LLONG:
                if (m_value.ll <= numeric_limits<T>::max() && m_value.ll >= numeric_limits<T>::min())
                    return static_cast<int>(m_value.ll);
            case ULLONG:
                if (m_value.ull <= numeric_limits<T>::max())
                    return static_cast<int>(m_value.ull);
            case DOUBLE:
                if (m_value.d <= numeric_limits<T>::max() && m_value.d >= numeric_limits<T>::min())
                    return static_cast<int>(m_value.d);
            case FLOAT:
                if (m_value.f <= numeric_limits<T>::max() && m_value.f >= numeric_limits<T>::min())
                    return static_cast<int>(m_value.f);
            case LDOUBLE:
                if (m_value.ld <= numeric_limits<T>::max() && m_value.ld >= numeric_limits<T>::min())
                    return static_cast<int>(m_value.ld);
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
