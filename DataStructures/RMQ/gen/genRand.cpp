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
	int n = (rand()%stoi(string(_argv[2]))) + 1;
	int m = (rand()%stoi(string(_argv[3]))) + 1;
	int valBorder = stoi(string(_argv[4]));
	printf("%d %d\n", n, m);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", rand()%valBorder);
	}
	puts("");
	
	for (int i = 0, a, b; i < n; i++)
	{
		a = rand()%n + 1;
		b = rand()%n + 1;
		if (a > b)
			swap(a, b);
		printf("%d %d\n", a, b);
	}
	return 0;
}
