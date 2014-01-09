
#include <igloo/igloo.h>
#include <arg3/log/log.h>

using namespace igloo;

int main()
{
    arg3::log::set_min_log_level(arg3::log::DEBUG);
    return TestRunner::RunAllTests();
}