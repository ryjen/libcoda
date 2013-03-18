#include "object.h"
#include "array.h"
#include <igloo/igloo.h>

using namespace arg3;

using namespace igloo;

using namespace std;

Context(JsonObject)
{
	Spec(testIterator)
	{
		json::object obj;

		obj.set_str("testa", "test string");

		obj.set_int("testb", 1234);

		obj.set_bool("testc", true);

		obj.set_double("testd", 1234.4321);

		auto i = obj.begin();

		Assert::That(i->first, Equals("testa"));

		Assert::That(i->second.is_str(), Equals(true));

		Assert::That(i->second.to_str(), Equals("test string"));

		i++;

		Assert::That(i->second.is_int(), Equals(true));

		Assert::That(i->second.to_int(), Equals(1234));

		i++;

		Assert::That(i->second.is_bool(), Equals(true));

		Assert::That(i->second.to_bool(), Equals(true));

		i++;

		Assert::That(i->second.is_double(), Equals(true));

		Assert::That(i->second.to_double(), Equals(1234.4321));
	}


    Spec(testParse)
    {
        const char *TESTVALUE = "{\"col1\":\"value1\",\"col2\":1234,\"col3\":123.321,\"col4\":true,\"col5\":[\"a1\",2,true],\"col6\":{\"col7\":true}}";

        json::object obj;

        bool rval = obj.parse(TESTVALUE);

        Assert::That(rval, Equals(true));

        Assert::That(obj.get("col1").is_str(), Equals(true));

        Assert::That(obj.get("col1").to_str(), Equals("value1"));

        Assert::That(obj.get("col2").to_int(), Equals(1234));

        Assert::That(obj.get("col3").to_double(), Equals(123.321));

        Assert::That(obj.get("col4").to_bool(), Equals(true));

        Assert::That(obj.get("col5").is_array(), Equals(true));

        Assert::That(obj.get("col5").get(0).to_str(), Equals("a1"));

        Assert::That(obj.get("col6").get_bool("col7"), Equals(true));
    }
};

