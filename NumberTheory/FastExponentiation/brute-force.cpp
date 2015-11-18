#include <cstdio>
#include <algorithm>

#define MAX_N 1000000

int n, m;
long long tab[MAX_N + 7];

void add(int _beg, int _end, long long _val)
{
	for (int i = _beg; i <= _end; i++)
	{
		tab[i] += _val;
	}
}

long long query(int _beg, int _end)
{
	long long maximum = tab[_beg];
	for (int i = _beg + 1; i <= _end; i++)
	{
		maximum = std::max(maximum, tab[i]);
	}
	return maximum;
}

long long a;
unsigned long long b, c;
int main()
{
    scanf("%lld%llu%llu", &a, &b, &c);
    if (a == 0 && b == 0)
		throw "Undefined";
    if (b == 0)
	{
		puts("1");
		return 0;
	}
	if (a < 0)
    {
        a = -a;
        a %= c;
        a = c - a;
    }
	long long  result = 1;
	a %= c;
	for (unsigned long long i = 1; i <= b; i++)
	{
		result *= a;
		result %= c;
	}
    
    printf("%lld\n", result);
}

