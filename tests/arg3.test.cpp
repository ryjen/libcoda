
#include <bandit/bandit.h>
#include "../src/log/log.h"

using namespace bandit;

int main(int argc, char *argv[])
{
    arg3::log::set_min_log_level(arg3::LOG_DEBUG);

    return bandit::run(argc, argv);
}
