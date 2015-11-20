#include <cstdio>
#include <algorithm>

#define MAX_TAB_SIZE 1000000

int array[MAX_TAB_SIZE + 7];
int n;
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    int beg, end;
    scanf("%d%d", &beg, &end);
    std::sort(array + beg, array + end);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}
