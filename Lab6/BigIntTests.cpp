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
	int digits[] = {0};

	ASSERT_EQ(1, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(SubtractionTest, NotSubtructIfLeftDigitLess)
{
	BigInt left, right;
	left.size = 3;
	right.size = 3;

	int leftDigits[] = {23, 45, 40};
	int rightDigits[] = {123, 45, 45};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	try
	{
		BigInt* result = left - right;
	}
	catch (AppException e)
	{
		ASSERT_EQ("Error", e.GetMessage());
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

TEST(MultiplicationTest, MultiplyIfMultsHasSameSizeAndNoCarry)
{
	BigInt left, right;
	left.size = 3;
	right.size = 3;

	int leftDigits[] = {33, 12, 1};
	int rightDigits[] = {44, 13, 5};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left * right;
	int digits[] = {1452, 957, 365, 73, 5};

	ASSERT_EQ(5, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(MultiplicationTest, MultiplyIfMultsHasSameSizeAndCarry)
{
	BigInt left, right;
	left.size = 3;
	right.size = 3;

	int leftDigits[] = {333, 125, 167};
	int rightDigits[] = {443, 135, 589};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left * right;
	int digits[] = {7519, 344, 7003, 6198, 8372, 9};

	ASSERT_EQ(6, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(MultiplicationTest, MultiplyIfMultsHasDiffSize)
{
	BigInt left, right;
	left.size = 2;
	right.size = 5;

	int leftDigits[] = {333, 125};
	int rightDigits[] = {443, 135, 589, 0, 327};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left * right;
	int digits[] = {7519, 344, 3022, 3646, 8898, 885, 4};

	ASSERT_EQ(7, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(MultiplicationTest, MultiplyIfOneMultIsZero)
{
	BigInt left, right;
	left.size = 1;
	right.size = 5;

	int leftDigits[] = {0};
	int rightDigits[] = {443, 135, 589, 0, 327};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left * right;
	int digits[] = {0};

	ASSERT_EQ(1, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(ShortMultiplicationTest, MultiplyIfShort)
{
	BigInt left;
	left.size = 3;

	int leftDigits[] = {33, 12, 1};
	SetDigits(&left, leftDigits);

	BigInt* result = left * 45678;
	int digits[] = {7374, 8286, 5732, 4};

	ASSERT_EQ(4, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(DivisionTest, DivideIfDividentIsLessThanDivisor)
{
	BigInt left, right;
	left.size = 2;
	right.size = 3;

	int leftDigits[] = {123, 45};
	int rightDigits[] = {123, 45, 6};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left / right;
	int digits[] = {0};

	ASSERT_EQ(1, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(DivisionTest, DivideIfDividentAndDivisorAreEquals)
{
	BigInt left, right;
	left.size = 3;
	right.size = 3;

	int leftDigits[] = {123, 45, 6};
	int rightDigits[] = {123, 45, 6};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left / right;
	int digits[] = {1};

	ASSERT_EQ(1, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(DivisionTest, DivideIfDivisorIsShort)
{
	BigInt left, right;
	left.size = 3;
	right.size = 1;

	int leftDigits[] = {123, 45, 6};
	int rightDigits[] = {123};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left / right;
	int digits[] = {1708, 488};

	ASSERT_EQ(2, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(DivisionTest, DivideIfDivisorIsLong)
{
	BigInt left, right;
	left.size = 3;
	right.size = 2;

	int leftDigits[] = {123, 45, 6};
	int rightDigits[] = {123, 88};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left / right;
	int digits[] = {682};

	ASSERT_EQ(1, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(DivisionTest, DivideIfDivisionResultIsLong)
{
	BigInt left, right;
	left.size = 4;
	right.size = 2;

	int leftDigits[] = {123, 45, 678, 999};
	int rightDigits[] = {123, 88};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);

	BigInt* result = left / right;
	int digits[] = {5656, 3514, 11};

	ASSERT_EQ(3, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(DivisionTest, NotDivideIfDivisorIsZero)
{
	BigInt left, right;
	left.size = 4;
	right.size = 1;

	int leftDigits[] = {123, 45, 678, 999};
	int rightDigits[] = {0};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	try
	{
		BigInt* result = left / right;
	}
	catch (AppException e)
	{
		ASSERT_EQ("Error", e.GetMessage());
	}
}