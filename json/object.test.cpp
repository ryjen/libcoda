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

        obj.setString("testa", "test string");

        obj.setInt("testb", 1234);

        obj.setBool("testc", true);

        obj.setDouble("testd", 1234.4321);

        auto i = obj.begin();

        Assert::That(i->first, Equals("testa"));

        Assert::That(i->second.isString(), Equals(true));

        Assert::That(i->second.toString(), Equals("test string"));

        i++;

        Assert::That(i->second.isInt(), Equals(true));

        Assert::That(i->second.toInt(), Equals(1234));

        i++;

        Assert::That(i->second.isBool(), Equals(true));

        Assert::That(i->second.toBool(), Equals(true));

        i++;

        Assert::That(i->second.isDouble(), Equals(true));

        Assert::That(i->second.toDouble(), Equals(1234.4321));
    }


    Spec(testParse)
    {
        const char *TESTVALUE = "{\"col1\":\"value1\",\"col2\":1234,\"col3\":123.321,\"col4\":true,\"col5\":[\"a1\",2,true],\"col6\":{\"col7\":true}}";

        json::object obj;

        bool rval = obj.parse(TESTVALUE);

        Assert::That(rval, Equals(true));

        Assert::That(obj.get("col1").isString(), Equals(true));

        Assert::That(obj.get("col1").toString(), Equals("value1"));

        Assert::That(obj.get("col2").toInt(), Equals(1234));

        Assert::That(obj.get("col3").toDouble(), Equals(123.321));

        Assert::That(obj.get("col4").toBool(), Equals(true));

        Assert::That(obj.get("col5").isArray(), Equals(true));

        Assert::That(obj.get("col5").get(0).toString(), Equals("a1"));

        Assert::That(obj.get("col6").getBool("col7"), Equals(true));
    }
};

