#include "gtest/gtest.h"
#include "FileOperations.h"
#include "TList.h"
#include "BigInt.h"
#include "UnitTestsHelper.h"

void SetDigits(BigInt* bigInt, int* digits)
{
	for(int i = 0; i < bigInt->size; i++)
	{
		bigInt->digits[i] = digits[i];
	}
}

TEST(AdditionTest, ShouldAddIfDigitsHasEqualSizeAndNoRemainder)
{
	BigInt left, right;
	left.size = right.size = 3;

	int leftDigits[] = {8998, 4567, 123};
	int rightDigits[] = {3210, 7654, 98};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	BigInt* result = left + right;

	ASSERT_EQ(3, result->size);
	int expect[] = {2208, 2222, 222};
	UnitTestsHelper::AssertDigits(expect, result);
}

TEST(AdditionTest, ShouldAddIfDigitsHasEqualSizeAndRemainder)
{
	BigInt left, right;
	left.size = right.size = 3;

	int leftDigits[] = {8998, 4567, 123};
	int rightDigits[] = {3210, 7654, 9998};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	BigInt* result = left + right;

	ASSERT_EQ(4, result->size);
	int expect[] = {2208, 2222, 122, 1};
	UnitTestsHelper::AssertDigits(expect, result);
}

TEST(AdditionTest, ShouldAddIfDigitsHasDiffSize)
{
	BigInt left, right;
	left.size = 3;
	right.size = 5;

	int leftDigits[] = {8998, 4567, 123};
	int rightDigits[] = {3210, 7654, 9998, 67, 543};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	BigInt* result = left + right;

	ASSERT_EQ(5, result->size);
	int expect[] = {2208, 2222, 122, 68, 543};
	UnitTestsHelper::AssertDigits(expect, result);
}

TEST(AdditionTest, ShouldAddIfDigitsHasZerosInResult)
{
	BigInt left, right;
	left.size = 2;
	right.size = 3;

	int leftDigits[] = {999, 1};
	int rightDigits[] = {999, 9999, 9};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	BigInt* result = left + right;

	ASSERT_EQ(3, result->size);
	int expect[] = {1998, 0, 10};
	UnitTestsHelper::AssertDigits(expect, result);
}

TEST(AdditionTest, ShouldAddIfDigitsHasNoRemainders)
{
	BigInt left, right;
	left.size = 2;
	right.size = 3;

	int leftDigits[] = {123, 12};
	int rightDigits[] = {321, 231, 2};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	BigInt* result = left + right;

	ASSERT_EQ(3, result->size);
	int expect[] = {444, 243, 2};
	UnitTestsHelper::AssertDigits(expect, result);
}