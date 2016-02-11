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

void WriteData(string &text, ofstream &outputFile)
{
	outputFile << text;		
	text = "";
}

void SearchSubStr(string line, string subStrForChange, string subStrForSearch, ofstream &outputFile)
{
	size_t it;
	string text;
	for ( it = line.find(subStrForSearch, 0); it != string::npos; it = line.find(subStrForSearch, 0))
	{
		line.replace(it, subStrForSearch.size(), subStrForChange);
		text += line.substr(0, it + subStrForChange.size());
		line = line.substr(it + subStrForChange.size(), line.size());
	}
	text += line + "\n";
	WriteData(text, outputFile);
}

void ReadData(char * argv[])
{
	string line;
	string subStrForSearch = argv[3];
	string subStrForChange = argv[4];

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	if ( inputFile.is_open() && outputFile.is_open())
	{
		while ( !inputFile.eof())
		{
			getline(inputFile, line);
			SearchSubStr(line, subStrForChange, subStrForSearch, outputFile);	
		}
	}
	else
	{
		cout << "Failed to open input file or output file for reading" << endl;
	}
	outputFile.flush();
}

int main(int argc, char * argv[])
{	
	setlocale(LC_ALL, "");

	if ( argc < 5)
	{
		printf("Ошибка! Не хватает аргументов для работы программы. Параметры командной строки: replace.exe inputFile outputFile searchString replaceString \n");
		return 1;
	}

	else if ( argc > 5)
	{
		printf("Ошибка! Слишком много аргументов для работы программы. Параметры командной строки: replace.exe inputFile outputFile searchString replaceString \n");
		return 1;
	}

	ReadData(argv);
	return 1;
}