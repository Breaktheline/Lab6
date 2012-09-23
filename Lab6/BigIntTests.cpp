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

TEST(CompareTest, CompareIfDigitsAreEquals)
{
	BigInt left, right;
	left.size = 2;
	right.size = 2;

	int leftDigits[] = {123, 45};
	int rightDigits[] = {123, 45};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	ASSERT_EQ(true, left == right);
	ASSERT_EQ(false, left > right);
	ASSERT_EQ(false, left < right);
}

TEST(CompareTest, CompareIfDigitsHasDiffSizes)
{
	BigInt left, right;
	left.size = 2;
	right.size = 3;

	int leftDigits[] = {123, 45};
	int rightDigits[] = {123, 45, 45};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	ASSERT_EQ(false, left == right);
	ASSERT_EQ(false, left > right);
	ASSERT_EQ(true, left < right);
}

TEST(CompareTest, CompareIfLeftDigitGreater)
{
	BigInt left, right;
	left.size = 3;
	right.size = 3;

	int leftDigits[] = {23, 45, 45};
	int rightDigits[] = {123, 45, 45};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	ASSERT_EQ(false, left == right);
	ASSERT_EQ(false, left > right);
	ASSERT_EQ(true, left < right);
}

TEST(CompareTest, CompareIfLeftDigitLess)
{
	BigInt left, right;
	left.size = 3;
	right.size = 3;

	int leftDigits[] = {23, 45, 46};
	int rightDigits[] = {123, 45, 45};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	ASSERT_EQ(false, left == right);
	ASSERT_EQ(true, left > right);
	ASSERT_EQ(false, left < right);
}

TEST(SubtractionTest, CanSubtructIfEquals)
{
	BigInt left, right;
	left.size = 3;
	right.size = 3;

	int leftDigits[] = {123, 45, 46};
	int rightDigits[] = {123, 45, 46};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left - right;

	ASSERT_EQ(0, result->size);
}

TEST(SubtractionTest, NotSubtructIfLeftDigitLess)
{
	BigInt left, right;
	left.size = 3;
	right.size = 3;

	int leftDigits[] = {23, 45, 46};
	int rightDigits[] = {123, 45, 45};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	try
	{
		BigInt* result = left - right;
	}
	catch (AppException* e)
	{
		ASSERT_EQ("Error", e->GetMessage());
	}
}

TEST(SubtractionTest, SubtructIfLeftDigitGreaterAndNoRemainder)
{
	BigInt left, right;
	left.size = 3;
	right.size = 3;

	int leftDigits[] = {224, 67, 46};
	int rightDigits[] = {123, 45, 45};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left - right;
	int digits[] = {101, 22, 1};

	ASSERT_EQ(3, result->size);
	UnitTestsHelper::AssertDigits(digits, result);

}

TEST(SubtractionTest, SubtructIfLeftDigitGreaterAndHasRemainder)
{
	BigInt left, right;
	left.size = 3;
	right.size = 2;

	int leftDigits[] = {1998, 0, 10};
	int rightDigits[] = {4567, 123};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left - right;
	int digits[] = {7431, 9876, 9};

	ASSERT_EQ(3, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(SubtractionTest, SubtructIfResultSizeIsLess)
{
	BigInt left, right;
	left.size = 3;
	right.size = 2;

	int leftDigits[] = {198, 0, 1};
	int rightDigits[] = {4567, 123};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left - right;
	int digits[] = {5631, 9876};

	ASSERT_EQ(2, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

