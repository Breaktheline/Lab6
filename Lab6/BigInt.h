#ifndef H_BIG_INT
#define H_BIG_INT

#include "Common.h"

class BigInt
{
public:
	static const int base = 10000;
	static const int baseDimentions = 4;
	static const int maxDigitsCount = 50000;
	static const int maxDecDigitsCount = 100000;

	int size;
	int digits[maxDigitsCount];

	BigInt();
	BigInt(int digit);
};

bool IsZero(const BigInt* digit);
BigInt* Add(const BigInt* left, const BigInt* right);
bool AreEquals(const BigInt* left, const BigInt* right);
bool IsGreater(const BigInt* left, const BigInt* right);
bool IsLess(const BigInt* left, const BigInt* right);
BigInt* Subtract(const BigInt* left, const BigInt* right);
BigInt* Multiply(const BigInt* left, const BigInt* right);
BigInt* Multiply(const BigInt* left, int right);
int FindDivisor(BigInt** divident, const BigInt* divisor);
BigInt* Divide(const BigInt* left, const BigInt* right);
BigInt* Power(const BigInt* left, const BigInt* power);
int DeleteExtraZeros(int startSize, BigInt* digit);

#endif

