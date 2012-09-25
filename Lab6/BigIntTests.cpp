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
	BigInt* result = Add(&left, &right);

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
	BigInt* result = Add(&left, &right);

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
	BigInt* result = Add(&left, &right);

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
	BigInt* result = Add(&left, &right);

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
	BigInt* result = Add(&left, &right);

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
	ASSERT_EQ(true, AreEquals(&left, &right));
	ASSERT_EQ(false, IsGreater(&left, &right));
	ASSERT_EQ(false, IsLess(&left, &right));
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
	ASSERT_EQ(false, AreEquals(&left, &right));
	ASSERT_EQ(false, IsGreater(&left, &right));
	ASSERT_EQ(true, IsLess(&left, &right));
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
	ASSERT_EQ(false, AreEquals(&left, &right));
	ASSERT_EQ(false, IsGreater(&left, &right));
	ASSERT_EQ(true, IsLess(&left, &right));
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
	ASSERT_EQ(false, AreEquals(&left, &right));
	ASSERT_EQ(true, IsGreater(&left, &right));
	ASSERT_EQ(false, IsLess(&left, &right));
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

	BigInt* result = Subtract(&left, &right);
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
		BigInt* result = Subtract(&left, &right);
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

	BigInt* result = Subtract(&left, &right);
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

	BigInt* result = Subtract(&left, &right);
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

	BigInt* result = Subtract(&left, &right);
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

	BigInt* result = Multiply(&left, &right);
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

	BigInt* result = Multiply(&left, &right);
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

	BigInt* result = Multiply(&left, &right);
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

	BigInt* result = Multiply(&left, &right);
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

	BigInt* result = Multiply(&left, 45678);
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

	BigInt* result = Divide(&left, &right);
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

	BigInt* result = Divide(&left, &right);
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

	BigInt* result = Divide(&left, &right);
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

	BigInt* result = Divide(&left, &right);
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

	BigInt* result = Divide(&left, &right);
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
		BigInt* result = Divide(&left, &right);
	}
	catch (AppException e)
	{
		ASSERT_EQ("Error", e.GetMessage());
		return;
	}

	ASSERT_FALSE(true);
}

TEST(DivisionTest, DivideIfDividentIsZero)
{
	BigInt left, right;
	left.size = 1;
	right.size = 4;

	int leftDigits[] = {0};
	int rightDigits[] = {123, 45, 678, 999};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	BigInt* result = Divide(&left, &right);
	int digits[] = {0};

	ASSERT_EQ(1, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(PowerTest, PowerIfPowerIsShort)
{
	BigInt left, right;
	left.size = 2;
	right.size = 1;

	int leftDigits[] = {123, 4};
	int rightDigits[] = {5};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	BigInt* result = Power(&left, &right);
	int digits[] = {6843, 8125, 6774, 2379, 8411, 1039};

	ASSERT_EQ(6, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

TEST(PowerTest, PowerIfPowerIsZero)
{
	BigInt left, right;
	left.size = 2;
	right.size = 1;

	int leftDigits[] = {2};
	int rightDigits[] = {0};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	BigInt* result = Power(&left, &right);
	int digits[] = {1};

	ASSERT_EQ(1, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}


TEST(PowerTest, PowerIfPowerIsBig)
{
	BigInt left, right;
	left.size = 1;
	right.size = 1;

	int leftDigits[] = {99};
	int rightDigits[] = {99};
	SetDigits(&left, leftDigits);
	SetDigits(&right, rightDigits);
	BigInt* result = Power(&left, &right);
	int digits[] = {9899, 49, 1592, 9999, 9977, 3849, 9301, 6765, 606, 8071, 1441, 6440, 193, 2157, 4516, 4359, 6949, 9967,
	9429, 4011, 3265, 9548, 7888, 9409, 2727, 2823, 101, 650, 2141, 5234, 5277, 7045, 5525, 2423, 5997, 4302, 1102, 8174, 
	7642, 5668, 4059, 8054, 5628, 8790, 6571, 6772, 4972, 6376, 9729, 36};
	FileOperations fileOperations;
	fileOperations.PrintBigInt(result);

	ASSERT_EQ(50, result->size);
	UnitTestsHelper::AssertDigits(digits, result);
}

//TEST(PowerTest, PowerIfNoOverflow)
//{
//	BigInt left, right;
//	left.size = 2;
//	right.size = 2;
//
//	int leftDigits[] = {9999, 9999};
//	int rightDigits[] = {5000, 2};
//	SetDigits(&left, leftDigits);
//	SetDigits(&right, rightDigits);
//	BigInt* result = Power(&left, &right);
//	FileOperations fileOperations;
//	//fileOperations.PrintBigInt(result);
//
//	ASSERT_EQ(50000, result->size);
//	//UnitTestsHelper::AssertDigits(digits, result);
//}
//
//TEST(PowerTest, ErrorPowerIfOverflow)
//{
//	BigInt left, right;
//	left.size = 2;
//	right.size = 2;
//
//	int leftDigits[] = {9999, 9999};
//	int rightDigits[] = {5001, 2};
//	SetDigits(&left, leftDigits);
//	SetDigits(&right, rightDigits);
//	try
//	{
//		BigInt* result = Power(&left, &right);
//	}
//	catch(AppException ex)
//	{
//		ASSERT_EQ("Error", ex.GetMessage());
//		return;
//	}
//
//	ASSERT_FALSE(true);
//	//ASSERT_EQ(25002, result->size);
//	//UnitTestsHelper::AssertDigits(digits, result);
//}
