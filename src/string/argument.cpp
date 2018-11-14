#include "argument.h"
#include "util.h"

using namespace std;

namespace coda {
  argument operator"" _arg(const char *cstr, size_t len) {
    return argument(string(cstr, len));
  }

  argument::argument() noexcept {}

  argument::argument(const string &str) noexcept : str_(str) {}

  argument::~argument() noexcept {}

  argument::argument(const argument &other) noexcept : str_(other.str_) {}

  argument::argument(argument &&other) noexcept : str_(std::move(other.str_)) {}

  argument &argument::operator=(const argument &other) noexcept {
    if (this != &other) {
      str_ = other.str_;
    }
    return *this;
  }

  argument &argument::operator=(argument &&other) noexcept {
    if (this != &other) {
      str_ = std::move(other.str_);
    }
    return *this;
  }

  /**
   * gets the next argument.
   * example arguments:
   * "abc 1234"
   * 'abc 1234'
   * (abc 1234)
   * abc
   * 1234
   */
  size_t argument::next(string &arg) const {
    char cEnd;

    size_t pos = str_.find_first_not_of(' ');

    if (pos == string::npos) {
      return pos;
    }

    cEnd = ' ';

    if (str_[pos] == '\'' || str_[pos] == '"' || str_[pos] == '(') {
      if (str_[pos] == '(') {
        cEnd = ')';
        pos++;
      } else {
        cEnd = str_[pos++];
      }
    }

    while (pos < str_.length()) {
      if (str_[pos] == cEnd) {
        pos++;
        break;
      }

      arg += str_[pos++];
    }

    pos = str_.find_first_not_of(' ', pos);

    return pos;
  }

  string argument::peek() const {
    string arg;

    next(arg);

    return arg;
  }

  string argument::next() {
    string arg;

    auto pos = next(arg);

    if (pos == string::npos) {
      str_.clear();
    } else {
      str_ = str_.substr(pos);
    }

    return arg;
  }
  long argument::next_number() { return stol(next()); }
  double argument::next_real() { return stod(next()); }
  bool argument::next_bool() {
    string arg = next();
    return coda::equals(arg, "true") || coda::equals(arg, "yes") ||
           coda::equals(arg, "1");
  }

  argument::operator const string &() noexcept { return str_; }

  bool argument::empty() const noexcept { return str_.length() == 0; }

  size_t argument::length() const noexcept { return str_.length(); }

  string argument::to_string() const noexcept { return str_; }

  char argument::operator[](int index) const { return str_[index]; }

  bool argument::operator!() const noexcept { return empty(); }

  bool argument::equals(const string &arg, bool caseSensitive) const {
    return coda::equals(str_, arg, caseSensitive);
  }

  bool argument::prefix(const string &arg, bool caseSensitive) const {
    return coda::prefix(arg, str_, caseSensitive);
  }

  bool argument::operator==(const std::string &arg) const noexcept {
    return str_ == arg;
  }
  bool argument::operator!=(const std::string &arg) const noexcept {
    return str_ != arg;
  }
  bool argument::operator==(const char *const arg) const { return str_ == arg; }
  bool argument::operator!=(const char *const arg) const { return str_ != arg; }
  bool argument::operator==(const argument &arg) const noexcept {
    return str_ == arg.str_;
  }
  bool argument::operator!=(const argument &arg) const noexcept {
    return str_ != arg.str_;
  }
  bool operator==(const std::string &a1, const argument &a2) noexcept {
    return a1 == a2.to_string();
  }
  bool operator!=(const std::string &a1, const argument &a2) noexcept {
    return a1 != a2.to_string();
  }
  bool operator==(const char *const a1, const argument &a2) {
    return a1 == a2.to_string();
  }
  bool operator!=(const char *const a1, const argument &a2) {
    return a1 != a2.to_string();
  }
} // namespace coda
