#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

int R(int _beg, int _end)	//[_beg; _end]
{
	return (rand()%(_end - _beg + 1) + _beg);
}

int main(int _argc, char *_argv[])
{
	if (_argc < 6)
	{
		cerr << "Generator: No n or m or valBorder provided" << endl;
		return -1;
	}
	srand(stoi(_argv[1]) + 1);
	int n = (rand()%stoi(string(_argv[2]))) + 1;
	int m = (rand()%stoi(string(_argv[3]))) + 1;
	int probability= (rand()%stoi(string(_argv[4]))) + 1;
	
	string pattern = "";
	for (int i = 0; i < n; i++)
	{
		pattern += (char)((rand()%('z'-'a') + 1) + 'a');
	}
	cout << pattern << " ";
	for (int i = 0; i < m; i++)
	{
		if (((rand()%probability) == 0) && (i + pattern.size() <= m))
		{
			cout << pattern;
			i += pattern.size() - 1;
		}
		else
		{
			cout << (char)((rand()%('z'-'a') + 1) + 'a');
		}
		
	}
	cout << endl;
	int t = (rand()%(stoi(string(_argv[5])))) + 1;
	cout << t << endl;
	for (int i = 0; i < t; ++i)
	{
		int b1 = R(0, n + m);
		int e1 = R(b1, n + m);
		int b2 = R(0, n + m);
		int e2 = R(b2, n + m);
		cout << b1 << " " << e1 << " " << b2 << " " << e2 << endl;
	}
	return 0;
}
