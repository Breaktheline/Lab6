#include "FileOperations.h"

BigInt* FileOperations::ReadBigInt(FILE* inputFile)
{
	//������� ������� ����
	int ch = fgetc(inputFile);
	while (ch == '0')
	{
		ch = fgetc(inputFile);
	}

	BigInt* bigInt = new BigInt();

	if (ch == '\n')
	{
		bigInt->size = 1;
		return bigInt;
	}

	char stringOfDigits[BigInt::maxDecDigitsCount];
	int stringLength = 0;
	while (ch != '\n')
	{
		stringOfDigits[stringLength] = ch;
		stringLength++;
		ch = fgetc(inputFile);
	}

	int digitLength = BigInt::baseDimentions;
	
	int digitPosition = 0;
	// � ����� ������
	for(int i = stringLength - 1; i >= 0; i -= digitLength)
	{
		// ������� ��������� ������� �����
		int startOfDigit = i - digitLength + 1;
		// ���� ��������� ������� �������������, �� ��������� ����� �����
		if (startOfDigit < 0)
		{
			digitLength += startOfDigit;
			startOfDigit = 0;
		}
		
		//��������� �����
		char digitString[BigInt::baseDimentions];
		for(int j = 0; j < digitLength; j++)
		{
			digitString[j] = stringOfDigits[startOfDigit + j];
		}
		//����� �������, ���� ����� ���������� ����� ������ 
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

