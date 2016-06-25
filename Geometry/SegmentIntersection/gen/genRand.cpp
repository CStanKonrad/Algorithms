#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

int main(int _argc, char *_argv[])
{
	if (_argc < 3)
	{
		cerr << "Generator: No n or valBorder provided" << endl;
		return -1;
	}
	srand(stoi(_argv[1]) + 1);
	int n = (rand()%stoi(string(_argv[2]))) + 1;
	//int nBorder = (rand()%stoi(string(_argv[3]))) + 1;
	int valBorder = (rand()%stoi(string(_argv[3]))) + 1;
	printf("%d\n", n);
	while (n--)
	{
		for (int i = 1; i <= 8; ++i)
		{
			printf("%d ", (rand()%valBorder));
		}
		puts("");
	}
	return 0;
}
