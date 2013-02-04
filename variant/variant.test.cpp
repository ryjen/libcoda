#include <igloo/igloo.h>
#include "variant.h"

// compile with: clang++ -stdlib=libc++ -std=c++11 -o test_variant variant.test.cpp; ./test_variant

// get igloo at: http://igloo-testing.org

using namespace igloo;

using namespace arg3;

Context(sqliteTest)
{

	Spec(testInt)
	{
		variant v(20);

		Assert::That(v, Equals(20));
	}

	Spec(testAssignOperator)
	{
		variant v = 20;

		Assert::That(v, Equals(20));
	}

	Spec(testUnsignedInt)
	{
		variant v = 123U;

		Assert::That(v, Equals(123U));
	}

	Spec(testLong) {
		auto v = variant(456L);

		Assert::That(v, Equals(456L));
	}

	Spec(testULong)
	{
		variant v = 789UL;

		Assert::That(v, Equals(789UL));
	}

	Spec(testLongLong)
	{
		variant v = 1234LL;

		Assert::That(v, Equals(1234LL));
	}

	Spec(testULongLong)
	{
		variant v = 1234ULL;

		Assert::That(v, Equals(1234ULL));
	}

	Spec(testString)
	{
		variant v = "testing1234";

		Assert::That(v, Equals("testing1234"));
	}

	Spec(testWideChar)
	{	
		wvariant v = L"123testing";

		Assert::That(v, Equals(wstring(L"123testing")));

		Assert::That(v.to_int(0), Equals(123));
	}

	Spec(testConvertInt)
	{
		variant v = "123";

		Assert::That(v, Equals(123));

		v = "1234asdb";

		Assert::That(v, Equals(1234));

		v = "asdf1234";

		AssertThrows(std::invalid_argument, v.to_int());

		v = "1234129837410928374109283741029837410293847";

		AssertThrows(std::out_of_range, v.to_int());
	}

	Spec(testConvertLong)
	{
		variant v = "1234";

		Assert::That(v, Equals(1234L));

		v = 12342.3412343;

		Assert::That(v, Equals(12342L));

		v = "asasdlfknalskdnf";

		AssertThrows(std::invalid_argument, v.to_long());
	}

	Spec(testCast)
	{
		variant v = "1234.1234";

		int i = v;

		Assert::That(i, Equals(1234));

		long l = v;

		Assert::That(l, Equals(1234));

		double d = v;

		Assert::That(d, Equals(1234.1234));

		bool b = v;

		Assert::That(b, Equals(true));

		string s = v;

		Assert::That(s, Equals("1234.1234"));
	}

	Spec(testNULL)
	{
		variant v = NULL;

		Assert::That(v, Equals(NULL));

		Assert::That(v.to_int(), Equals(0));

		Assert::That(v.to_bool(), Equals(false));
	}

	Spec(testBoolOperator)
	{
		variant v = NULL;

		Assert::That(!v, Equals(true));

		v = "1234";

		Assert::That(!v, Equals(false));

	}

	Spec(mapVariantTest)
	{
		map<string,variant> container;

		container["test1"] = 1234;
		container["test2"] = "123.43";
		container["test3"] = true;

		Assert::That(container["test1"], Equals("1234"));
		Assert::That(container["test2"], Equals(123.43));
		Assert::That(container["test3"], Equals(1));
		
	}

	Spec(testAppendOperator)
	{
		variant v = "test";

		v << 1 << 2 << 3;

		Assert::That(v, Equals("test123"));
	}

	Spec(testBaseEquality) {
		variant v(10);

		Assert::That(v.base_int(16), Equals(16));

		Assert::That(v.base_long(16), Equals(16L));

		Assert::That(v.base_ulong(16), Equals(16UL));

		Assert::That(v.base_ullong(16), Equals(16ULL));
	}

	Spec(testBaseAutoDetect)
	{
		variant v = "0x7B";

		Assert::That(v.to_int(), Equals(123));

		v = "0173";

		Assert::That(v.to_long(), Equals(123));
	}
};
