#ifndef ARG3_VARIANT_H_

#include "variant.h"
#include <cstdlib>

namespace arg3
{

    variant::variant() :
        type_(INT), refcount_(NULL), value_(0)
    {}

    variant::variant(char c) :
        type_(CHAR), refcount_(NULL), value_(c)
    {}

    variant::variant(unsigned char uc) :
        type_(UCHAR), refcount_(NULL), value_(uc)
    {}

    variant::variant(wchar_t wc) :
        type_(WCHAR), refcount_(NULL), value_(wc)
    {}

    variant::variant(short s) :
        type_(SHORT), refcount_(NULL), value_(s)
    {}

    variant::variant(unsigned short us) :
        type_(USHORT), refcount_(NULL), value_(us)
    {}

    variant::variant(int i) :
        type_(INT), refcount_(NULL), value_(i)
    {}

    variant::variant(unsigned ui) :
        type_(UINT), refcount_(NULL), value_(ui)
    {}

    variant::variant(long l) :
        type_(LONG), refcount_(NULL), value_(l)
    {}

    variant::variant(unsigned long ul) :
        type_(ULONG), refcount_(NULL), value_(ul)
    {}

    variant::variant(float f) :
        type_(FLOAT), refcount_(NULL), value_(f)
    {}

    variant::variant(double d) :
        type_(DOUBLE), refcount_(NULL), value_(d)
    {}

    variant::variant(long double ld) :
        type_(LDOUBLE), refcount_(NULL), value_(ld)
    {}

    variant::variant(long long ll) :
        type_(LLONG), refcount_(NULL), value_(ll)
    {}

    variant::variant(unsigned long long ull) :
        type_(ULLONG), refcount_(NULL), value_(ull)
    {}

    variant::variant(void *p) :
        type_(POINTER), refcount_(NULL), value_(p)
    { }

    // for strings we initialize refcount and make a copy of the cstring

    variant::variant(const char *str) :
        type_(CSTRING), refcount_(new unsigned(0)), value_(strdup(str))
    {}

    variant::variant(const wchar_t *str) :
        type_(WCSTRING), refcount_(new unsigned(0)), value_(wcsdup(str))
    {}

    variant::variant(const string &str) :
        type_(STRING), refcount_(new unsigned(0)), value_(strdup(str.c_str()))
    {}

    variant::variant(const wstring &str) :
        type_(WSTRING), refcount_(new unsigned(0)), value_(wcsdup(str.c_str()))
    {}

    // copy constructor
    variant::variant(const variant &other) :
        type_(other.type_), refcount_(other.refcount_), value_(other.value_)
    {
        // update refcount
        if (refcount_)
            (*refcount_)++;
    }

    variant::variant(variant &&other) : type_(other.type_), refcount_(std::move(refcount_)), value_(std::move(other.value_))
    {
        other.refcount_ = NULL;
        value_.p = NULL;
    }

    variant &variant::operator=(const variant &other)
    {
        if (this != &other)
        {

            type_ = other.type_;

            value_ = other.value_;

            refcount_ = other.refcount_;

            // update refcount
            if (refcount_)
                (*refcount_)++;

        }
        return *this;
    }

    variant &variant::operator=(variant &&other)
    {
        if(this != &other)
        {
            type_ = std::move(other.type_);
            value_ = std::move(other.value_);
            refcount_ = std::move(other.refcount_);
            other.refcount_ = NULL;
            other.value_.p = NULL;
        }

        return *this;
    }

    variant::~variant()
    {
        // check refcounts to free a pointer
        if (refcount_)
        {
            // no references except this one
            if (*refcount_ == 0)
            {
                if(value_.p)
                    free(const_cast<void *>(value_.p));
                delete refcount_;
                refcount_ = NULL;
            }
            // decrement reference count
            else
            {
                (*refcount_)--;
            }
        }

    }

