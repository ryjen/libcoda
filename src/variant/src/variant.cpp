#ifndef RJ_VARIANT_H_

#include "variant.h"
#include <wchar.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <sstream>

using namespace std;

namespace rj
{
    const char *const variant::TYPE_NAMES[] = {"nulltype", "number", "unumber", "real", "binary", "string", "wstring", "char", "wchar", "bool"};

    variant::variant() : type_(NULLTYPE), num_(0)
    {
    }

    variant::variant(const nullptr_t &null) : type_(NULLTYPE), num_(0), size_(0)
    {
    }

    variant::variant(bool value) : type_(BOOL), num_(value), size_(sizeof(bool))
    {
    }

    variant::variant(char c) : type_(CHAR), num_(c), size_(sizeof(char))
    {
    }

    variant::variant(unsigned char uc) : type_(CHAR), unum_(uc), size_(sizeof(unsigned char))
    {
    }

    variant::variant(wchar_t wc) : type_(WCHAR), num_(wc), size_(sizeof(wchar_t))
    {
    }

    variant::variant(short s) : type_(NUMBER), num_(s), size_(sizeof(short))
    {
    }

    variant::variant(unsigned short us) : type_(UNUMBER), unum_(us), size_(sizeof(unsigned short))
    {
    }

    variant::variant(int i) : type_(NUMBER), num_(i), size_(sizeof(int))
    {
    }

    variant::variant(unsigned ui) : type_(UNUMBER), unum_(ui), size_(sizeof(unsigned))
    {
    }

    variant::variant(long l) : type_(NUMBER), num_(l), size_(sizeof(long))
    {
    }

    variant::variant(unsigned long ul) : type_(UNUMBER), unum_(ul), size_(sizeof(unsigned long))
    {
    }

    variant::variant(float f) : type_(REAL), real_(f), size_(sizeof(float))
    {
    }

    variant::variant(double d) : type_(REAL), real_(d), size_(sizeof(double))
    {
    }

    variant::variant(long double ld) : type_(REAL), real_(ld), size_(sizeof(long double))
    {
    }

    variant::variant(long long ll) : type_(NUMBER), num_(ll), size_(sizeof(long long))
    {
    }

    variant::variant(unsigned long long ull) : type_(UNUMBER), unum_(ull), size_(sizeof(unsigned long long))
    {
    }

    variant::variant(const char *str) : type_(STRING), str_(str == nullptr ? "" : str), size_(str == nullptr ? 0 : strlen(str))
    {
    }

    variant::variant(const wchar_t *str) : type_(WSTRING), wstr_(str == nullptr ? L"" : str), size_(str == nullptr ? 0 : wcslen(str))
    {
    }

    variant::variant(const string &str) : type_(STRING), str_(str), size_(str.size())
    {
    }

    variant::variant(const wstring &str) : type_(WSTRING), wstr_(str), size_(str.size())
    {
    }

    variant::variant(const binary &bin) : type_(BINARY), ptr_(bin), size_(bin.size())
    {
    }

    variant::variant(const std::shared_ptr<complex> &c) : type_(COMPLEX), compl_(c), size_(c->size())
    {
    }

    // copy constructor
    variant::variant(const variant &other) : type_(NULLTYPE), num_(0), size_(0)
    {
        copy_value(other);
    }

    variant::variant(variant &&other) : type_(NULLTYPE), num_(0), size_(0)
    {
        move_value(std::move(other));
    }

    variant &variant::operator=(const variant &other)
    {
        cleanup();
        return copy_value(other);
    }

    variant &variant::operator=(variant &&other)
    {
        cleanup();
        return move_value(std::move(other));
    }

    variant::~variant()
    {
        cleanup();
    }

