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
		cerr << "Generator: No a or b provided" << endl;
		return -1;
	}
	srand(stoi(_argv[1]) + 1);
	int a = (rand()%stoi(string(_argv[2]))) + 1;
	int b = (rand()%stoi(string(_argv[3]))) + 1;
	printf("%d %d\n", a, b);
	return 0;
}
