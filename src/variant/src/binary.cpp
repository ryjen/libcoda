#include "binary.h"
#include <cerrno>
#include <cstring>
#include <sstream>
#include <stdexcept>

namespace rj
{
    binary::binary() : val_(nullptr), sz_(0), alloc_(nullptr), copy_(nullptr), free_(nullptr), cmp_(nullptr)
    {
    }
    binary::binary(const void *p, size_t sz, alloc_fn construct, copy_fn copy, free_fn destroy, cmp_fn compare)
        : val_(nullptr), sz_(0), alloc_(construct), copy_(copy), free_(destroy), cmp_(compare)
    {
        copy_mem(p, sz, construct, copy);
    }
    binary::binary(const binary &p) : val_(p.val_), sz_(p.sz_), alloc_(p.alloc_), copy_(p.copy_), free_(p.free_), cmp_(p.cmp_)
    {
        copy_mem(p.val_, p.sz_, p.alloc_, p.copy_);
    }
    binary::binary(binary &&p) : val_(p.val_), sz_(p.sz_), alloc_(p.alloc_), copy_(p.copy_), free_(p.free_), cmp_(p.cmp_)
    {
        p.val_ = nullptr;
        p.sz_ = 0;
        p.alloc_ = nullptr;
        p.copy_ = nullptr;
        p.free_ = nullptr;
        p.cmp_ = nullptr;
    }
    binary::~binary()
    {
        if (val_ && free_) {
            free_(val_);
        }
    }
    binary &binary::operator=(const binary &other)
    {
        if (free_ && val_) {
            free_(val_);
        }
        val_ = other.val_;
        sz_ = other.sz_;
        alloc_ = other.alloc_;
        copy_ = other.copy_;
        free_ = other.free_;
        cmp_ = other.cmp_;
        copy_mem(other.val_, other.sz_, other.alloc_, other.copy_);
        return *this;
    }

    binary &binary::operator=(binary &&other)
    {
        val_ = other.val_;
        sz_ = other.sz_;
        alloc_ = other.alloc_;
        copy_ = other.copy_;
        free_ = other.free_;
        cmp_ = other.cmp_;
        other.val_ = nullptr;
        other.sz_ = 0;
        other.alloc_ = nullptr;
        other.copy_ = nullptr;
        other.free_ = nullptr;
        other.cmp_ = nullptr;
        return *this;
    }

    void binary::copy_mem(const void *p, size_t size, alloc_fn construct, copy_fn copy)
    {
        if (size > 0 && construct != nullptr) {
            val_ = construct(size);
            sz_ = size;
            if (val_ == nullptr) {
                throw std::bad_alloc();
            }
            if (p != nullptr && copy != nullptr) {
                copy(val_, p, size);
            } else {
                memset(val_, 0, size);
            }
        }
    }

    size_t binary::size() const
    {
        return sz_;
    }

    void *binary::value() const
    {
        return val_;
    }

    bool binary::is_null() const
    {
        return val_ == nullptr || sz_ == 0;
    }

    bool binary::is_transient() const
    {
        return free_ != nullptr;
    }

    std::string binary::to_string() const
    {
        if (val_ == nullptr || sz_ == 0) {
            return "0x0";
        }

        std::ostringstream os;
        os << *this;
        return os.str();
    }

    bool binary::operator==(const binary &p) const
    {
        return cmp_ && val_ && p.val_ && sz_ > 0 && cmp_(val_, p.val_, sz_) == 0;
    }

    bool binary::operator==(const void *p) const
    {
        return cmp_ && val_ && sz_ > 0 && p && cmp_(val_, p, sz_) == 0;
    }

    bool binary::operator==(const std::nullptr_t &null) const
    {
        return is_null();
    }

    std::ostream &operator<<(std::ostream &out, const binary &value)
    {
        out << std::hex << value.val_;
        return out;
    }

    bool operator==(const void *ptr, const rj::binary &p)
    {
        return p == ptr;
    }

    bool operator==(const std::nullptr_t &null, const rj::binary &bin)
    {
        return bin == null;
    }

    std::string to_string(const rj::binary &p)
    {
        return p.to_string();
    }
}
