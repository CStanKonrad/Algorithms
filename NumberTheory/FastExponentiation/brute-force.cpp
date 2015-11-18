#include <cstdio>
#include <algorithm>

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

