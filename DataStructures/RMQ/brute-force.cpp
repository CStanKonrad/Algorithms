#include <cstdio>
#include <algorithm>
int tab[1000000 + 7];

int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tab[i]);
    }
    for (int j = 1, a, b; j <= m; j++)
    {
        scanf("%d%d", &a, &b);
        int minVal = tab[a];
        for (int j = a + 1; j <= b; j++)
        {
			minVal = std::min(minVal, tab[j]);
		}
		printf("%d\n", minVal);
    }
    return 0;
}
