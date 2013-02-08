#include <igloo/igloo.h>
#include "collections.h"

using namespace arg3;

using namespace igloo;

Context(collections_test)
{
	Spec(join_test)
	{
		vector<int> ints = {4, 6, 23, 65, 343, 65, 123};

		string test = join(ints);

		Assert::That(test, Equals("4,6,23,65,343,65,123"));
	}
};