    void variant::cleanup()
    {
        switch (type_) {
            // Fixes valgrind leaks
            case STRING:
                str_.~string();
                break;
            case WSTRING:
                wstr_.~wstring();
                break;
            case BINARY:
                ptr_.~binary();
                break;
            case COMPLEX:
                compl_.~shared_ptr<complex>();
            default:
                break;
        }
    }
    variant &variant::copy_value(const variant &other)
    {
        switch (other.type_) {
            case NUMBER:
            case NULLTYPE:
            case CHAR:
            case WCHAR:
            case BOOL:
                num_ = other.num_;
                break;
            case UNUMBER:
                unum_ = other.unum_;
                break;
            case REAL:
                real_ = other.real_;
                break;
            case STRING:
                new (&str_) string(other.str_);
                break;
            case WSTRING:
                new (&wstr_) wstring(other.wstr_);
                break;
            case BINARY:
                new (&ptr_) binary(other.ptr_);
                break;
            case COMPLEX:
                new (&compl_) std::shared_ptr<complex>(other.compl_);
                break;
        }

        type_ = other.type_;

        size_ = other.size_;

        return *this;
    }
    variant &variant::move_value(variant &&other)
    {
        switch (other.type_) {
            case NUMBER:
            case NULLTYPE:
            case CHAR:
            case WCHAR:
            case BOOL:
                num_ = other.num_;
                break;
            case UNUMBER:
                unum_ = other.unum_;
                break;
            case REAL:
                real_ = other.real_;
                break;
            case STRING:
                new (&str_) string(std::move(other.str_));
                break;
            case WSTRING:
                new (&wstr_) wstring(std::move(other.wstr_));
                break;
            case BINARY:
                new (&ptr_) binary(std::move(other.ptr_));
                break;
            case COMPLEX:
                new (&compl_) std::shared_ptr<complex>(std::move(other.compl_));
                break;
        }
        type_ = other.type_;
        size_ = other.size_;
        other.type_ = NULLTYPE;
        other.num_ = 0;
        return *this;
    }

    size_t variant::size() const
    {
        return size_;
    }

    variant::types variant::type() const
    {
        return type_;
    }

    std::string variant::type_name() const
    {
        return TYPE_NAMES[type_];
    }

    // operators
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

