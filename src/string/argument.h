#ifndef CODA_ARGUMENT_H_
#define CODA_ARGUMENT_H_

#include <string>

namespace coda {
  /*
   * basically a string tokenizer thats aware of quotes/parenthesis
   */
  class argument {
    private:
    std::string str_;

    protected:
    size_t next(std::string &) const;

    public:
    argument(const std::string &) noexcept;
    argument() noexcept;
    argument(const argument &other) noexcept;
    argument(argument &&other) noexcept;
    argument &operator=(const argument &other) noexcept;
    argument &operator=(argument &&other) noexcept;
    ~argument() noexcept;

    //! peek at the next argument
    /*!
     * @returns string the next available argument
     *
     * Notes: will not remove the argument from the original
     */
    std::string peek() const;
    //! gets the next argument
    /*!
     * @returns string the next argument
     *
     * Notes: will remove the argument from the original
     */
    std::string next();

    long next_number();
    double next_real();
    bool next_bool();
    operator const std::string &() noexcept;
    bool empty() const noexcept;
    bool operator!() const noexcept;
    char operator[](int) const;
    size_t length() const noexcept;
    std::string to_string() const noexcept;

    bool equals(const std::string &arg, bool caseSensitive = false) const;
    bool prefix(const std::string &arg, bool caseSensitive = false) const;

    bool operator==(const std::string &arg) const noexcept;
    bool operator!=(const std::string &arg) const noexcept;
    bool operator==(const char *const arg) const;
    bool operator!=(const char *const arg) const;
    bool operator==(const argument &arg) const noexcept;
    bool operator!=(const argument &arg) const noexcept;
  };

  argument operator"" _arg(const char *cstr, size_t len);

  bool operator==(const std::string &a1, const argument &a2) noexcept;
  bool operator!=(const std::string &a1, const argument &a2) noexcept;
  bool operator==(const char *const a1, const argument &a2);
  bool operator!=(const char *const a1, const argument &a2);
} // namespace coda

#endif
