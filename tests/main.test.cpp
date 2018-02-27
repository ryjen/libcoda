#include <string>

#include <bandit/bandit.h>
#include "../src/log/log.h"

using namespace bandit;

int main(int argc, char *argv[])
{
    rj::log::level::set(rj::log::level::Debug);

    return bandit::run(argc, argv);
}
