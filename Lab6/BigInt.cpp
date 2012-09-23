#include "BigInt.h"

BigInt::BigInt()
{
	for(int i = 0; i < BigInt::maxDigitsCount; i++)
	{
		digits[i] = 0;
	}

	size = 0;
}

BigInt* operator+(const BigInt &left, const BigInt &right)
{
	BigInt* result = new BigInt();
	int maxAmount = Max(left.size, right.size);
	int remainder = 0;

	for (int i = 0; i < maxAmount + remainder; i++)
	{
		int sum = left.digits[i] + right.digits[i] + remainder;

		//Если результат операции сложения больше основания, будет остаток
		if (sum >= BigInt::base)
		{
			result->digits[i] = sum - BigInt::base;
			remainder = 1;
		}
		else
		{
			result->digits[i] = sum;
			remainder = 0;
		}
	}

	result->size = result->digits[maxAmount] != 0 ? maxAmount + 1 : maxAmount;

	return result;
}

bool operator==(const BigInt &left, const BigInt &right)
{
	if (left.size != right.size)
	{
		return false;
	}

	for(int i = 0; i < left.size; i++)
	{
		if (left.digits[i] != right.digits[i])
		{
			return false;
		}
	}

	return true;
}

bool operator>(const BigInt &left, const BigInt &right)
{
	if (left.size != right.size)
	{
		return left.size > right.size;
	}

	for(int i = left.size; i >= 0; i--)
	{
		if (left.digits[i] != right.digits[i])
		{
			return left.digits[i] > right.digits[i];
		}
	}

	return false;
}

bool operator<(const BigInt &left, const BigInt &right)
{
	if (left.size != right.size)
	{
		return left.size < right.size;
	}

	for(int i = left.size; i >= 0; i--)
	{
		if (left.digits[i] != right.digits[i])
		{
			return left.digits[i] < right.digits[i];
		}
	}

	return false;
}

BigInt* operator-(const BigInt &left, const BigInt &right)
{
	if (left < right)
	{
		throw AppException(ErrorMessages::ERROR);
	}

	BigInt* result = new BigInt();
	int remainder = 0;
	for(int i = 0; i < left.size; i++)
	{
		int subtraction = left.digits[i] - right.digits[i] - remainder;
		if (subtraction >= 0)
		{
			result->digits[i] = subtraction;
			remainder = 0;
		}
		else
		{
			result->digits[i] = BigInt::base + subtraction;
			remainder = 1;
		}
	}

	int size = left.size;
	while(result->digits[size-1] <= 0 && size > 0)
	{
		size--;
	}

	result->size = size;
	return result;
}