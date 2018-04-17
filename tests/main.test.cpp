#include <string>

#include <bandit/bandit.h>
#include "log/log.h"

using namespace bandit;

int main(int argc, char *argv[])
{
    coda::log::level::set(coda::log::level::Debug);

    return bandit::run(argc, argv);
}
