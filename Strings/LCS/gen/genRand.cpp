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
	if (_argc < 4)
	{
		cerr << "Generator: No enough call parameters" << endl;
		return -1;
	}
	srand(stoi(_argv[1]) + 1);
	int n = (rand()%stoi(string(_argv[2]))) + 1;
	int m = (rand()%stoi(string(_argv[3]))) + 1;
	int valBorder= (rand()%stoi(string(_argv[4]))) + 1;
	
	printf ("%d %d\n", n, m);
	for (int i = 1; i <= n; ++i)
	{
		printf("%d ", rand()%valBorder);
	}
	puts("");
	for (int i = 1; i <= m; ++i)
	{
		printf("%d ", rand()%valBorder);
	}
	return 0;
}
