#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

int main(int _argc, char *_argv[])
{
	if (_argc < 5)
	{
		cerr << "Generator: No n or m or valBorder provided" << endl;
		return -1;
	}
	srand(stoi(_argv[1]) + 1);
	int a = (rand()%stoi(string(_argv[2])));
	if (rand()%2 == 0)
		a = -a;
	int b = (rand()%stoi(string(_argv[3])));
	if (a == 0 && b == 0)
	{
		b = 1;
	}
	int c = (rand()%stoi(string(_argv[4]))) + 1;
	printf("%d %d %d\n", a, b, c);
	return 0;
}
