#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cstdint>
#include <winsock.h>
#include <cstring>
#include <stdio.h>
#include <conio.h>
#include <locale.h>

using namespace std;

void From10to2(int number, int methodOfByte[8])
{
	int countOfByte = 7;
		while ( number != 1)
		{
			methodOfByte[countOfByte] = number % 2;
			countOfByte--;
			number = number / 2;
		}
		methodOfByte[countOfByte] = number;
}

void CountTheNumber(int methodOfByte[8], int &outputNumber)
{
	const int scaleOfNotation = 2;
	for ( int i = 0; i < 8; i++)
	{
		if ( methodOfByte[i] == 1)
		{
			outputNumber += int(pow(scaleOfNotation, i));
		}
	}
}

void WriteData(int outputNumber, ofstream &outputFile, bool errorInputNumber)
{
	if ( outputFile.is_open())
	{
		if ( errorInputNumber)
		{
			outputFile << "error in input" << endl;
		}
		else
		{
			outputFile << outputNumber << endl;
		}	
		if ( !outputFile)
		{
			cout << "An error occurred when writing outputFile" << endl;
		}
	}
	else
	{
		cout << "Failed to open output.txt for writing" << endl;
	}
	outputFile.close();
}

int main(int argc, char * argv[])
{
	int inputNumber;
	int outputNumber = 0;
	int methodOfByte[8] = {0,0,0,0,0,0,0,0};
	bool errorInputNumber = false;
	
	setlocale(LC_ALL, "");

	if ( argc < 3)
	{
		printf("Ошибка! Не хватает аргументов для работы программы. Параметры командной строки: flipbyte.exe outputFile number \n");
		return 1;
	}
	else if ( argc > 3)
	{
		printf("Ошибка! Слишком много аргументов для работы программы. Параметры командной строки: flipbyte.exe outputFile number \n");
		return 1;
	}

	ofstream outputFile(argv[1]);

	inputNumber = atoi(argv[2]);

	if ( inputNumber > 0 && inputNumber <= 255)
	{
		From10to2(inputNumber, methodOfByte);
		CountTheNumber(methodOfByte, outputNumber);
	}
	else
	{
		if ( inputNumber != 0)
		{
			errorInputNumber = true;
		}
	}
	WriteData(outputNumber, outputFile, errorInputNumber);
	return 1;
}