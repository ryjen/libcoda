#include <bandit/bandit.h>
#include "bigint.h"

using namespace bandit;
using namespace arg3;

go_bandit([]()
{

    describe("a big integer", []()
    {
        it("can use a literal", []()
        {

            bigint bi = 34098792871928374019287305239874052938465018273192387418273657623868726345_bi;

            Assert::That(bi.to_string(), Equals("34098792871928374019287305239874052938465018273192387418273657623868726345") );
        });
    });

});
