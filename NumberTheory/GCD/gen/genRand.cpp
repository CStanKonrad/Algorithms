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
	int a = (rand()%stoi(string(_argv[2])));
	if (rand()%2 == 0)
		a = -a;
	int b = (rand()%stoi(string(_argv[3])));
	if (rand()%2 == 0)
		b = -b;
	if (a == 0 && b == 0)
	{
		b = 1;
	}
	printf("%d %d\n", a, b);
	return 0;
}
