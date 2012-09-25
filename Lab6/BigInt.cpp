#include "BigInt.h"

BigInt::BigInt()
{
	for(int i = 0; i < BigInt::maxDigitsCount; i++)
	{
		digits[i] = 0;
	}

	size = 0;
}

BigInt::BigInt(int digit)
{
	digits[0] = digit;
	for(int i = 1; i < BigInt::maxDigitsCount; i++)
	{
		digits[i] = 0;
	}

	size = 1;
}

bool IsZero(const BigInt* digit)
{
	return digit->size == 1 && digit->digits[0] == 0;
}

BigInt* Add(const BigInt* left, const BigInt* right)
{
	BigInt* result = new BigInt();
	int maxAmount = Max(left->size, right->size);
	int carry = 0;

	for (int i = 0; i < maxAmount + carry; i++)
	{
		int sum = left->digits[i] + right->digits[i] + carry;

		//Если результат операции сложения больше основания, будет остаток
		if (sum >= BigInt::base)
		{
			result->digits[i] = sum - BigInt::base;
			carry = 1;
		}
		else
		{
			result->digits[i] = sum;
			carry = 0;
		}
	}

	result->size = result->digits[maxAmount] != 0 ? maxAmount + 1 : maxAmount;

	return result;
}

bool AreEquals(const BigInt* left, const BigInt* right)
{
	if (left->size != right->size)
	{
		return false;
	}

	for(int i = 0; i < left->size; i++)
	{
		if (left->digits[i] != right->digits[i])
		{
			return false;
		}
	}

	return true;
}

bool IsGreater(const BigInt* left, const BigInt* right)
{
	if (left->size != right->size)
	{
		return left->size > right->size;
	}

	for(int i = left->size; i >= 0; i--)
	{
		if (left->digits[i] != right->digits[i])
		{
			return left->digits[i] > right->digits[i];
		}
	}

	return false;
}

bool IsLess(const BigInt* left, const BigInt* right)
{
	if (left->size != right->size)
	{
		return left->size < right->size;
	}

	for(int i = left->size; i >= 0; i--)
	{
		if (left->digits[i] != right->digits[i])
		{
			return left->digits[i] < right->digits[i];
		}
	}

	return false;
}

BigInt* Subtract(const BigInt* left, const BigInt* right)
{
	if (IsLess(left, right))
	{
		throw AppException(ErrorMessages::ERROR);
	}

	BigInt* result = new BigInt();
	int carry = 0;
	for(int i = 0; i < left->size; i++)
	{
		int subtraction = left->digits[i] - right->digits[i] - carry;
		if (subtraction >= 0)
		{
			result->digits[i] = subtraction;
			carry = 0;
		}
		else
		{
			result->digits[i] = BigInt::base + subtraction;
			carry = 1;
		}
	}

	result->size = DeleteExtraZeros(left->size, result);
	return result;
}

BigInt* Multiply(const BigInt* left, const BigInt* right)
{
	if (left->size + right->size > BigInt::maxDigitsCount)
	{
		throw AppException(ErrorMessages::ERROR);
	}

	if (IsZero(left) || IsZero(right))
	{
		return new BigInt(0);
	}

	BigInt* result = new BigInt();

	//Идем последовательно по каждой "цифре" второго числа
	for (int i = 0; i < right->size; i++)
	{
		int carry = 0;
		//Умножаем на каждую "цифру" первого числа с учетом переноса
		for (int j = 0; j < left->size || carry > 0; j++)
		{
			// предыдущее значение в ячейке + произведение чисел + перенос от прошлого произведения
			int mult = result->digits[i+j] + left->digits[j] * right->digits[i] + carry;
			carry = mult / BigInt::base;
			//вычитаем от произведение перенос
			result->digits[i+j] = mult - carry*BigInt::base;
		}
	}

	//Вычисляем размер получившегося числа
	result->size = DeleteExtraZeros(left->size + right->size, result);

	return result;
}

BigInt* Multiply(const BigInt* left, int right)
{
	BigInt* result = new BigInt();

	int carry = 0;
	//Умножаем короткое на каждую "цифру" первого числа с учетом переноса
	for (int i = 0; i < left->size || carry > 0; i++)
	{
		// предыдущее значение в ячейке + произведение чисел + перенос от прошлого произведения
		int mult = left->digits[i] * right + carry;
		carry = mult / BigInt::base;
		//вычитаем от произведение перенос
		result->digits[i] = mult - carry*BigInt::base;
	}

	//Вычисляем размер получившегося числа
	result->size = DeleteExtraZeros(left->size + 1, result);
	return result;
}

int FindDivisor(BigInt** divident, const BigInt* divisor)
{
	int left = 0;
	int right = BigInt::base;
	int half = 0;
	BigInt* mult;

	while (left <= right)
	{
		half = (left + right) / 2;
		mult = Multiply(divisor, half);
		if (IsGreater(mult, *divident))
		{
			right = half - 1;
		}
		else
		{
			left = half + 1;
		}

		delete mult;
	}

	half = (left + right) / 2;
	mult = Multiply(divisor, half);

	BigInt* oldDivident = *divident;
	*divident = Subtract(*divident, mult);
	delete oldDivident;

	delete mult;

	return half;
}

void DeleteExtraZeros( BigInt* divident, BigInt* result );

BigInt* Divide(const BigInt* left, const BigInt* right)
{
	if (IsZero(right))
	{
		throw AppException(ErrorMessages::ERROR);
	}

	BigInt* result = new BigInt();
	BigInt* divident = new BigInt();
	//Движемся с начала числа
	for (int i = left->size - 1; i >= 0; i--)
	{
		//Умножаем делимое на основание, сдвигая число
		for(int j = divident->size; j > 0; j--)
		{
			divident->digits[j] = divident->digits[j-1];
		}
		//Прибавляем следующую "цифру" к делимому
		divident->digits[0] = left->digits[i];
		divident->size++;
		divident->size = DeleteExtraZeros(divident->size, divident);

		result->digits[i] = FindDivisor(&divident, right);
	}

	// избавляемся от лишних нулей
	result->size = DeleteExtraZeros(left->size, result);
	return result;
}

BigInt* Power(const BigInt* left, const BigInt* power)
{
	if (IsZero(power))
	{
		if (IsZero(left))
		{
			throw AppException(ErrorMessages::ERROR);
		}

		return new BigInt(1);
	}

	BigInt* result = new BigInt(1);

	BigInt* n = new BigInt(*power);
	BigInt* digit = new BigInt(*left);
	BigInt* two = new BigInt(2);

	while (true)
	{
		//Если число нечетное, то умножаем на число.
		if (n->digits[0] & 1)
		{
			BigInt* oldResult = result;
			result = Multiply(result, digit);
			delete oldResult;
		}

		BigInt* oldN = n;
		n = Divide(n, two);
		delete oldN;

		if (IsZero(n))
		{
			break;
		}

		BigInt* oldDigit = digit;
		digit = Multiply(digit, digit);
		delete oldDigit;
	}

	delete two;
	delete n;
	delete digit;

	return result;
}

int DeleteExtraZeros(int startSize, BigInt* digit)
{
	int size = startSize;
	while (size > 1 && digit->digits[size-1] == 0)
	{
		size--;
	}
	return size;
}

