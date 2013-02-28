#ifndef ARG3_VARIANT_H_

#include "variant.h"
#include <cstdlib>

namespace arg3
{

    variant::variant() :
        m_type(INT), m_value(0)
    {}

    variant::variant(char c) :
        m_type(CHAR), m_refcount(NULL), m_value(c)
    {}

    variant::variant(unsigned char uc) :
        m_type(UCHAR), m_refcount(NULL), m_value(uc)
    {}

    variant::variant(wchar_t wc) :
        m_type(WCHAR), m_refcount(NULL), m_value(wc)
    {}

    variant::variant(short s) :
        m_type(SHORT), m_refcount(NULL), m_value(s)
    {}

    variant::variant(unsigned short us) :
        m_type(USHORT), m_refcount(NULL), m_value(us)
    {}

    variant::variant(int i) :
        m_type(INT), m_refcount(NULL), m_value(i)
    {}

    variant::variant(unsigned ui) :
        m_type(UINT), m_refcount(NULL), m_value(ui)
    {}

    variant::variant(long l) :
        m_type(LONG), m_refcount(NULL), m_value(l)
    {}

    variant::variant(unsigned long ul) :
        m_type(ULONG), m_refcount(NULL), m_value(ul)
    {}

    variant::variant(float f) :
        m_type(FLOAT), m_refcount(NULL), m_value(f)
    {}

    variant::variant(double d) :
        m_type(DOUBLE), m_refcount(NULL), m_value(d)
    {}

    variant::variant(long double ld) :
        m_type(LDOUBLE), m_refcount(NULL), m_value(ld)
    {}

    variant::variant(long long ll) :
        m_type(LLONG), m_refcount(NULL), m_value(ll)
    {}

    variant::variant(unsigned long long ull) :
        m_type(ULLONG), m_refcount(NULL), m_value(ull)
    {}

    variant::variant(void *p) :
        m_type(POINTER), m_refcount(NULL), m_value(p)
    { }

    // for strings we initialize refcount and make a copy of the cstring

    variant::variant(const char *str) :
        m_type(CSTRING), m_refcount(new unsigned(0)), m_value(strdup(str))
    {}

    variant::variant(const wchar_t *str) :
        m_type(WCSTRING), m_refcount(new unsigned(0)), m_value(wcsdup(str))
    {}

    variant::variant(const string &str) :
        m_type(STRING), m_refcount(new unsigned(0)), m_value(strdup(str.c_str()))
    {}

    variant::variant(const wstring &str) :
        m_type(WSTRING), m_refcount(new unsigned(0)), m_value(wcsdup(str.c_str()))
    {}

    // copy constructor
    variant::variant(const variant &other) :
        m_type(other.m_type), m_refcount(other.m_refcount), m_value(other.m_value)
    {
        // update refcount
        if (m_refcount)
            (*m_refcount)++;
    }

    variant &variant::operator=(const variant &other)
    {
        if (this != &other)
        {

            m_type = other.m_type;

            m_value = other.m_value;

            m_refcount = other.m_refcount;

            // update refcount
            if (m_refcount)
                (*m_refcount)++;

        }
        return *this;
    }

    variant::~variant()
    {

        // check refcounts to free a pointer
        if (m_refcount)
        {
            // no references except this one
            if (*m_refcount == 0)
            {
                free(const_cast<void *>(m_value.p));
            }
            // decrement reference count
            else
            {
                (*m_refcount)--;
            }
        }

    }

    int variant::type() const
    {
        return m_type;
    }

    //operators
    variant::operator string() const
    {
        return to_string();
    }

    variant::operator int() const
    {
        return to_int();
    }

    variant::operator long() const
    {
        return to_long();
    }

    variant::operator long long() const
    {
        return to_llong();
    }

    variant::operator unsigned long() const
    {
        return to_ulong();
    }
    variant::operator unsigned long long() const
    {
        return to_ullong();
    }

