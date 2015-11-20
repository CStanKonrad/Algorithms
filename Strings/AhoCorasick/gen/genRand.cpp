#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

string pattern[1000000];
int main(int _argc, char *_argv[])
{
	if (_argc < 5)
	{
		cerr << "Generator: No n or m or valBorder provided" << endl;
		return -1;
	}
	srand(stoi(_argv[1]) + 1);
	int n = (rand()%stoi(string(_argv[2]))) + 1;	//numOf patterns
	int m = (rand()%stoi(string(_argv[3]))) + 1;	//len of patterns border 
	int q = (rand()%stoi(string(_argv[4]))) + 1;	//len of text border
	int probability= (rand()%stoi(string(_argv[5]))) + 1;
	cout << n << endl;
	for (int i = 0; i < n; i++)
	{
		pattern[i] = "";
		for (int j = 0; j < m; j++)
		{
			pattern[i] += (char)((rand()%('z'-'a') + 1) + 'a');
		}
		//cout << pattern[i] << endl;
	}
	
	
	for (int i = 0; i < q; i++)
	{
		if (((rand()%probability) == 0))
		{
			int id = rand()%n;
			if (i + pattern[id].size() <= q)
			{
				cout << pattern[id];
				i += pattern[id].size();
			}
		}
		else
		{
			cout << (char)((rand()%('z'-'a') + 1) + 'a');
		}
		
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << pattern[i] << endl;
	}
	return 0;
}
