#ifndef H_UNIT_TESTS_HELPER
#define H_UNIT_TESTS_HELPER

#include "Common.h"

class UnitTestsHelper
{
public:
	static void AssertDigits(int* digits, BigInt* bigInt)
	{
		for (int i = 0; i < bigInt->size; i++)
		{
			ASSERT_EQ(digits[i], bigInt->digits[i]);
		}
	}
};

#endif