    variant::operator double() const
    {
        return to_double();
    }

    variant::operator float() const
    {
        return to_float();
    }

    variant::operator bool() const
    {
        return to_bool();
    }

    variant::operator wstring() const
    {
        return to_wstring();
    }

    variant::operator unsigned() const
    {
        return to_uint();
    }

    bool variant::operator==(bool other) const
    {
        return to_bool() == other;
    }

    bool variant::operator==(float other) const
    {
        return to_float() == other;
    }

    bool variant::operator==(const wstring &str) const
    {
        return to_wstring() == str;
    }

    bool variant::operator==(const string &str) const
    {
        return to_string() == str;
    }

    bool variant::operator==(unsigned long long ull) const
    {
        return to_ullong() == ull;
    }

    bool variant::operator==(long long ll) const
    {
        return to_llong() == ll;
    }

    bool variant::operator==(long l) const
    {
        return to_long() == l;
    }

    bool variant::operator==(int i) const
    {
        return to_int() == i;
    }

    bool variant::operator==(unsigned ui) const
    {
        return to_uint() == ui;
    }

    bool variant::operator==(unsigned long ul) const
    {
        return to_ulong() == ul;
    }

    bool variant::equals(const variant &value) const
    {
        switch (m_type)
        {
        case CHAR:
        case UCHAR:
        case WCHAR:
        case SHORT:
        case USHORT:
        case INT:
            return m_value.i == value.m_value.i;
        case UINT:
            return m_value.ui == value.m_value.ui;
        case LONG:
            return m_value.l == value.m_value.l;
        case ULONG:
            return m_value.ul == value.m_value.ul;
        case LLONG:
            return m_value.ll == value.m_value.ll;
        case ULLONG:
            return m_value.ull == value.m_value.ull;
        case FLOAT:
            return m_value.f == value.m_value.f;
        case DOUBLE:
            return m_value.d == value.m_value.d;
        case LDOUBLE:
            return m_value.ld == value.m_value.ld;
        case POINTER:
            return m_value.p == value.m_value.p;
        case CSTRING:
        case STRING:
            return strcmp(to_cstring(), value.to_cstring());
        case WCSTRING:
        case WSTRING:
            return wcscmp(to_wcstring(), to_wcstring());
        default:
            return this == &value;
        }

    }

    bool variant::operator==(const variant &value) const
    {
        return equals(value);
    }

    string variant::to_string(const string &def) const
    {
        switch (m_type)
        {
        case STRING:
        case CSTRING:
            return static_cast<const char *>(m_value.p);
        case CHAR:
            return (const char *) &m_value.i;
        case BOOL:
            return m_value.i == 0 ? "false" : "true";
        case WCHAR:
        case UCHAR:
        case SHORT:
        case USHORT:
        case INT:
            return std::to_string(m_value.i);
        case UINT:
            return std::to_string(m_value.ui);
        case LONG:
            return std::to_string(m_value.l);
        case ULONG:
            return std::to_string(m_value.ul);
        case LLONG:
            return std::to_string(m_value.ll);
        case ULLONG:
            return std::to_string(m_value.ull);
        case FLOAT:
            return std::to_string(m_value.f);
        case DOUBLE:
            return std::to_string(m_value.d);
        case LDOUBLE:
            return std::to_string(m_value.ld);
        default:
        case WSTRING:
        case WCSTRING:
            return D(def);
        }
    }

    const char *variant::to_cstring(const char *def) const
    {
        switch (m_type)
        {
        case STRING:
        case CSTRING:
            return static_cast<const char *>(m_value.p);
        case CHAR:
            return (const char *) &m_value.i;
        default:
            return D(def);
        }
    }

    const wchar_t *variant::to_wcstring(const wchar_t *def) const
    {
        switch (m_type)
        {
        case WSTRING:
        case WCSTRING:
            return static_cast<const wchar_t *>(m_value.p);
        case WCHAR:
            return (const wchar_t *) &m_value.i;
        default:
            return D(def);
        }
    }

