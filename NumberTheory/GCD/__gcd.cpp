#include <cstdio>
#include <algorithm>

using namespace std;

long long a, b;
int main()
{
    scanf("%lld%lld", &a, &b);
    long long result = __gcd(a, b);
    if (result < 0)
		result = -result;
    printf("%lld\n", result);
    return 0;
}