    variant::operator long double() const
    {
        return to_ldouble();
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

    variant::operator const wchar_t *() const
    {
        return to_wcstring();
    }

    variant::operator const char *() const
    {
        return to_cstring();
    }

    variant::operator char() const
    {
        return to_char();
    }

    variant::operator binary() const
    {
        return to_binary();
    }

    bool variant::operator==(const nullptr_t &other) const
    {
        return is_null();
    }

    bool variant::operator==(bool other) const
    {
        return to_bool() == other;
    }

    bool variant::operator==(float other) const
    {
        return to_float() == other;
    }

    bool variant::operator==(double other) const
    {
        return to_double() == other;
    }

    bool variant::operator==(long double other) const
    {
        return to_ldouble() == other;
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

    bool variant::operator==(const char *str) const
    {
        return to_string() == str;
    }

    bool variant::operator==(const wchar_t *str) const
    {
        return to_wstring() == str;
    }

    bool variant::operator==(const binary &bin) const
    {
        switch (type_) {
            case BINARY:
                return ptr_ == bin;
            default:
                return to_binary() == bin;
        }
    }

    bool variant::operator!=(const std::nullptr_t &t) const
    {
        return !operator==(t);
    }
    bool variant::operator!=(bool other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(float other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(double other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(long double other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(const std::wstring &other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(const std::string &other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(unsigned long long other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(long long other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(long other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(int other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(unsigned other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(unsigned long other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(const char *other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(const wchar_t *other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(const variant &other) const
    {
        return !operator==(other);
    }
    bool variant::operator!=(const binary &other) const
    {
        return !operator==(other);
    }

    bool variant::equals(const variant &value) const
    {
        if (type_ != value.type_) {
            return to_string() == value.to_string();
        }

        switch (type_) {
            case NUMBER:
            case CHAR:
            case WCHAR:
            case BOOL:
                return num_ == value.num_;
            case UNUMBER:
                return unum_ == value.unum_;
            case REAL:
                return real_ == value.real_;
            case STRING:
                return str_ == value.str_;
            case WSTRING:
                return wstr_ == value.wstr_;
            case BINARY:
                return ptr_ == value.ptr_;
            case COMPLEX:
                return compl_ == value.compl_;
            case NULLTYPE:
            default:
                return this == &value;
        }
    }

    bool variant::operator==(const variant &value) const
    {
        return equals(value);
    }

    bool variant::is_string() const
    {
        switch (type_) {
            case STRING:
                return true;
            default:
                return false;
        }
    }

    bool variant::is_wstring() const
    {
        switch (type_) {
            case WSTRING:
                return true;
            default:
                return false;
        }
    }

    bool variant::is_complex() const
    {
        return type_ == COMPLEX && compl_;
    }

    bool variant::is_numeric() const
    {
        switch (type_) {
            case NUMBER:
            case UNUMBER:
            case CHAR:
            case WCHAR:
            case BOOL:
            case REAL:
                return true;
            default:
                return false;
        }
    }

    bool variant::is_binary() const
    {
        switch (type_) {
            case BINARY:
                return true;
            default:
                return false;
        }
    }

    bool variant::is_real() const
    {
        switch (type_) {
            case REAL:
                return true;
            default:
                return false;
        }
    }

    bool variant::is_null() const
    {
        switch (type_) {
            case NULLTYPE:
                return true;
            default:
                return false;
        }
    }

    const void *variant::to_pointer() const
    {
        switch (type_) {
            case STRING:
                return str_.c_str();
            case WSTRING:
                return wstr_.c_str();
            case BINARY:
                return ptr_.value();
            case COMPLEX:
                return compl_->to_pointer();
            default:
                throw illegal_conversion();
        }
    }

    binary variant::to_binary() const
    {
        switch (type_) {
            case BINARY:
                return ptr_;
            case COMPLEX:
                return compl_->to_binary();
            case NULLTYPE:
                return binary();
            default:
                throw illegal_conversion();
        }
    }
    string variant::to_string(const string &def) const
    {
        try {
            return to_string();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }
    string variant::to_string() const
    {
        switch (type_) {
            case STRING:
                return str_;
            case CHAR: {
                static char buf[2] = {0};
                buf[0] = static_cast<char>(num_);
                buf[1] = 0;
                return buf;
            }
            case BOOL:
                return num_ == 0 ? "false" : "true";
            case NUMBER:
                return std::to_string(num_);
            case UNUMBER:
                return std::to_string(unum_);
            case REAL:
                return std::to_string(real_);
            case NULLTYPE:
                return "NULL";
            case BINARY:
                return ptr_.to_string();
            case COMPLEX:
                return compl_ ? compl_->to_string() : "NULL";
            default:
                throw illegal_conversion();
        }
    }
    const char *variant::to_cstring(const char *def) const
    {
        try {
            return to_cstring();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }

    const char *variant::to_cstring() const
    {
        switch (type_) {
            case STRING:
                return str_.c_str();
            case CHAR: {
                static char buf[2] = {0};
                buf[0] = static_cast<char>(num_);
                buf[1] = 0;
                return buf;
            }
            case NULLTYPE:
                return nullptr;
            case COMPLEX:
                return compl_->to_cstring();
            default:
                throw illegal_conversion();
        }
    }

    const wchar_t *variant::to_wcstring(const wchar_t *def) const
    {
        try {
            return to_wcstring();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }
    const wchar_t *variant::to_wcstring() const
    {
        switch (type_) {
            case WSTRING:
                return wstr_.c_str();
            case WCHAR: {
                static wchar_t buf[5];
                swprintf(buf, 2, L"%c", num_);
                return buf;
            }
            case NULLTYPE:
                return nullptr;
            case COMPLEX:
                return compl_->to_wcstring();
            default:
                throw illegal_conversion();
        }
    }

    wstring variant::to_wstring(const wstring &def) const
    {
        try {
            return to_wstring();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }

    wstring variant::to_wstring() const
    {
        switch (type_) {
            case WSTRING:
                return wstr_;
            case BOOL:
                return num_ == 0 ? L"false" : L"true";
            case WCHAR: {
                wchar_t buf[5];
                swprintf(buf, 2, L"%c", num_);
                return buf;
            }
            case NUMBER:
                return std::to_wstring(num_);
            case UNUMBER:
                return std::to_wstring(unum_);
            case REAL:
                return std::to_wstring(real_);
            case NULLTYPE:
                return L"NULL";
            case COMPLEX:
                return compl_->to_wstring();
            default:
                throw illegal_conversion();
        }
    }

    int variant::to_int() const
    {
        return convert_base<int, int>(stoi, stoi, BASE);
    }

    int variant::to_int(const int def) const
    {
        try {
            return to_int();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }

    unsigned variant::to_uint(const unsigned def) const
    {
        try {
            return to_uint();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }

    unsigned variant::to_uint() const
    {
        return convert_base<unsigned, unsigned long>(stoul, stoul, BASE);
    }

    long variant::to_long(const long def) const
    {
        try {
            return to_long();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }

    long variant::to_long() const
    {
        return convert_base<long, long>(stol, stol, BASE);
    }

    unsigned long variant::to_ulong(const unsigned long def) const
    {
        try {
            return to_ulong();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }

    unsigned long variant::to_ulong() const
    {
        return convert_base<unsigned long, unsigned long>(stoul, stoul, BASE);
    }

    long long variant::to_llong(const long long def) const
    {
        try {
            return to_llong();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }

    long long variant::to_llong() const
    {
        return convert_base<long long, long long>(stoll, stoll, BASE);
    }

    unsigned long long variant::to_ullong(const unsigned long long def) const
    {
        try {
            return to_ullong();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }
    unsigned long long variant::to_ullong() const
    {
        return convert_base<unsigned long long, unsigned long long>(stoull, stoull, BASE);
    }

    double variant::to_double(const double def) const
    {
        try {
            return to_double();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }

    double variant::to_double() const
    {
        return convert<double, double>(stod, stod);
    }

    long double variant::to_ldouble(const long double def) const
    {
        try {
            return to_ldouble();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }

    long double variant::to_ldouble() const
    {
        return convert<long double, long double>(stold, stold);
    }
    bool variant::to_bool() const
    {
        switch (type_) {
            case BOOL:
            case CHAR:
            case WCHAR:
            case NUMBER:
                return num_ != 0;
            case UNUMBER:
                return unum_ != 0;
            case REAL:
                return !isnan(real_);
            case STRING: {
                return str_ == "true" || str_ == "yes";
            }
            case WSTRING: {
                return wstr_ == L"true" || wstr_ == L"yes";
            }
            case BINARY:
                return ptr_.size() > 0 && ptr_.value() != nullptr;
            case COMPLEX:
                return compl_ && compl_->to_bool();
            default:
                return false;
        }
    }

    float variant::to_float(const float def) const
    {
        try {
            return to_float();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }

    float variant::to_float() const
    {
        return convert<float, float>(stof, stof);
    }

    char variant::to_char(const char def) const
    {
        try {
            return to_char();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }
    char variant::to_char() const
    {
        if (is_numeric() || is_real()) {
            return convert_numeric<char>();
        }

        if (is_string()) {
            if (str_.size() == 0) {
                return '\0';
            }

            return str_[0];
        }

        if (is_complex()) {
            return compl_->to_char();
        }

        throw illegal_conversion("no conversion found");
    }
    unsigned char variant::to_uchar(const unsigned char def) const
    {
        try {
            return to_uchar();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }
    unsigned char variant::to_uchar() const
    {
        if (is_numeric() || is_real()) {
            return convert_numeric<unsigned char>();
        }

        if (is_string()) {
            if (str_.size() == 0) {
                return '\0';
            }

            return str_[0];
        }

        if (is_complex()) {
            return compl_->to_uchar();
        }
        throw illegal_conversion();
    }
    wchar_t variant::to_wchar(const wchar_t def) const
    {
        try {
            return to_wchar();
        } catch (const illegal_conversion &e) {
            return def;
        }
    }
    wchar_t variant::to_wchar() const
    {
        if (is_numeric() || is_real()) {
            return convert_numeric<wchar_t>();
        }

        if (is_wstring()) {
            if (wstr_.size() == 0) {
                return L'\0';
            }

            return wstr_[0];
        }

        if (is_complex()) {
            return compl_->to_wchar();
        }

        throw illegal_conversion();
    }

    std::shared_ptr<variant::complex> variant::to_complex() const
    {
        if (!is_complex()) {
            throw illegal_conversion();
        }
        return compl_;
    }

    // for streams

    ostream &operator<<(ostream &stream, const variant &v)
    {
        stream << v.to_string();
        return stream;
    }

    ostream &operator<<(ostream &stream, const variant::complex &v)
    {
        stream << v.to_string();
        return stream;
    }

    // utility operators

    bool operator==(const nullptr_t &f, const variant &v)
    {
        return v.is_null();
    }

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

    bool operator==(long double d, const variant &v)
    {
        return d == v.to_ldouble();
    }

    bool operator==(const binary &bin, const variant &v)
    {
        return v == bin;
    }

    bool operator==(const variant::complex &c, const variant &v)
    {
        auto comp = v.to_complex();
        if (!comp) {
            return false;
        }
        return c.equals(*comp);
    }

    bool operator!=(const std::nullptr_t &n, const variant &v)
    {
        return !operator==(n, v);
    }
    bool operator!=(float f, const variant &v)
    {
        return !operator==(f, v);
    }
    bool operator!=(const std::wstring &str, const variant &v)
    {
        return !operator==(str, v);
    }
    bool operator!=(const std::string &str, const variant &v)
    {
        return !operator==(str, v);
    }
    bool operator!=(unsigned long long ull, const variant &v)
    {
        return !operator==(ull, v);
    }
    bool operator!=(long long ll, const variant &v)
    {
        return !operator==(ll, v);
    }
    bool operator!=(long l, const variant &v)
    {
        return !operator==(l, v);
    }
    bool operator!=(int i, const variant &v)
    {
        return !operator==(i, v);
    }
    bool operator!=(unsigned ui, const variant &v)
    {
        return !operator==(ui, v);
    }
    bool operator!=(unsigned long ul, const variant &v)
    {
        return !operator==(ul, v);
    }
    bool operator!=(bool b, const variant &v)
    {
        return !operator==(b, v);
    }
    bool operator!=(double d, const variant &v)
    {
        return !operator==(d, v);
    }
    bool operator!=(long double ld, const variant &v)
    {
        return !operator==(ld, v);
    }
    bool operator!=(const binary &bin, const variant &v)
    {
        return !operator==(bin, v);
    }

    bool operator!=(const variant::complex &c, const variant &v)
    {
        return !operator==(c, v);
    }

    // Custom type
    int variant::complex::to_int() const
    {
        throw illegal_conversion();
    }
    unsigned variant::complex::to_uint() const
    {
        throw illegal_conversion();
    }
    long variant::complex::to_long() const
    {
        throw illegal_conversion();
    }
    unsigned long variant::complex::to_ulong() const
    {
        throw illegal_conversion();
    }
    long long variant::complex::to_llong() const
    {
        throw illegal_conversion();
    }
    unsigned long long variant::complex::to_ullong() const
    {
        throw illegal_conversion();
    }
    double variant::complex::to_double() const
    {
        throw illegal_conversion();
    }
    long double variant::complex::to_ldouble() const
    {
        throw illegal_conversion();
    }
    bool variant::complex::to_bool() const
    {
        throw illegal_conversion();
    }
    float variant::complex::to_float() const
    {
        throw illegal_conversion();
    }
    const void *variant::complex::to_pointer() const
    {
        throw illegal_conversion();
    }
    binary variant::complex::to_binary() const
    {
        throw illegal_conversion();
    }
    char variant::complex::to_char() const
    {
        throw illegal_conversion();
    }
    unsigned char variant::complex::to_uchar() const
    {
        throw illegal_conversion();
    }
    wchar_t variant::complex::to_wchar() const
    {
        throw illegal_conversion();
    }
    string variant::complex::to_string() const
    {
        throw illegal_conversion();
    }
    const char *variant::complex::to_cstring() const
    {
        throw illegal_conversion();
    }
    const wchar_t *variant::complex::to_wcstring() const
    {
        throw illegal_conversion();
    }
    wstring variant::complex::to_wstring() const
    {
        throw illegal_conversion();
    }

    variant::complex::operator string() const
    {
        return to_string();
    }
    variant::complex::operator int() const
    {
        return to_int();
    }
    variant::complex::operator long() const
    {
        return to_long();
    }
    variant::complex::operator long long() const
    {
        return to_llong();
    }
    variant::complex::operator unsigned long() const
    {
        return to_ulong();
    }
    variant::complex::operator unsigned long long() const
    {
        return to_ullong();
    }
    variant::complex::operator double() const
    {
        return to_double();
    }
    variant::complex::operator long double() const
    {
        return to_ldouble();
    }
    variant::complex::operator float() const
    {
        return to_float();
    }
    variant::complex::operator bool() const
    {
        return to_bool();
    }
    variant::complex::operator wstring() const
    {
        return to_wstring();
    }
    variant::complex::operator unsigned() const
    {
        return to_uint();
    }
    variant::complex::operator char() const
    {
        return to_char();
    }
    variant::complex::operator unsigned char() const
    {
        return to_uchar();
    }
    variant::complex::operator wchar_t() const
    {
        return to_wchar();
    }
    variant::complex::operator const wchar_t *() const
    {
        return to_wcstring();
    }
    variant::complex::operator const char *() const
    {
        return to_cstring();
    }
    variant::complex::operator binary() const
    {
        return to_binary();
    }

    bool variant::complex::equals(const complex &other) const
    {
        return hashcode() == other.hashcode();
    }

    bool variant::complex::operator==(const variant::complex &other) const
    {
        return equals(other);
    }

    std::string to_string(const rj::variant &value)
    {
        return value.to_string();
    }

    string to_string(const variant::complex &value)
    {
        return value.to_string();
    }
}
#endif
