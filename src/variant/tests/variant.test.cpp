#include <bandit/bandit.h>
#include <functional>
#include "variant.h"

using namespace bandit;

using namespace std;

using namespace rj;

class complex_val : public variant::complex
{
   private:
    int val_;

   public:
    complex_val(int val) : val_(val)
    {
    }
    int to_int() const
    {
        return val_;
    }
    long to_long() const
    {
        return val_;
    }
    std::string to_string() const
    {
        return std::to_string(val_);
    }

    size_t size() const
    {
        return sizeof(int);
    }
    long hashcode() const
    {
        std::size_t h1 = std::hash<int>()(val_);
        return h1;
    }
};

go_bandit([]() {

    describe("a variant value", []() {

        describe("constructing", [] {

            it("is an int", []() {
                variant v(20);

                Assert::That(v, Equals(20));

                Assert::That(v, Equals("20"));

                Assert::That(v.to_wstring(), Equals(wstring(L"20")));
            });

            it("is an unsigned int", []() {
                variant v = 123U;

                Assert::That(v, Equals(123U));

                unsigned u = v;

                Assert::That(u, Equals(123U));

                Assert::That(v.to_wstring(), Equals(wstring(L"123")));
            });

            it("is a long", []() {
                auto v = variant(456L);

                Assert::That(v, Equals(456L));

                Assert::That(v.is_null(), IsFalse());
            });

            it("is an unsigned long", []() {
                variant v = 789UL;

                Assert::That(v, Equals(789UL));

                unsigned long ul = v;

                Assert::That(ul, Equals(789UL));
            });

            it("is a long long", []() {
                variant v = 1234LL;

                Assert::That(v, Equals(1234LL));

                long long l = v;

                Assert::That(1234LL, Equals(l));
            });

            it("is an unsigned long long", []() {
                variant v = 1234ULL;

                Assert::That(v, Equals(1234ULL));

                unsigned long long ull = v;

                Assert::That(ull, Equals(1234ULL));
            });

            it("is a string", []() {
                variant v = "testing1234";

                Assert::That(v.is_null(), IsFalse());

                Assert::That(v, Equals("testing1234"));
            });

            it("can be a wide string", []() {
                wstring temp = L"hello, world";

                variant v = temp;

                Assert::That(v, Equals(temp));
            });

            it("is a wide character string", []() {
                variant v = L"123testing";

                Assert::That(v, Equals(wstring(L"123testing")));

                Assert::That(v.to_int(0), Equals(123));

                wstring ws = v;

                Assert::That(ws, Equals(wstring(L"123testing")));

                v = L"asdfbjaksd";

                Assert::That(v.to_int(-1), Equals(-1));
            });

            it("is NULL", []() {
                variant v;

                Assert::That(v == nullptr, IsTrue());

                AssertThrows(illegal_conversion, v.to_int());

                Assert::That(v.to_bool(), IsFalse());

                Assert::That(v.to_wstring() == L"NULL", IsTrue());
            });

            it("is a boolean", []() {
                variant v = nullptr;

                Assert::That(!v, IsTrue());

                v = "1234";

                Assert::That(!v, IsTrue());

                v = "true";

                Assert::That(v.to_bool(), IsTrue());

                variant f(false);

                variant t(true);

                Assert::That(t.to_bool(), IsTrue());

                Assert::That(t.to_string(), Equals("true"));

                Assert::That(f.to_string(), Equals("false"));

                Assert::That(t.to_wstring(), Equals(wstring(L"true")));

            });

            it("is a char", []() {
                variant v = 'c';

                Assert::That(v, Equals('c'));

                Assert::That(v, Equals(99));

                Assert::That(v, Equals("c"));

                char c = v;

                Assert::That(c, Equals('c'));

                Assert::That(v.to_cstring(), Equals("c"));
            });

            it("is an unsigned char", []() {
                unsigned char c = 255;

                variant v = c;

                unsigned char other = 255;

                Assert::That(v.to_uchar(), Equals(other));

                Assert::That(v.to_uchar(128), Equals(other));

                AssertThrows(illegal_conversion, v.to_char());

                Assert::That(v.to_char('~'), Equals('~'));
            });

            it("is a wide character", []() {
                wchar_t wc = L'c';

                variant v = wc;

                Assert::That(v, Equals(L'c'));

                Assert::That(!wcscmp(v.to_wcstring(), L"c"), IsTrue());

                Assert::That(v.to_wstring(), Equals(wstring(L"c")));

            });

            it("is a character array", []() {
                const char* temp = "hello, world";

                variant v = temp;

                Assert::That(!strcmp(temp, v), IsTrue());

                temp = v;

                Assert::That(!strcmp("hello, world", temp), IsTrue());

                Assert::That(!wcscmp(v.to_wcstring(L"nah"), L"nah"), IsTrue());
            });

            it("is a wide character array", []() {
                wchar_t* temp = wcsdup(L"Hello");

                variant v(temp);

                Assert::That(!wcscmp(v, temp), IsTrue());

                free(temp);
            });

            it("is a short", []() {
                short s = 3768;

                variant v = s;

                short test = 3768;

                Assert::That(v, Equals(test));
            });

            it("is a double", []() {
                double s = 32768.1234;

                variant v = s;

                Assert::That(v, Equals(32768.1234));
            });

            it("is an unsigned short", []() {
                unsigned short s = 12341;

                variant v = s;

                unsigned short test = 12341;

                Assert::That(v, Equals(test));
            });

            it("is a float", []() {
                float f = 123.1234f;

                variant v = f;

                Assert::That(v.is_real(), IsTrue());

                Assert::That(v, Equals(123.1234f));

                f = v;

                Assert::That(f, Equals(123.1234f));

                Assert::That(v.to_wstring(), Equals(std::to_wstring(123.1234f)));
            });

            it("is a long double", []() {

                long double ld = 123123.12341234L;

                variant v = ld;

                Assert::That(v.is_real(), IsTrue());

                Assert::That(v.to_ldouble(), Equals(ld));

                ld = v.to_ldouble();

                Assert::That(ld, Equals(123123.12341234L));
            });

            it("is a complex type", []() {
                auto comp = make_shared<complex_val>(1234);

                variant v(comp);

                Assert::That(v.is_complex(), IsTrue());

                auto temp = v.to_complex();

                Assert::That(*temp, Equals(*comp));

            });
        });
        describe("casting", []() {
            variant v = "1234.1234";

            it("is an int", [&v]() {
                int i = v;

                Assert::That(i, Equals(1234));
            });
            it("is a long", [&v]() {
                long l = v;

                Assert::That(l, Equals(1234));
            });

            it("is a double", [&v]() {
                double d = v;

                Assert::That(d, Equals(1234.1234));
            });

            it("is a long double", [&v]() {
                long double d = v;

                Assert::That(d, Equals(1234.1234L));
            });

            it("is a string", [&v]() {
                string s = v;

                Assert::That(s, Equals("1234.1234"));
            });

            it("is a boolean", []() {
                bool b = variant("true");

                Assert::That(b, IsTrue());
            });

            it("is a binary", []() {
                void* data = malloc(24);

                binary b = variant(binary(data, 24));

                free(data);

                Assert::That(b.size(), Equals(24U));
                Assert::That(b.value() != nullptr, IsTrue());

            });

            it("is a complex type", []() {
                auto comp = make_shared<complex_val>(1234);

                variant v(comp);

                int i = v;

                Assert::That(i, Equals(1234));

            });
        });

        describe("string conversion", [] {
            variant v = "1234";

            it("is a long", [&v]() {
                Assert::That(v, Equals(1234L));

                v = 12342.3412343;

                Assert::That(v, Equals(12342L));

                v = "asasdlfknalskdnf";

                AssertThrows(illegal_conversion, v.to_long());

                Assert::That(v.to_long(-1), Equals(-1));

                v = L"1234asdfasdf";

                Assert::That(v.to_long(-1), Equals(1234));

                v = L"asdfkjdns";

                Assert::That(v.to_long(-1), Equals(-1));
            });

            it("is an unsigned long", [&v]() {

                v = "1234";

                Assert::That(v.to_ulong(0), Equals(1234UL));

                v = L"1234";

                Assert::That(v.to_ulong(0), Equals(1234UL));

                v = "asdfasdf";

                Assert::That(v.to_ulong(0), Equals(0UL));

                v = L"asdfasdkj2ewe";

                Assert::That(v.to_ulong(0), Equals(0UL));
            });

            it("is a long long", [&v]() {

                v = "1234";

                Assert::That(v.to_llong(-1), Equals(1234));

                v = L"1234";

                Assert::That(v.to_llong(-1), Equals(1234));

                v = "asdf1234";

                Assert::That(v.to_llong(-1), Equals(-1));

                v = L"asdfasdfa123";

                Assert::That(v.to_llong(-1), Equals(-1));

                v = nullptr;

                Assert::That(v.to_llong(-1), Equals(-1));
            });

            it("is a double", [&v]() {

                v = "1234.1234";

                Assert::That(v.to_double(-1), Equals(1234.1234));

                v = L"1234.1234";

                Assert::That(v.to_double(-1), Equals(1234.1234));

                v = "asdf1234";

                AssertThrows(illegal_conversion, v.to_double());

                v = L"asdfasdfa123";

                AssertThrows(illegal_conversion, v.to_double());

                v = nullptr;

                Assert::That(v.to_double(-1), Equals(-1));
            });

            it("is a long double", [&v]() {

                v = "1234.1234";

                Assert::That(v.to_ldouble(-1), Equals(1234.1234L));

                v = L"1234.1234";

                Assert::That(v.to_ldouble(-1), Equals(1234.1234L));

                v = "asdf1234";

                Assert::That(v.to_ldouble(-1), Equals(-1));

                v = L"asdfasdfa123";

                AssertThrows(illegal_conversion, v.to_ldouble());

                v = nullptr;

                Assert::That(v.to_ldouble(-1), Equals(-1));
            });

            it("is an unsigned long long", [&v]() {

                v = "1234";

                Assert::That(v.to_ullong(0), Equals(1234UL));

                v = L"1234";

                Assert::That(v.to_ullong(0), Equals(1234UL));

                v = "asdf1234";

                Assert::That(v.to_ullong(0), Equals(0UL));

                v = L"asdfasdfa123";

                Assert::That(v.to_ullong(0), Equals(0UL));

                v = nullptr;

                Assert::That(v.to_ullong(0), Equals(0UL));
            });

            it("is an unsigned int", [&v]() {
                v = "1234";

                Assert::That(v.to_uint(0), Equals(1234UL));

                v = "asdfasdf";

                Assert::That(v.to_uint(0), Equals(0UL));

                v = L"1234asdf";

                Assert::That(v.to_uint(0), Equals(1234UL));

                v = L"Aknasdfkjh";

                Assert::That(v.to_uint(0), Equals(0UL));

                v = nullptr;
                AssertThrows(illegal_conversion, v.to_uint());

                Assert::That(v.to_uint(0), Equals(0UL));
            });

            it("is an int", [&v]() {
                v = "1234";

                Assert::That(v.to_int(), Equals(1234));

                v = "1234asdb";

                Assert::That(v.to_int(), Equals(1234));

                v = "asdf1234";

                AssertThrows(illegal_conversion, v.to_int());

                Assert::That(v.to_int(-1), Equals(-1));

                v = "1234129837410928374109283741029837410293847123412341235436574567845765";

                AssertThrows(illegal_conversion, v.to_int());

                Assert::That(v.to_int(-1), Equals(-1));
            });

            it("is not a wide string", [&v]() {
                v = L"12341234";

                Assert::That(v.to_string("nope"), Equals("nope"));

                Assert::That(v.to_cstring("uhh"), Equals("uhh"));
            });
        });

        it("can be contained in a map", []() {
            map<string, variant> container;

            container["test1"] = 1234;
            container["test2"] = "123.43";
            container["test3"] = true;

            Assert::That(container["test1"], Equals("1234"));
            Assert::That(container["test2"], Equals(123.43f));
            Assert::That(container["test3"], IsTrue());

        });


        it("can be different number types", []() {
            variant v = 1234;

            Assert::That(v.to_string(), Equals("1234"));

            Assert::That(v.to_int(), Equals(1234));

            Assert::That(v.to_long(), Equals(1234));

            Assert::That(v.to_bool(), IsTrue());

            Assert::That(v.to_float(), Equals(1234.0));

            Assert::That(v.to_float(0.11), Equals(1234.0));

            v = "test";

            Assert::That(v.is_string(), IsTrue());

            AssertThrows(illegal_conversion, v.to_int());

            Assert::That(v.to_int(-1), Equals(-1));

            Assert::That(v.to_float(0.5), Equals(0.5));

            v = numeric_limits<unsigned long long>::max();

            Assert::That(v.to_int(-1), Equals(-1));
        });

        it("can detect integer bases", []() {
            variant v = "0x7B";

            Assert::That(v.to_string(), Equals("0x7B"));
            Assert::That(v.to_int(), Equals(123));

            v = "0173";

            Assert::That(v.to_long(), Equals(123));
        });

        it("can hold binary", []() {

            int* p = (int*)calloc(2, sizeof(int));

            *p = 1;
            *(p + 1) = 2;

            variant v(binary(p, sizeof(int) * 2));

            int* temp = (int*)v.to_pointer();

            Assert::That(*temp, Equals(1));

            Assert::That(*(temp + 1), Equals(2));

            free(p);
        });

        describe("copying", []() {
            it("can copy itself", [] {
                string str = "1234123";

                variant v = str;

                {
                    variant t(v);

                    Assert::That(t.is_string(), IsTrue());

                    Assert::That(t.to_string(), Equals(v));
                }

                Assert::That(v, Equals(str));
            });

            it("can copy an int", []() {
                variant v = 1234;

                variant v2(v);

                Assert::That(v2 == 1234, IsTrue());
            });

            it("can copy a float", []() {
                variant v = 1234.1234;

                variant v2(v);

                Assert::That(v2 == 1234.1234, IsTrue());
            });

            it("can copy a wide string", []() {
                variant v = L"test";

                variant v2(v);

                Assert::That(v2 == L"test", IsTrue());
            });

            it("can copy a complex type", []() {
                variant v(make_shared<complex_val>(1234));

                variant v2(v);

                Assert::That(v2.to_int(), Equals(1234));
            });

        });

        describe("assigning", []() {

            variant v = "1234";

            it("can assign another variant", [&v]() {
                variant o;

                o = v;

                Assert::That(o.to_string(), Equals(v));

            });

            it("can assign an int", [&v]() {
                v = 20;

                Assert::That(v, Equals(20));
            });

            it("can assign a string", [&v]() {
                string temp = "hello, world";

                v = temp;

                Assert::That(temp, Equals(v));
            });

        });

        it("can move", []() {
            variant v = "32194905";

            variant t = std::move(v);

            Assert::That(t, Equals("32194905"));

            Assert::That(v.is_null(), IsTrue());
        });

        it("knows its dynamic size", []() {
            variant v = 123457;

            Assert::That(v.size(), Equals(sizeof(int)));

            v = L"12345";

            Assert::That(v.size(), Equals(5U));

            int i = 55555;

            v = variant(binary(&i, sizeof(int)));

            Assert::That(v.size(), Equals(sizeof(int)));
        });

        describe("equality", []() {
            variant v, other;

            it("has equality with bool", [&v, &other]() {
                v = "true";

                Assert::That(v == true, IsTrue());

                Assert::That(v != true, IsFalse());
                Assert::That(true != v, IsFalse());

                v = "asdfasdf";

                Assert::That(v == true, IsFalse());

                Assert::That(v != true, IsTrue());
            });

            it("has equality with float", [&v, &other]() {
                v = 123.1234f;

                Assert::That(v == 123.1234f, IsTrue());

                Assert::That(v == std::to_string(123.1234f), IsTrue());

                Assert::That(v != 321.321f, IsTrue());

                Assert::That(321.321f != v, IsTrue());

                Assert::That(v.equals(123.1234f), IsTrue());
            });

            it("has equality with double", [&v, &other]() {
                v = 321.321;

                Assert::That(v == 321.321, IsTrue());

                Assert::That(v == std::to_string(321.321), IsTrue());

                Assert::That(v != 123.123, IsTrue());

                Assert::That(123.123 != v, IsTrue());

                Assert::That(v.equals(321.321), IsTrue());
            });

            it("has equality with long double", [&v, &other]() {
                long double ld = 234.432L;

                v = ld;

                Assert::That(v == ld, IsTrue());

                Assert::That(ld == v, IsTrue());

                long double ld2 = 32234.432L;

                Assert::That(v != ld2, IsTrue());

                Assert::That(ld2 != v, IsTrue());

                Assert::That(v == std::to_string(ld), IsTrue());

                Assert::That(v.equals(234.432L), IsTrue());

            });

            it("has equality with wstring", [&v, &other]() {
                v = wstring(L"Hello, world");

                Assert::That(v == wstring(L"Hello, world"), IsTrue());

                Assert::That(v != wstring(L"world, hello"), IsTrue());

                Assert::That(wstring(L"world, hello") != v, IsTrue());

                Assert::That(v.equals(wstring(L"Hello, world")), IsTrue());
            });

            it("has equality with numerical types", [&v, &other]() {
                v = 1234321;

                Assert::That(v == 1234321ULL, IsTrue());

                Assert::That(1234321ULL != v, IsFalse());

                Assert::That(v == 1234321LL, IsTrue());

                Assert::That(1234321LL != v, IsFalse());

                Assert::That(v == 1234321L, IsTrue());

                Assert::That(1234321L != v, IsFalse());

                Assert::That(v == 1234321, IsTrue());

                Assert::That(1234321 != v, IsFalse());

                Assert::That(v == 1234321U, IsTrue());

                Assert::That(1234321U != v, IsFalse());

                Assert::That(v == 1234321UL, IsTrue());

                Assert::That(1234321UL != v, IsFalse());
            });

            it("has equality with itself", []() {
                variant v = "1234";

                variant other = "1234";

                Assert::That(v == other, IsTrue());
            });

            it("has equality with character array", []() {
                char buf[101] = {0};
                strncpy(buf, "hello, world", 100);

                variant v = buf;

                Assert::That(v == buf, IsTrue());
            });

            it("has equality with a wide character array", []() {
                wchar_t buf[101] = {0};
                wcsncpy(buf, L"hello, world", 100);

                variant v = buf;

                Assert::That(v == buf, IsTrue());
            });

            it("has equality with strings", []() {
                variant v = "hello, world";

                Assert::That(v == string("hello, world"), IsTrue());

                Assert::That(v != string("world, hello"), IsTrue());

                Assert::That(v.equals("hello, world"), IsTrue());
            });

            it("has equality with unsigned long long", []() {
                unsigned long long l = 12341234ULL;

                variant v = l;

                Assert::That(v == l, IsTrue());

                Assert::That(v != 43214321ULL, IsTrue());
            });

            it("has equality with long long", []() {
                long long l = 1234123LL;

                variant v = l;

                Assert::That(v == l, IsTrue());

                Assert::That(v != 143930943LL, IsTrue());
            });

            it("has equality with long", []() {
                variant v = 123412L;

                Assert::That(v == 123412L, IsTrue());

                Assert::That(v != 432121L, IsTrue());
            });

            it("has equality with int", []() {
                variant v = 1234;

                Assert::That(v == 1234, IsTrue());

                Assert::That(v != 123232, IsTrue());

                Assert::That(v.equals(1234), IsTrue());
            });

            it("has equality with unsigned int", []() {
                variant v = 1234U;

                Assert::That(v == 1234U, IsTrue());

                Assert::That(v != 4321U, IsTrue());

                Assert::That(v.equals(1234U), IsTrue());
            });

            it("has equality with unsigned long", [] {
                variant v = 1234UL;

                Assert::That(v == 1234UL, IsTrue());

                Assert::That(v != 4321UL, IsTrue());

                Assert::That(v == "1234", IsTrue());

                Assert::That(v != "4321", IsTrue());

                Assert::That(v == L"1234", IsTrue());

                Assert::That(v != L"4321", IsTrue());
            });

            it("has equality with itself", []() {
                variant a = "1234";

                variant b = "1234";

                Assert::That(a == b, IsTrue());

                variant c = "4321";

                Assert::That(a != c, IsTrue());
            });

            it("has blob equality", []() {
                size_t size = sizeof(int) * 2;

                void* data = malloc(size);

                memset(data, 1, size);

                binary bin = binary(data, size);

                variant v(bin);

                Assert::That(v != nullptr, IsTrue());

                Assert::That(v.is_binary(), IsTrue());

                variant t(v);

                Assert::That(v.equals(t), IsTrue());

                bool eq = (bin == v && v == bin);

                free(data);

                Assert::That(eq, IsTrue());
            });

            it("has default equality", []() {
                variant v;

                variant* b;

                variant c;

                b = &v;

                Assert::That(b->equals(v), IsTrue());

                Assert::That(v.equals(c), IsFalse());
            });
        });

        it("knows its type", []() {
            variant v(1234.1234);

            Assert::That(v.type(), Equals(variant::REAL));

            Assert::That(v.type_name(), Equals("real"));

            v = "testing";

            Assert::That(v.type(), Equals(variant::STRING));

            Assert::That(v.type_name(), Equals("string"));
        });

        describe("conversion", []() {
            it("converts a complex type", []() {
                variant v(make_shared<complex_val>(1234));

                AssertThrows(illegal_conversion, v.to_pointer());

                AssertThrows(illegal_conversion, v.to_binary());

                AssertThrows(illegal_conversion, v.to_cstring());

                AssertThrows(illegal_conversion, v.to_wcstring());

                AssertThrows(illegal_conversion, v.to_wcstring());

                AssertThrows(illegal_conversion, v.to_char());

                AssertThrows(illegal_conversion, v.to_uchar());

                AssertThrows(illegal_conversion, v.to_wchar());

                Assert::That(v.to_string(), Equals("1234"));

                ostringstream out;

                out << *v.to_complex();

                Assert::That(out.str(), Equals("1234"));

            });

            it("converts a wide string", []() {
                variant v = L"1234";

                Assert::That(v.to_pointer() != nullptr, IsTrue());

                v = L"true";

                Assert::That(v.to_bool(), IsTrue());

                AssertThrows(illegal_conversion, v.to_char());

                AssertThrows(illegal_conversion, v.to_uchar());

                Assert::That(v.to_wchar(), Equals(L't'));

                Assert::That(v.to_wchar(L'G'), Equals(L't'));
            });

            it("converts a string", []() {
                variant v = "1234";

                Assert::That(v.to_pointer() != nullptr, IsTrue());

                Assert::That(v.to_char(), Equals('1'));

                Assert::That(v.to_uchar(), Equals('1'));

                AssertThrows(illegal_conversion, v.to_wchar());
            });

            it("converts an integral type", []() {
                variant v = 1234;

                AssertThrows(illegal_conversion, v.to_pointer());

                AssertThrows(illegal_conversion, v.to_binary());
            });

            it("converts an unsigned type", []() {
                variant v = 1234U;

                Assert::That(v.to_bool(), IsTrue());
            });

            it("converts a real type", []() {
                variant v = 1234.1234;

                Assert::That(v.to_bool(), IsTrue());

                AssertThrows(illegal_conversion, v.to_complex());
            });

            it("converts a nulltype", []() {
                variant v = nullptr;

                Assert::That(v.to_binary().size(), Equals(0U));

                Assert::That(v.to_string(), Equals("NULL"));

                Assert::That(v.to_cstring() == nullptr, IsTrue());

                Assert::That(v.to_wcstring() == nullptr, IsTrue());

                Assert::That(nullptr == v, IsTrue());

                ostringstream out;

                out << v;

                Assert::That(out.str(), Equals("NULL"));

            });

            it("converts a binary", []() {
                binary b;

                variant v = b;

                Assert::That(v.to_string(), Equals("0x0"));

                Assert::That(v.to_bool(), IsFalse());
            });
        });

    });


});
