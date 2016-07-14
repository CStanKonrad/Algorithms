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
		cerr << "Generator: to few arguments" << endl;
		return -1;
	}
	srand(stoi(_argv[1]) + 1);
	int n = rand()%stoi(_argv[2]);
	printf("%d\n", n);
	return 0;
}
