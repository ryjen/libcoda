
#include <json.h>
#include <json_object.h>
#include <algorithm>
#include <cmath>
#include <string>

#include <bandit/bandit.h>
#include <unistd.h>
#include <fstream>
#include "array.h"
#include "exception.h"
#include "object.h"

using namespace coda;

using namespace bandit;

using namespace std;

using namespace snowhouse;

inline bool equalf(double x, double y, double absTol)
{
    return fabs(x - y) <= absTol * std::max(1.0, std::max(fabs(x), fabs(y)));
}

void test_iterator(const json::object &obj)
{
    for (auto &entry : obj) {
        Assert::That(entry.first.empty(), Equals(false));
        Assert::That(entry.second.size() == 0, Equals(true));
    }
}

go_bandit([]() {

    describe("json object", []() {
        it("is movable", []() {
            json::object obj;

            obj.set_int("i", 1234);

            json::object other(std::move(obj));

            Assert::That(obj.is_valid(), Equals(false));

            Assert::That(other.size(), Equals(1));
        });

        it("can be constructed with arguments", []() {
            std::string temp("lorum ipsum");

            json::object ss(temp);

            Assert::That(ss.is_string(), Equals(true));

            Assert::That(ss.to_string(), Equals("lorum ipsum"));

            json::object s("hello, world");

            Assert::That(s.is_string(), Equals(true));

            Assert::That(s.to_string(), Equals("hello, world"));
#ifdef JSON_C_EXTENDED
            json::object i64(12345678LL);

            Assert::That(i64.to_int64(), Equals(12345678LL));
#endif
            json::object i(32);

            Assert::That(i.to_int(), Equals(32));

            json::object b(true);

            Assert::That(b.to_bool(), Equals(true));

            json::object d(123.123);

            Assert::That(coda::almost_equal(d.to_double(), 123.123, 1), Equals(true));

            json::object c(d);

            Assert::That(c.is_double(), Equals(true));

            Assert::That(coda::almost_equal(c.to_double(), d.to_double(), 1), Equals(true));

        });

        it("is assignable", []() {
            json::object obj(1234);

            json::object other;

            other = obj;

            Assert::That(other.is_int(), Equals(true));

            Assert::That(other.to_int(), Equals(1234));
        });

        it("can be null", []() {
            json::object obj(nullptr);

            Assert::That(obj.is_null(), Equals(true));

            obj = 1234;

            Assert::That(obj.is_null(), Equals(false));

            const char *json = "{ \"key\": null }";

            obj.parse(json);

            Assert::That(obj.get("key").is_null(), Equals(true));
        });

        describe("implicit conversion", []() {
            it("to an int", []() {
                json::object obj("1234");

                int other = obj;

                Assert::That(other, Equals(1234));

            });
            it("to a double", []() {
                json::object obj("123.456");

                double other = obj;
                Assert::That(equalf(other, 123.456, 0.00001), Equals(true));
            });

            it("to a string", []() {
                json::object obj(12345);

                std::string other = obj;

                Assert::That(other, Equals("12345"));
            });
        });

        describe("json object iterator", []() {

            it("can iterator values", []() {
                json::object obj;

                obj.set_string("testa", "test string");

                obj.set_int("testb", 1234);

                obj.set_bool("testc", true);

                obj.set_double("testd", 1234.4321);

                json::object_iterator i = obj.begin();

                Assert::That(i, !Equals(obj.end()));

                Assert::That(i->first, Equals("testa"));

                Assert::That(i->second.is_string(), Equals(true));

                Assert::That(i->second.to_string(), Equals("test string"));

                i++;

                Assert::That(i->second.is_int(), Equals(true));

                Assert::That(i->second.to_int(), Equals(1234));

                i++;

                Assert::That(i->second.is_bool(), Equals(true));

                Assert::That(i->second.to_bool(), Equals(true));

                i++;

                Assert::That(i->second.is_double(), Equals(true));

                Assert::That(i->second.to_double(), Equals(1234.4321));

                test_iterator(obj);

            });

            it("is movable", []() {
                json::object obj;

                obj.set_string("testa", "test string");

                auto i = obj.begin();

                auto o = std::move(i);

                Assert::That(i.is_valid(), Equals(false));
                Assert::That(i->first.size(), Equals(0));

                Assert::That(o->first, Equals("testa"));
                Assert::That(o->second, Equals("test string"));
            });

            it("is copyable", []() {
                json::object obj;

                obj.set_int("i", 1234);

                auto i = obj.begin();

                json::object_iterator o(i);

                Assert::That(o->first, Equals(i->first));
                Assert::That(o->second, Equals(o->second));


                json::object_iterator j = obj.end();

                j = i;

                Assert::That(j->first, Equals(i->first));
                Assert::That(j->second, Equals(j->second));
            });

            it("can be incremented", []() {
                json::object obj;

                obj.set_int("a", 1234);
                obj.set_int("b", 4321);
                obj.set_string("c", "lorum ipsum");

                auto i = obj.begin();

                i += 2;

                Assert::That(i->first, Equals("c"));
                Assert::That(i->second, Equals("lorum ipsum"));

                i = obj.begin();

                auto j = (i + 2);

                Assert::That(j->first, Equals("c"));
                Assert::That(j->second, Equals("lorum ipsum"));
            });
        });

        it("can be constructed with an input stream", []() {
            ifstream file;

            file.open(ROOT_PATH "/object.test.json");

            if (!file.is_open()) file.open("object.test.json");

            Assert::That(file.is_open(), Equals(true));

            json::object obj(file);

            Assert::That(obj.get_int("var1"), Equals(1234));

            Assert::That(obj.get_string("var2"), Equals("test"));
        });

        it("can parse JSON", []() {
            const char *TESTVALUE =
                "{\"col1\":\"value1\",\"col2\":1234,\"col3\":123.321,\"col4\":true,\"col5\":[\"a1\",2,true],\"col6\":{"
                "\"col7\":true}}";

            json::object obj;

            bool rval = obj.parse(TESTVALUE);

            Assert::That(rval, Equals(true));

            Assert::That(obj.get_string("col1"), Equals("value1"));

            Assert::That(obj.get_int("col2"), Equals(1234));

            Assert::That(obj.get_double("col3"), Equals(123.321));

            Assert::That(obj.get_bool("col4"), Equals(true));

            Assert::That(obj.get_array("col5").size(), Equals(3));

            Assert::That(obj.get_array("col5").get(0).to_string(), Equals("a1"));

            Assert::That(obj.get("col6").get_bool("col7"), Equals(true));
#ifdef JSON_C_EXTENDED
            Assert::That(obj.get_int64("col2"), Equals(1234));
#endif
        });

        it("cannot be a json array", []() {
            json::object obj;

            json_object *temp = json_object_new_array();

            AssertThrows(json::exception, (json::object(temp)));

            json_object_put(temp);

            json::array array;

            array.add_int(1234);

            obj.set_array("a", array);

            // obj.set_string("s", "lorum ipsum");

            AssertThrows(json::exception, obj.get("a"));

            // AssertThrows(json::exception, obj.get_array("s"));
        });

        it("can remove properties", []() {
            json::object obj;

            obj.set_string("col1", "value1");

            Assert::That(obj.contains("col1"), Equals(true));

            obj.remove("col1");

            Assert::That(obj.contains("col1"), Equals(false));
        });

        it("has a size", []() {

            json::object obj;

            obj.set_int("i", 1234);

            obj.set_string("s", "ipsum");

            Assert::That(obj.size(), Equals(2));
        });

        it("can set properties", []() {
            json::object obj;

            obj.set_string("s", "lorum ipsum");

            obj.set_int("s", 1234);

            Assert::That(obj.get("s").is_int(), Equals(true));

            Assert::That(obj.get_int("s"), Equals(1234));
#ifdef JSON_C_EXTENDED
            obj.set_int64("i", 1234LL);

            Assert::That(obj.get_int64("i"), Equals(1234LL));
#endif
            json::array a;

            a.add_int(1234);
            a.add_string("ipsum");

            obj.set_array("a", a);

            Assert::That(obj.get_array("a").size(), Equals(2));
        });

        it("can set an sub object", []() {
            json::object obj(1234);

            json::object temp;

            temp.set("obj", obj);

            Assert::That(obj.to_int(), Equals(1234));

            Assert::That(temp.get_int("obj"), Equals(1234));
        });

        it("can set a null property", []() {
            json::object obj;

            obj.set_null("test");

            Assert::That(obj.get("test").type(), Equals(json_type_null));

            Assert::That(obj.get("test").is_null(), Equals(true));

            Assert::That(obj.get("test"), !Equals(obj));
        });

        it("has int property equality", []() {
            json::object obj;

            obj.set_int("i", 1234);

            json::object i(1234);

            Assert::That(i == obj.get("i"), Equals(true));

            obj.set_int("i", 4321);

            Assert::That(obj.get("i") != i, Equals(true));

            Assert::That(14321 != obj.get("i"), Equals(true));
        });

        it("has string property equality", []() {
            json::object obj;

            obj.set_string("s", "lorum ipsum");

            json::object s("lorum ipsum");

            Assert::That(obj.get("s"), Equals(s));

            Assert::That(string("lorum ipsum") == obj.get("s"), Equals(true));

            Assert::That(string("1234123") != obj.get("s"), Equals(true));
        });

        it("has bool property equality", []() {
            json::object obj;

            obj.set_bool("b", true);

            json::object b(true);

            Assert::That(obj.get("b"), Equals(b));

            Assert::That(true == obj.get("b"), Equals(true));

            Assert::That(true != obj.get("b"), Equals(false));
        });

        it("has double property equality", []() {
            json::object obj;

            obj.set_double("d", 123.321);

            json::object d(123.321);

            Assert::That(obj.get("d"), Equals(d));

            Assert::That(123.321 == obj.get("d"), Equals(true));

            Assert::That(321.123 != obj.get("d"), Equals(true));
        });

#ifdef JSON_C_EXTENDED
        it("has int64 property equality", []() {
            json::object obj;

            obj.set_int64("i64", 123456LL);

            json::object i64(123456LL);

            Assert::That(obj.get("i64"), Equals(i64));

            Assert::That(123456LL == obj.get("i64"), Equals(true));

            Assert::That(432343LL != obj.get("i64"), Equals(true));
        });
#endif

        it("doesn't have null property equality", []() {
            json::object obj;

            obj.set_null("n");

            Assert::That(obj.get("n"), !Equals(obj.get("n")));
        });

        it("can be primitive types", []() {
            json::object obj;

            obj.set_int("i", 1234);

#ifdef JSON_C_EXTENDED
            obj.set_int64("i64", 123456789LL);
#endif
            obj.set_bool("b", true);
            obj.set_double("d", 1234.1234);
            obj.set_string("s", "abcdef");

            int i = obj.get("i");

            Assert::That(i, Equals(1234));

#ifdef JSON_C_EXTENDED
            long long i64 = obj.get("i64");

            Assert::That(i64, Equals(123456789LL));
#endif

            bool b = obj.get("b");

            Assert::That(b, Equals(true));

            string s = obj.get("s");

            Assert::That(s, Equals("abcdef"));
        });

    });


});
