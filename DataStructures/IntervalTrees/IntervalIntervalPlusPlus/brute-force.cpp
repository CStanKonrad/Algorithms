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
	long long sum = 0;
	for (int i = _beg; i <= _end; i++)
	{
		sum += tab[i];
	}
	return sum;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, t, a, b, c; i <= m; i++)
    {

		scanf("%d", &t);
		if (t == 1)
		{
			scanf("%d%d%d", &a, &b, &c);
			add(a, b, c);
		}
		else
		{
			scanf("%d%d", &a, &b);
			printf("%lld\n", query(a, b));
		}
    }
    return 0;
}
