#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

string pattern[1000000];
int main(int _argc, char *_argv[])
{
	if (_argc < 4)
	{
		cerr << "Generator: No n or m or valBorder provided" << endl;
		return -1;
	}
	srand(stoi(_argv[1]) + 1);
	int n = (rand()%stoi(string(_argv[2]))) + 1;	//numOf patterns
	int valBorder = (rand()%stoi(string(_argv[3]))) + 1;	//len of patterns border 
	cout << n << endl;
	
	for (int i = 0; i < n; i++)
	{
		cout << rand()%valBorder << " ";
	}
	cout << endl;
	int _beg = rand()%(n);
	int _end = rand()%(n + 1);
	if (_beg > _end)
		swap(_beg, _end);
	if (_beg == _end)
		_end++;
	cout << _beg << " " << _end << endl;

	return 0;
}
