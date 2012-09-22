#ifndef H_OPERATIONS
#define H_OPERATIONS

#include "BigInt.h"
#include "stdio.h"

class Operations
{
public:
	BigInt* ReadBigInt(FILE* inputFile);
	void PrintBigInt(BigInt* bigInt);
};

#endif
