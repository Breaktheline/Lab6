#include "BigInt.h"

BigInt* operator+(const BigInt &left, const BigInt &right)
{
	BigInt* resultBigInt = new BigInt();
	int maxAmount = Max(left.size, right.size);
	int remainder = 0;

	for (int i = 0; i < maxAmount + remainder; i++)
	{
		int sum = left.digits[i] + right.digits[i] + remainder;

		//Если результат операции сложения больше основания, будет остаток
		if (sum >= BigInt::base)
		{
			resultBigInt->digits[i] = sum - BigInt::base;
			remainder = 1;
		}
		else
		{
			resultBigInt->digits[i] = sum;
			remainder = 0;
		}
	}

	resultBigInt->size = resultBigInt->digits[maxAmount] != 0 ? maxAmount + 1 : maxAmount;

	return resultBigInt;
}

BigInt::BigInt()
{
	for(int i = 0; i < BigInt::maxDigitsCount; i++)
	{
		digits[i] = 0;
	}
}
