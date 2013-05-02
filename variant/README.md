variant
=======

A c++11 utility class for storing arbitrary variables with automatic type conversion.  Usefull for things like database or configuration values.

Data storage is a basic_string<T> and conversions are done using std::stoi and std::to_string() type methods.

#### examples:

```c++
variant v = "1234.1234"; // assign a string

assert(v == 1234); // yep can convert to int

assert(v == 1234.1234); // yep can convert to double

assert(v == true); // yep can convert to bool

v = 1234.1234; // assign a double

assert(v == 1234ULL); // yep can convert to an unsigned long long

assert(v == "1234.1234"); // yep its a string

v = "abscdef"; // assign a non number string

v.to_int(); // will throw illegal_argument exception

v.to_int(0); // will return 0 by default instead of throwing an exception

```