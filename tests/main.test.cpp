#include <string>

#include <bandit/bandit.h>
#include "../src/log/log.h"

using namespace bandit;

int main(int argc, char *argv[])
{
    rj::log::set_min_log_level(rj::LOG_DEBUG);

    return bandit::run(argc, argv);
}