    wstring variant::to_wstring(const wstring &def) const
    {
        switch (m_type)
        {
        case STRING:
        case CSTRING:
            return D(def);
        case WSTRING:
        case WCSTRING:
            return static_cast<const wchar_t *>(m_value.p);
        case CHAR:
        case BOOL:
            return m_value.i == 0 ? L"false" : L"true";
        case WCHAR:
            return (const wchar_t *) &m_value.i;
        case UCHAR:
        case SHORT:
        case USHORT:
        case INT:
            return std::to_wstring(m_value.i);
        case UINT:
            return std::to_wstring(m_value.ui);
        case LONG:
            return std::to_wstring(m_value.l);
        case ULONG:
            return std::to_wstring(m_value.ul);
        case LLONG:
            return std::to_wstring(m_value.ll);
        case ULLONG:
            return std::to_wstring(m_value.ull);
        case FLOAT:
            return std::to_wstring(m_value.f);
        case DOUBLE:
            return std::to_wstring(m_value.d);
        case LDOUBLE:
            return std::to_wstring(m_value.ld);
        default:
            return D(def);
        }
    }

    bool variant::is_string() const
    {
        switch (m_type)
        {
        case STRING:
        case CSTRING:
            return true;
        default:
            return false;
        }
    }

    bool variant::is_wstring() const
    {
        switch (m_type)
        {
        case WSTRING:
        case WCSTRING:
            return true;
        default:
            return false;
        }
    }

    bool variant::is_numeric() const
    {
        switch (m_type)
        {
        case CHAR:
        case UCHAR:
        case WCHAR:
        case SHORT:
        case USHORT:
        case INT:
        case UINT:
        case LONG:
        case ULONG:
        case LLONG:
        case ULLONG:
            return true;
        default:
            return false;
        }
    }

    bool variant::is_real() const
    {
        switch (m_type)
        {
        case FLOAT:
        case DOUBLE:
        case LDOUBLE:
            return true;
        default:
            return false;
        }
    }

