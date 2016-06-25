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
		cerr << "Generator: No t or nBorder or valBorder provided" << endl;
		return -1;
	}
	srand(stoi(_argv[1]) + 1);
	int t = (rand()%stoi(string(_argv[2]))) + 1;
	int nBorder = (rand()%stoi(string(_argv[3]))) + 1;
	int valBorder = (rand()%stoi(string(_argv[4]))) + 1;
	printf("%d\n", t);
	while (t--)
	{
		int n = (rand()%nBorder) + 1;
		printf("%d\n", n);
		for (int i = 1; i <= n; ++i)
		{
			printf("%d %d\n", (rand()%valBorder) - (rand()%valBorder), (rand()%valBorder) - (rand()%valBorder));
		}
		puts("");
	}
	return 0;
}
