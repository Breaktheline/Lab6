#include "gtest/gtest.h"
#include "FileOperations.h"
#include "TList.h"
#include "BigInt.h"

void WriteDataToFile(char* fileName, TList<char>* string) 
{
	FILE* inputFile = fopen(fileName, "w");
	for(int i = 0; i < string->GetCount(); i++)
	{
		fprintf(inputFile, "%c", string->GetElement(i));
	}
	fprintf(inputFile, "\n");
	fclose(inputFile);
}

BigInt* ReadBigInt(TList<char>* inputString) 
{
	char* fileName = "Tests/in";
	WriteDataToFile(fileName, inputString);

	FILE* inputFile = fopen(fileName, "r");
	FileOperations operations;
	BigInt* bigInt = operations.ReadBigInt(inputFile);
	fclose(inputFile);

	return bigInt;
}

TList<char>* CreateInputString(char* string, int length)
{
	TList<char>* inputString = new TList<char>();
	for(int i = 0; i < length; i++)
	{
		inputString->Add(string[i]);
	}
	return inputString;
}

void AssertDigits(int* digits, int length, BigInt* bigInt)
{
	for (int i = 0; i < length; i++)
	{
		ASSERT_EQ(digits[i], bigInt->digits[i]);
	}
}

TEST(InputOutputTest, ShouldReadSimpleLongDigit)
{
	TList<char>* inputString = CreateInputString("1234567899876543", 16);
	BigInt* bigInt = ReadBigInt(inputString);
	
	ASSERT_EQ(4, bigInt->amount);
	int digits[] = {6543, 9987, 5678, 1234};
	AssertDigits(digits, 4, bigInt);
}

TEST(InputOutputTest, ShouldReadLongDigitWithShortLastDigit)
{
	TList<char>* inputString = CreateInputString("11234567899876543", 17);
	BigInt* bigInt = ReadBigInt(inputString);

	ASSERT_EQ(5, bigInt->amount);
	int digits[] = {6543, 9987, 5678, 1234, 1};
	AssertDigits(digits, 5, bigInt);
}

TEST(InputOutputTest, ShouldReadLongDigitWithFirstZeros)
{
	TList<char>* inputString = CreateInputString("0000001234567899876543", 22);
	BigInt* bigInt = ReadBigInt(inputString);

	ASSERT_EQ(4, bigInt->amount);
	int digits[] = {6543, 9987, 5678, 1234};
	AssertDigits(digits, 4, bigInt);
}

TEST(InputOutputTest, ShouldReadLongDigitWithZerosInTheMiddle)
{
	TList<char>* inputString = CreateInputString("000100000090070043", 18);
	BigInt* bigInt = ReadBigInt(inputString);

	ASSERT_EQ(4, bigInt->amount);
	int digits[] = {43, 9007, 0, 100};
	AssertDigits(digits, 4, bigInt);
}