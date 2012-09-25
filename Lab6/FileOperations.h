#ifndef H_FILE_OPERATIONS
#define H_FILE_OPERATIONS

#include "BigInt.h"
#include <stdio.h>
#include <stdlib.h>

enum Operation {ADD, SUBTRACT, MULTIPLY, DIVIDE, POWER, GREATER, LESS, EQUALS, UNKNOWN};

struct Result
{
	Result(bool aCondition, BigInt* aDigit)
	{
		condition = aCondition;
		digit = aDigit;
	}

	~Result()
	{
		delete digit;
	}

	bool IsDigit()
	{
		return digit != NULL;
	}

	bool condition;
	BigInt* digit;
};

class FileOperations
{
public:
	BigInt* ReadBigInt(FILE* inputFile, int ch);
	void PrintBigInt(BigInt* bigInt);
	void ReadFromFile(FILE* inputFile);
	Result ExecuteOperation(int operation, BigInt* first, BigInt* second);
	void PrintResult(Result* result);
	void PrintError(const char* message) ;
};

#endif
