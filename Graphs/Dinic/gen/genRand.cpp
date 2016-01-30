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
		cerr << "Generator: No n or m or p provided" << endl;
		return -1;
	}
	srand(stoi(_argv[1]) + 1);
	int n = (rand()%stoi(string(_argv[2]))) + 1;
	int m = (rand()%stoi(string(_argv[3]))) + 1;
	int valBroder = (rand()%stoi(string(_argv[4]))) + 1;
	
	printf("%d %d\n", n, m);
	
	for (int i = 1; i <= m; ++i)
	{
		printf("%d %d %d\n", rand()%n + 1, rand()%n + 1, rand()%valBroder + 1);
	}
	return 0;
}
