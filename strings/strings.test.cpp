#include <igloo/igloo.h>
#include "strings.h"

using namespace igloo;

using namespace arg3;


Context(arg3strings)
{
    Spec(is_valid_email_test)
    {
        string email = "somedude@email.com.ca";

        Assert::That(is_valid_email(email), Equals(true));
    }
};
