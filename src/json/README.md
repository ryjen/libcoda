
coda_json
=======
[![Build Status](http://img.shields.io/travis/ryjen/json.svg)](https://travis-ci.org/ryjen/json)
[![Coverage Status](https://coveralls.io/repos/ryjen/json/badge.svg?branch=master&service=github)](https://coveralls.io/github/ryjen/json?branch=master)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://ryjen.mit-license.org)

Building
--------

After cloning run the following command to initialize submodules:

```bash
git submodule update --init --recursive
```

you can use [cmake](https://cmake.org) to generate for the build system of your choice.

```bash
mkdir debug; cd debug; 
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
make test
```

options supported are:

    -DENABLE_COVERAGE=ON   :   enable code coverage using lcov
    -DENABLE_MEMCHECK=ON    :   enable valgrind memory checking on tests

Examples
--------

*Objects*

```c++
ifstream file("object.test.json");

coda::json::object obj(file);

obj.get_int("var1"); // get an integer for a key

obj.set_string("var2", "testing"); // set a key/value pair

for(auto &entry: obj) // entry will be of type std::pair<string, coda::json::object>
{
	cout << "Key: " << entry.first << " Value: " << entry.second.to_string() << endl;
}

obj.parse("{ \"var1\": 1234, \"var2\": \"testing\" }"); // parse from string

obj.get("var1").to_int() == 1234; // true
```

*Arrays*

```c++
coda::json::array value;

value.add_double(123.321);

value.add_bool(true);

value.get_double(0) == 123.321; // true

value.get_bool(1) == true; // true

value[0].to_double() == 123.321; // true

value[1].to_bool() == true; // true

for(auto &entry: value) // entry will be of type coda::json::object
{
	cout << entry.to_string() << endl;
}

```


