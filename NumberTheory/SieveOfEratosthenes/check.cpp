#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

bool writeBug = false;
bool writeFileNames = false;

string waColor = "\033[1;33m";
string clearColor = "\033[0m";

string patStr;
string tesStr;

bool isWhite(char _c)
{
	if (_c == ' ' || _c == '	' || _c == '\n' || _c == '\r')
		return true;
	else
		return false;
}

bool readNext(ifstream &_file, string &_str)
{
	while(isWhite(_file.peek()))
		_file.get();
	if (_file.eof() == false)
	{
		_file >> _str;
		return true;
	}
	else
		return false;
}

bool isPrime(int _num)
{
	for (int i = 2; i < _num; i++)
	{
		if (_num%i == 0)
			return false;
	}
	return true;
}

string cutString(string _str, unsigned int _maxSize = 20)	//cuts string when bigger than _maxSize
{
	string result = "";
	for (int i = 0; i < min<unsigned int>(_maxSize, _str.size()); i++)
	{
		result += _str[i];
	}
	if (_maxSize < _str.size())
		result += "...";
	return result;
}

int main(int _argc, char *_argv[])
{
	for (int i = 1; i < _argc; i++)
	{
		if (_argv[i][0] != '-')
		{
			if (i + 1 < _argc)
			{
				patStr = string(_argv[i]);
				tesStr = string(_argv[i + 1]);
				break;
			}
			else
			{
				cerr << "CMP: cmp/default: No second output file path" << endl;
				return -2;
			}	
		}
		else
		{
			if (strcmp(_argv[i], "-bug") == 0)
				writeBug = true;
			else if (strcmp(_argv[i], "-fname") == 0)
				writeFileNames = true;
			else if (strcmp(_argv[i], "-nocolor") == 0)
			{
				waColor = "";
				clearColor = "";
			}
			else
			{
				cerr << "CMP: No arg called \"" << _argv[i] << "\" exists" << endl;
			}
		}
	}
	if (writeFileNames)
		cout << patStr << "	" << tesStr << endl;
		
	ifstream tes(tesStr.c_str());
	
	if (tes.is_open() == false)
	{
		cerr << "CMP: Can't open: " << tesStr << endl;
		return -2;
	}
	
	int strNr = 1;
	bool tb;
	while (true)
	{
		tb = readNext(tes, tesStr);

		if (tb == false)
			break;
		if (!isPrime(stoi(tesStr)))
		{
			puts("WA");
			return -1;
		}
		strNr++;
	}
	tes.close();
	return 0;
}
