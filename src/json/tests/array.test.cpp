#include <string>

#include "array.h"
#include "object.h"
#include <bandit/bandit.h>
#include <json.h>

using namespace coda;
using namespace bandit;
using namespace snowhouse;

go_bandit([]() {
  describe("json array", []() {
    it("is copyable", []() {
      json::array a;

      a.add_int(1234);

      json::array b(a);

      Assert::That(b.size(), Equals(a.size()));

      Assert::That(b.get(0), Equals(a.get(0)));
    });

    it("is movable", []() {
      json::array a;

      a.add_int(1234);

      json::array b(std::move(a));

      Assert::That(a.is_valid(), Equals(false));
      Assert::That(b.is_valid(), Equals(true));

      Assert::That(b.get_int(0), Equals(1234));
    });

    it("is copy assignable", []() {
      json::array a;
      a.add_int(1234);
      json::array b;
      b = a;
      Assert::That(a.size(), Equals(b.size()));
      Assert::That(b.get_int(0), Equals(1234));
    });

    it("is move assignable", []() {
      json::array a;
      a.add_int(1234);
      json::array b;
      b = std::move(a);
      Assert::That(a.is_valid(), Equals(false));
      Assert::That(b.is_valid(), Equals(true));
      Assert::That(b.get_int(0), Equals(1234));
    });

    describe("iterators", []() {
      json::array value;

      value.add_string("test");

      value.add_int(1234);

      value.add_double(123.321);

      value.add_bool(true);

      it("can iterate different values", [&value]() {
        auto i = value.begin();

        Assert::That(i->is_string(), Equals(true));

        Assert::That(i->to_string(), Equals("test"));

        i++;

        Assert::That(i->is_int(), Equals(true));

        Assert::That(i->to_int(), Equals(1234));

        ++i;

        Assert::That(i->is_double(), Equals(true));

        Assert::That(i->to_double(), Equals(123.321));

        i += 1;

        Assert::That(i->is_bool(), Equals(true));

        Assert::That(i->to_bool(), Equals(true));
      });

      it("can be copied", [&value]() {
        coda::json::array::iterator k = value.begin();
        auto i = ++value.begin();

        auto j(i);

        Assert::That(*i, Equals(*j));

        k = i;

        Assert::That(*i, Equals(*k));
      });

      it("can be moved", [&value]() {
        auto i(++value.begin());

        auto j = std::move(i);

        // Assert::That(i->is_valid(), Equals(false));
        Assert::That(j->to_int(), Equals(1234));
      });

      it("can be indexed", [&value]() {
        auto i = value.begin();

        Assert::That(i[2].is_double(), Equals(true));
        Assert::That(i[1].to_int(), Equals(1234));
      });

      it("can iterate more than one", [&value]() {
        auto i = value.begin();

        i += 2;

        Assert::That(i->is_double(), Equals(true));
        Assert::That(i->to_double(), Equals(123.321));

        i++;

        i -= 2;

        Assert::That(i->is_int(), Equals(true));
        Assert::That(i->to_int(), Equals(1234));

        i = value.begin();

        auto j = i + 2;

        Assert::That(j->is_double(), Equals(true));

        Assert::That(j->to_double(), Equals(123.321));

        j += 1;

        j = j - 2;

        Assert::That(j->is_int(), Equals(true));
        Assert::That(j->to_int(), Equals(1234));
      });

      it("can be const", [&value]() {
        const auto i = value.begin();

        Assert::That((*i).is_string(), Equals(true));

        const auto j(value.end() - 1);

        Assert::That((*j).is_bool(), Equals(true));
      });

      it("can reverse iterate", [&value]() {
        auto i = value.rbegin();

        i++;

        // TODO: figure out why this is failing
        // Assert::That(i->is_double(), Equals(true));

        const auto j = value.rbegin();

        // Assert::That(j->is_bool(), Equals(true));

        i = value.rend();

        i--;

        // Assert::That(i->is_string(), Equals(true));

        const auto k(value.rend() - 1);

        // Assert::That(k->is_string(), Equals(true));
      });

      it("can compare", [&value]() {
        auto i = value.begin();

        i += 2;

        Assert::That(i > value.begin(), Equals(true));
        Assert::That(i < value.end(), Equals(true));
        Assert::That(i != value.begin(), Equals(true));
        Assert::That(i >= value.begin(), Equals(true));
        Assert::That(i <= value.end(), Equals(true));

        auto j(i);

        Assert::That(i == j, Equals(true));
        Assert::That(i >= j, Equals(true));
        Assert::That(i <= j, Equals(true));
      });

      it("can decrement", [&value]() {
        auto i = value.end();

        i--;

        Assert::That(i->is_bool(), Equals(true));
        Assert::That(i->to_bool(), Equals(true));

        --i;

        Assert::That(i->is_double(), Equals(true));
        Assert::That(i->to_double(), Equals(123.321));

        i -= 1;

        Assert::That(i->is_int(), Equals(true));
        Assert::That(i->to_int(), Equals(1234));
      });
    });

    it("can add an int", []() {

    });

#ifdef JSON_C_EXTENDED
    it("can add int64 objects", []() {
      json::array a;

      a.add_int64(12341234LL);

      Assert::That(a.get_int64(0), Equals(12341234LL));
    });
#endif

    it("can add an object", []() {
      json::array a;

      json::object obj;

      obj.set_int("i", 1234);

      a.add(obj);

      Assert::That(a.size(), Equals(1));

      a.add(3, json::object());

      Assert::That(a.size(), Equals(4));

      Assert::That(a.get(3).is_null(), Equals(false));

      Assert::That(a.get(2).is_null(), Equals(true));
    });

    it("can handle a bad index", []() {
      json::array a;

      a.add_string("abced");

      AssertThrows(std::out_of_range, a.get(2));
      AssertThrows(std::out_of_range, a.get_string(2));
      AssertThrows(std::out_of_range, a.get_int(2));
      AssertThrows(std::out_of_range, a.get_int64(2));
      AssertThrows(std::out_of_range, a.get_array(2));
      AssertThrows(std::out_of_range, a.get_bool(2));
      AssertThrows(std::out_of_range, a.get_double(2));
    });

    it("can add an array", []() {
      json::array a;
      json::array o;

      o.add_double(1234.1234);

      a.add_array(o);

      Assert::That(a.get_array(0).size(), Equals(1));

      a.add_array(3, json::array());

      Assert::That(a.size(), Equals(4));

      Assert::That(a.get_array(3).size(), Equals(0));

      AssertThrows(std::exception, a.get_array(2));
    });

    it("can add a string", []() {
      json::array a;

      a.add_string("lorum ipsum");

      Assert::That(a.get_string(0), Equals("lorum ipsum"));

      a.add_string(3, "abcdef");

      Assert::That(a.size(), Equals(4));

      Assert::That(a.get_string(3), Equals("abcdef"));

      Assert::That(a.get_string(2), Equals(""));
    });

    it("can add a double", []() {
      json::array a;

      a.add_double(1234.4321);

      Assert::That(a.get_double(0), Equals(1234.4321));

      a.add_double(3, 432.321);

      Assert::That(a.size(), Equals(4));

      Assert::That(a.get_double(3), Equals(432.321));

      Assert::That(a.get_double(2), Equals(0.0));
    });

    it("can add an int", []() {
      json::array a;

      a.add_int(1234);

      a.add_int(3, 4321);

      Assert::That(a.size(), Equals(4));

      Assert::That(a.get_int(0), Equals(1234));

      Assert::That(a.get_int(3), Equals(4321));

      Assert::That(a.get_int(2), Equals(0));
    });
#ifdef JSON_C_EXTENDED
    it("can add an int64", []() {
      json::array a;

      a.add_int64(1234);

      a.add_int64(3, 4321);

      Assert::That(a.size(), Equals(4));

      Assert::That(a.get_int64(0), Equals(1234));

      Assert::That(a.get_int64(3), Equals(4321));

      Assert::That(a.get_int64(2), Equals(0));
    });
#endif

    it("can be empty", []() {
      json::array a;

      Assert::That(a.empty(), Equals(true));

      a.add_int(1234);

      Assert::That(a.empty(), Equals(false));
    });

    it("can compare", []() {
      json::array a;

      a.add_int(1234);

      Assert::That(a == a, Equals(true));

      auto b(a);

      Assert::That(b == a, Equals(true));

      json::array c;

      Assert::That(a != c, Equals(true));
    });

    it("can be indexed", []() {
      json::array a;

      a.add_string("abc");

      a.add_int(1234);

      Assert::That(a[0].to_string(), Equals("abc"));

      AssertThrows(std::out_of_range, a[4]);
    });

    it("can add a bool", []() {
      json::array a;

      a.add_bool(true);

      a.add_bool(3, false);

      Assert::That(a.size(), Equals(4));

      Assert::That(a.get_bool(0), Equals(true));

      Assert::That(a.get_bool(3), Equals(false));

      Assert::That(a.get_bool(2), Equals(false));
    });

    it("can add multiple objects", []() {
      json::array a;

      a.add_int(1234);

      a.add_string("abcdef");

      Assert::That(a.size(), Equals(2));

      Assert::That(a.front().is_int(), Equals(true));

      Assert::That(a.back().is_string(), Equals(true));
    });
  });
});
