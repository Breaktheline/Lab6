#include "gtest/gtest.h"
#include "FileOperations.h"
#include "TList.h"
#include "BigInt.h"
#include "UnitTestsHelper.h"

void WriteDataToFile(char* fileName, char* string) 
{
	FILE* inputFile = fopen(fileName, "w");
	fprintf(inputFile, "%s\n", string);
	fclose(inputFile);
}

BigInt* ReadBigInt(char* inputString) 
{
	char* fileName = "Tests/in";
	WriteDataToFile(fileName, inputString);

	FILE* inputFile = fopen(fileName, "r");
	FileOperations operations;
	BigInt* bigInt = operations.ReadBigInt(inputFile, fgetc(inputFile));
	fclose(inputFile);

	return bigInt;
}

void AssertDigits(int* digits, int length, BigInt* bigInt)
{
	for (int i = 0; i < length; i++)
	{
		ASSERT_EQ(digits[i], bigInt->digits[i]);
	}
}

void SetUpDigits(int* digits, int length, int* digitsToSetup) 
{
	for(int i = 0; i < length; i++)
	{
		digits[i] = digitsToSetup[i];
	}
}

TEST(InputOutputTest, ShouldReadSimpleLongDigit)
{
	BigInt* bigInt = ReadBigInt("1234567899876543");
	
	ASSERT_EQ(4, bigInt->size);
	int digits[] = {6543, 9987, 5678, 1234};
	UnitTestsHelper::AssertDigits(digits, bigInt);
}

TEST(InputOutputTest, ShouldReadLongDigitWithShortLastDigit)
{
	BigInt* bigInt = ReadBigInt("11234567899876543");

	ASSERT_EQ(5, bigInt->size);
	int digits[] = {6543, 9987, 5678, 1234, 1};
	UnitTestsHelper::AssertDigits(digits, bigInt);
}

TEST(InputOutputTest, ShouldReadLongDigitWithFirstZeros)
{
	BigInt* bigInt = ReadBigInt("0000001234567899876543");

	ASSERT_EQ(4, bigInt->size);
	int digits[] = {6543, 9987, 5678, 1234};
	UnitTestsHelper::AssertDigits(digits, bigInt);
}

TEST(InputOutputTest, ShouldReadLongDigitWithZerosInTheMiddle)
{
	BigInt* bigInt = ReadBigInt("000100000090070043");

	ASSERT_EQ(4, bigInt->size);
	int digits[] = {43, 9007, 0, 100};
	UnitTestsHelper::AssertDigits(digits, bigInt);
}

TEST(InputOutputTest, ShouldReadZero)
{
	BigInt* bigInt = ReadBigInt("00000");

	ASSERT_EQ(1, bigInt->size);
	int digits[] = {0};
	UnitTestsHelper::AssertDigits(digits, bigInt);
}

TEST(InputOutputTest, ShouldPrintLongDigitWithZerosInside)
{
	BigInt bigInt;
	bigInt.size = 5;
	int digits[] = {43, 9007, 0, 100, 23};
	SetUpDigits(bigInt.digits, 5, digits);

	FileOperations operations;
	operations.PrintBigInt(&bigInt);
}

TEST(InputOutputTest, ShouldPrintLongDigitOne)
{
	BigInt bigInt;
	bigInt.size = 1;
	int digits[] = {43};
	SetUpDigits(bigInt.digits, 1, digits);

	FileOperations operations;
	operations.PrintBigInt(&bigInt);
}

TEST(InputOutputTest, ShouldPrintZero)
{
	BigInt bigInt;
	bigInt.size = 1;
	int digits[] = {0};
	SetUpDigits(bigInt.digits, 1, digits);

	FileOperations operations;
	operations.PrintBigInt(&bigInt);
}

TEST(OutputTest, CanPrintAddResult)
{
	BigInt* bigInt = ReadBigInt("1234567899876543");
	BigInt* result = Add(bigInt, bigInt);
	FileOperations operations;
	operations.PrintBigInt(result);
}

TEST(ReadFileTest, ShouldExecuteSeveralOperationsFromFile)
{	
	char* fileName = "Tests/in";
	char* one = "1234567899876543\n1234567899876543\n+";
	char* two = "123456789987\n1234567899876543\n-";
	char* three = "123456789987\n123456789987\n-";
	char* four = "123456789987\n1234567\n-";
	char* five = "123456789987\n1234567899876543\n*";
	char* six = "123456789987\n000000\n*";
	char* seven = "1\n1234567899876543\n*";
	char* eight = "123456789987\n1234567899876543\n/";
	char* nine = "123456789987\n876543\n/";
	char* ten = "123456789\n123456789\n/";
	char* eleven = "123456789\n0\n/";
	char* twelve = "000\n123456789\n/";
	char* thirteen = "123456789987\n123456789\n^";
	char* fourteen = "12\n12345\n^";
	char* fifteen = "12\n8\n^";
	char* sixteen = "123456789987\n123456789\n>";
	char* seventeen = "123456790\n123456789\n>";
	char* eighteen = "123456790\n123456789\n=";
	char* nineteen = "123456789\n123456789\n=";
	char* twenty = "123456790\n123456789\n=";
	char* twentyone = "123456790\n123456789\n<";
	FILE* inputFile = fopen(fileName, "w");
	fprintf(inputFile, "%s\n", one);
	fprintf(inputFile, "%s\n", two);
	fprintf(inputFile, "%s\n", three);
	fprintf(inputFile, "%s\n", four);
	fprintf(inputFile, "%s\n", five);
	fprintf(inputFile, "%s\n", six);
	fprintf(inputFile, "%s\n", seven);
	fprintf(inputFile, "%s\n", eight);
	fprintf(inputFile, "%s\n", nine);
	fprintf(inputFile, "%s\n", ten );
	fprintf(inputFile, "%s\n", eleven);
	fprintf(inputFile, "%s\n", twelve);
	fprintf(inputFile, "%s\n", thirteen);
	fprintf(inputFile, "%s\n", fourteen);
	fprintf(inputFile, "%s\n", fifteen);
	fprintf(inputFile, "%s\n", sixteen);
	fprintf(inputFile, "%s\n", seventeen);
	fprintf(inputFile, "%s\n", eighteen);
	fprintf(inputFile, "%s\n", nineteen);
	fprintf(inputFile, "%s\n", twenty);
	fprintf(inputFile, "%s\n", twentyone);
	fclose(inputFile);

	inputFile = fopen(fileName, "r");
	FileOperations operations;
	operations.ReadFromFile(inputFile);
	fclose(inputFile);
}