    int variant::type() const
    {
        return type_;
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
        switch (type_)
        {
        case CHAR:
        case UCHAR:
        case WCHAR:
        case SHORT:
        case USHORT:
        case INT:
            return value_.i == value.value_.i;
        case UINT:
            return value_.ui == value.value_.ui;
        case LONG:
            return value_.l == value.value_.l;
        case ULONG:
            return value_.ul == value.value_.ul;
        case LLONG:
            return value_.ll == value.value_.ll;
        case ULLONG:
            return value_.ull == value.value_.ull;
        case FLOAT:
            return value_.f == value.value_.f;
        case DOUBLE:
            return value_.d == value.value_.d;
        case LDOUBLE:
            return value_.ld == value.value_.ld;
        case POINTER:
            return value_.p == value.value_.p;
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
        switch (type_)
        {
        case STRING:
        case CSTRING:
            return static_cast<const char *>(value_.p);
        case CHAR:
            return (const char *) &value_.i;
        case BOOL:
            return value_.i == 0 ? "false" : "true";
        case WCHAR:
        case UCHAR:
        case SHORT:
        case USHORT:
        case INT:
            return std::to_string(value_.i);
        case UINT:
            return std::to_string(value_.ui);
        case LONG:
            return std::to_string(value_.l);
        case ULONG:
            return std::to_string(value_.ul);
        case LLONG:
            return std::to_string(value_.ll);
        case ULLONG:
            return std::to_string(value_.ull);
        case FLOAT:
            return std::to_string(value_.f);
        case DOUBLE:
            return std::to_string(value_.d);
        case LDOUBLE:
            return std::to_string(value_.ld);
        default:
        case WSTRING:
        case WCSTRING:
            return D(def);
        }
    }

    const char *variant::to_cstring(const char *def) const
    {
        switch (type_)
        {
        case STRING:
        case CSTRING:
            return static_cast<const char *>(value_.p);
        case CHAR:
            return (const char *) &value_.i;
        default:
            return D(def);
        }
    }

    const wchar_t *variant::to_wcstring(const wchar_t *def) const
    {
        switch (type_)
        {
        case WSTRING:
        case WCSTRING:
            return static_cast<const wchar_t *>(value_.p);
        case WCHAR:
            return (const wchar_t *) &value_.i;
        default:
            return D(def);
        }
    }

    wstring variant::to_wstring(const wstring &def) const
    {
        switch (type_)
        {
        case STRING:
        case CSTRING:
            return D(def);
        case WSTRING:
        case WCSTRING:
            return static_cast<const wchar_t *>(value_.p);
        case CHAR:
        case BOOL:
            return value_.i == 0 ? L"false" : L"true";
        case WCHAR:
            return (const wchar_t *) &value_.i;
        case UCHAR:
        case SHORT:
        case USHORT:
        case INT:
            return std::to_wstring(value_.i);
        case UINT:
            return std::to_wstring(value_.ui);
        case LONG:
            return std::to_wstring(value_.l);
        case ULONG:
            return std::to_wstring(value_.ul);
        case LLONG:
            return std::to_wstring(value_.ll);
        case ULLONG:
            return std::to_wstring(value_.ull);
        case FLOAT:
            return std::to_wstring(value_.f);
        case DOUBLE:
            return std::to_wstring(value_.d);
        case LDOUBLE:
            return std::to_wstring(value_.ld);
        default:
            return D(def);
        }
    }

    bool variant::is_string() const
    {
        switch (type_)
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
        switch (type_)
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
        switch (type_)
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
        switch (type_)
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
                return V(stoi(static_cast<const char *>(value_.p), NULL, BASE));
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
                return V(wcstol(static_cast<const wchar_t *>(value_.p), NULL, BASE));
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
                return V(stol(static_cast<const char *>(value_.p), NULL, BASE));
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
                return V(wcstoul(static_cast<const wchar_t *>(value_.p), NULL, BASE));
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
                return V(stol(static_cast<const char *>(value_.p), 0, BASE));
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
                return V(wcstol(static_cast<const wchar_t *>(value_.p), NULL, BASE));
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
                return V(stoul(static_cast<const char *>(value_.p), 0, BASE));
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
                return V(wcstoul(static_cast<const wchar_t *>(value_.p), NULL, BASE));
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
                return V(stoll(static_cast<const char *>(value_.p), 0, BASE));
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
                return V(wcstoll(static_cast<const wchar_t *>(value_.p), NULL, BASE));
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
                return V(stoull(static_cast<const char *>(value_.p), 0, BASE));
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
                return V(wcstoull(static_cast<const wchar_t *>(value_.p), NULL, BASE));
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
                return V(stod(static_cast<const char *>(value_.p), 0));
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
                return V(wcstod(static_cast<const wchar_t *>(value_.p), NULL));
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
        switch (type_)
        {
        case BOOL:
        case CHAR:
        case UCHAR:
        case WCHAR:
        case SHORT:
        case USHORT:
        case INT:
            return value_.i != 0;
        case UINT:
            return value_.ui != 0;
        case LONG:
            return value_.l != 0;
        case ULONG:
            return value_.ul != 0;
        case LLONG:
            return value_.ll != 0;
        case ULLONG:
            return value_.ull != 0;
        case FLOAT:
            return !isnan(value_.f);
        case DOUBLE:
            return !isnan(value_.d);
        case LDOUBLE:
            return !isnan(value_.ld);
        case CSTRING:
        case STRING:
        {
            const char *temp = static_cast<const char *>(value_.p);
            return temp && *temp;
        }
        case WCSTRING:
        case WSTRING:
        {
            const wchar_t *temp = static_cast<const wchar_t *>(value_.p);
            return wcslen(temp) != 0;
        }
        case POINTER:
            return value_.p != 0;
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
                return V(stof(static_cast<const char *>(value_.p), NULL));
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
                return V(wcstof(static_cast<const wchar_t *>(value_.p), NULL));
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
