#include "FileOperations.h"

BigInt* FileOperations::ReadBigInt(FILE* inputFile, int ch)
{
	//”бираем ведущие нули
	//int ch = fgetc(inputFile);

	while (ch == '0')
	{
		ch = fgetc(inputFile);
	}

	BigInt* bigInt = new BigInt();

	if (ch == '\n' || ch == '\r')
	{
		bigInt->size = 1;
		return bigInt;
	}

	char stringOfDigits[BigInt::maxDecDigitsCount];
	int stringLength = 0;
	while (ch != '\n'&& ch != '\r')
	{
		stringOfDigits[stringLength] = ch;
		stringLength++;
		ch = fgetc(inputFile);
	}

	int digitLength = BigInt::baseDimentions;

	int digitPosition = 0;
	// с конца строки
	for(int i = stringLength - 1; i >= 0; i -= digitLength)
	{
		// Ќаходим стартовую позицию числа
		int startOfDigit = i - digitLength + 1;
		// ≈сли стартова€ позици€ отрицительна€, то уменьшаем длину числа
		if (startOfDigit < 0)
		{
			digitLength += startOfDigit;
			startOfDigit = 0;
		}

		//—читываем число
		char digitString[BigInt::baseDimentions];
		for(int j = 0; j < digitLength; j++)
		{
			digitString[j] = stringOfDigits[startOfDigit + j];
		}
		// онец массива, если длина считанного числа меньше 
		if (digitLength < BigInt::baseDimentions)
		{
			digitString[digitLength] = '\0';
		}

		bigInt->digits[digitPosition] = atoi(digitString);
		digitPosition++;
	}

	bigInt->size = digitPosition;
	return bigInt;
}

void FileOperations::PrintBigInt(BigInt* bigInt)
{
	const char format[] = "%.4d";

	printf("%d",bigInt->digits[bigInt->size-1]);
	for (int i = bigInt->size - 2; i >= 0; i--)
	{
		printf(format, bigInt->digits[i]);
	}
	printf("\n");
}

void FileOperations::PrintError(const char* message) 
{
	printf("%s\n", message);
}

void FileOperations::ReadFromFile(FILE* inputFile)
{
	if (inputFile == NULL)
	{
		PrintError(ErrorMessages::FILE_OPEN_ERROR);
		return;
	}
	int ch = fgetc(inputFile);
	while(!feof(inputFile) && ch != EOF)
	{
		BigInt* first = ReadBigInt(inputFile, ch);
		BigInt* second = ReadBigInt(inputFile, fgetc(inputFile));
		int operation = fgetc(inputFile);
		fgetc(inputFile);
		try
		{
			Result result = ExecuteOperation(operation, first, second);
			PrintResult(&result);
			delete first;
			delete second;
		}
		catch(AppException ex)
		{
			PrintError(ex.GetMessage());
		}
		ch = fgetc(inputFile);
	}
}

Result FileOperations::ExecuteOperation(int operation, BigInt* first, BigInt* second)
{
	BigInt* digit = NULL;
	bool condition = false;
	switch(operation)
	{
	case '+':
		{
			digit = Add(first, second);
			break;
		}
	case '-':
		{
			digit = Subtract(first, second);
			break;
		}
	case '*':
		{
			digit = Multiply(first, second);
			break;
		}
	case '/':
		{
			digit = Divide(first, second);
			break;
		}
	case '^':
		{
			digit = Power(first, second);
			break;
		}
	case '>':
		{
			condition = IsGreater(first, second);
			break;
		}
	case '<':
		{
			condition = IsLess(first, second);
			break;
		}
	case '=':
		{
			condition = AreEquals(first, second);
			break;
		}
	default:
		throw AppException(ErrorMessages::WRONG_INPUT_ERROR);
	}

	return Result(condition, digit);
}

void FileOperations::PrintResult(Result* result)
{
	if (result->IsDigit())
	{
		PrintBigInt(result->digit);
	}
	else
	{
		if(result->condition)
		{
			printf("true\n");
		}
		else
		{
			printf("false\n");
		}
	}
}
