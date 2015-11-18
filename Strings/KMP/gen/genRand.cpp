#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

int main(int _argc, char *_argv[])
{
	if (_argc < 4)
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
		if ((rand()%probability) == 0)
		{
			cout << pattern;
			i += pattern.size();
		}
		else
		{
			cout << (char)((rand()%('z'-'a') + 1) + 'a');
		}
		
	}
	cout << endl;
	return 0;
}