    int variant::to_int(int def) const
    {
        if (is_numeric() || is_real())
            return convert_numeric(def);

        if (is_string())
        {
            try
            {
                return stoi(static_cast<const char *>(m_value.p), NULL, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else if (is_wstring())
        {
            try
            {
                return wcstol(static_cast<const wchar_t *>(m_value.p), NULL, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else
        {
            return D(def);
        }
    }

    unsigned variant::to_uint(unsigned def) const
    {
        if (is_numeric() || is_real())
            return convert_numeric(def);

        if (is_string())
        {
            try
            {
                return stol(static_cast<const char *>(m_value.p), NULL, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else if (is_wstring())
        {
            try
            {
                return wcstoul(static_cast<const wchar_t *>(m_value.p), NULL, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else
        {
            return D(def);
        }
    }

    long variant::to_long(long def) const
    {
        if (is_numeric() || is_real())
        {
            return convert_numeric(def);
        }
        else if (is_string())
        {
            try
            {
                return stol(static_cast<const char *>(m_value.p), 0, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else if (is_wstring())
        {
            try
            {
                return wcstol(static_cast<const wchar_t *>(m_value.p), NULL, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else
        {
            return D(def);
        }
    }

    unsigned long variant::to_ulong(unsigned long def) const
    {
        if (is_numeric() || is_real())
        {
            return convert_numeric(def);
        }
        else if (is_string())
        {
            try
            {
                return stoul(static_cast<const char *>(m_value.p), 0, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else if (is_wstring())
        {
            try
            {
                return wcstoul(static_cast<const wchar_t *>(m_value.p), NULL, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else
        {
            return D(def);
        }
    }

    long long variant::to_llong(long long def) const
    {
        if (is_numeric() || is_real())
        {
            return convert_numeric(def);
        }
        else if (is_string())
        {
            try
            {
                return stoll(static_cast<const char *>(m_value.p), 0, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else if (is_wstring())
        {
            try
            {
                return wcstoll(static_cast<const wchar_t *>(m_value.p), NULL, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else
        {
            return D(def);
        }
    }

    unsigned long long variant::to_ullong(unsigned long long def) const
    {
        if (is_numeric() || is_real())
        {
            return convert_numeric(def);
        }
        else if (is_string())
        {
            try
            {
                return stoull(static_cast<const char *>(m_value.p), 0, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else if (is_wstring())
        {
            try
            {
                return wcstoull(static_cast<const wchar_t *>(m_value.p), NULL, BASE);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else
        {
            return D(def);
        }
    }

    double variant::to_double(double def) const
    {
        if (is_numeric() || is_real())
        {
            return convert_numeric(def);
        }
        else if (is_string())
        {
            try
            {
                return stod(static_cast<const char *>(m_value.p), 0);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else if (is_wstring())
        {
            try
            {
                return wcstod(static_cast<const wchar_t *>(m_value.p), NULL);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else
        {
            return D(def);
        }
    }


    bool variant::to_bool() const
    {
        switch (m_type)
        {
        case BOOL:
        case CHAR:
        case UCHAR:
        case WCHAR:
        case SHORT:
        case USHORT:
        case INT:
            return m_value.i != 0;
        case UINT:
            return m_value.ui != 0;
        case LONG:
            return m_value.l != 0;
        case ULONG:
            return m_value.ul != 0;
        case LLONG:
            return m_value.ll != 0;
        case ULLONG:
            return m_value.ull != 0;
        case FLOAT:
            return !isnan(m_value.f);
        case DOUBLE:
            return !isnan(m_value.d);
        case LDOUBLE:
            return !isnan(m_value.ld);
        case CSTRING:
        case STRING:
        {
            const char *temp = static_cast<const char *>(m_value.p);
            return temp && *temp;
        }
        case WCSTRING:
        case WSTRING:
        {
            const wchar_t *temp = static_cast<const wchar_t *>(m_value.p);
            return wcslen(temp) != 0;
        }
        case POINTER:
            return m_value.p != 0;
        default:
            return false;
        }
    }

    float variant::to_float(float def) const
    {
        if (is_numeric() || is_real())
        {
            return convert_numeric(def);
        }
        else if (is_string())
        {
            try
            {
                return stof(static_cast<const char *>(m_value.p), NULL);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else if (is_wstring())
        {
            try
            {
                return wcstof(static_cast<const wchar_t *>(m_value.p), NULL);
            }
            catch (const exception &e)
            {
                return D(def);
            }
        }
        else
        {
            return D(def);
        }
    }

    // for streams

    ostream &operator<<(ostream &stream, const variant &v)
    {
        stream << v.to_string();
        return stream;
    }

    // utility operators

    bool operator==(float f, const variant &v)
    {
        return f == v.to_float();
    }

    bool operator==(const wstring &str, const variant &v)
    {
        return str == v.to_wstring();
    }

    bool operator==(const string &str, const variant &v)
    {
        return str == v.to_string();
    }

    bool operator==(unsigned long long ull, const variant &v)
    {
        return ull == v.to_ullong();
    }

    bool operator==(long long ll, const variant &v)
    {
        return ll == v.to_llong();
    }

    bool operator==(long l, const variant &v)
    {
        return l == v.to_long();
    }

    bool operator==(int i, const variant &v)
    {
        return i == v.to_int();
    }

    bool operator==(unsigned ui, const variant &v)
    {
        return ui == v.to_uint();
    }

    bool operator==(unsigned long ul, const variant &v)
    {
        return ul == v.to_ulong();
    }

    bool operator==(bool b, const variant &v)
    {
        return b == v.to_bool();
    }

    bool operator==(double d, const variant &v)
    {
        return d == v.to_double();
    }

}

#endif
