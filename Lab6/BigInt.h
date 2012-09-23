#ifndef H_BIG_INT
#define H_BIG_INT

#include "Common.h"

class BigInt
{
public:
	static const int base = 10000;
	static const int baseDimentions = 4;
	static const int maxDigitsCount = 25000;
	static const int maxDecDigitsCount = 100000;

	int size;
	int digits[maxDigitsCount];

	BigInt();

	friend BigInt* operator+(BigInt const &left, BigInt const &right);

private:
	
};

#endif