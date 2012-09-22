#ifndef H_FILE_OPERATIONS
#define H_FILE_OPERATIONS

#include "BigInt.h"
#include <stdio.h>
#include <stdlib.h>

class FileOperations
{
public:
	BigInt* ReadBigInt(FILE* inputFile);
	void PrintBigInt(BigInt* bigInt);
};

#endif
