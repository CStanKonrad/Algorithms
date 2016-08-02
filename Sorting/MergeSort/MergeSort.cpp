/*
The MIT License (MIT)

Copyright (c) 2016 CStanKonrad

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <cstdio>

#define MAX_TAB_SIZE 1000000


/* O(nlog(2, end - beg))
 * stable
 * */
int mergeSort_buffer[MAX_TAB_SIZE + 7];
void mergeSort(int *beg, int *end)   //sorts [beg;end): a[i] <= a[j] for i < j
{
	int *mid = &beg[int(end - beg)/2];
	
	if (end - beg > 2)
	{
		mergeSort(beg, mid);
		mergeSort(mid, end);
	}
	
	
	for (int i = 0; &beg[i] != end; ++i)
		mergeSort_buffer[i] = beg[i];
	
	
	int i = 0, j = int(mid - beg), e = 0;
	
	while (&beg[i] != mid && &beg[j] != end)
	{
		if (mergeSort_buffer[i] <= mergeSort_buffer[j])
		{
			beg[e] = mergeSort_buffer[i];
			++i;
		}
		else
		{
			beg[e] = mergeSort_buffer[j];
			++j;
		}
		++e;
	}
	
	while (&beg[i] != mid)
	{
		
		beg[e] = mergeSort_buffer[i];
		++i;
		++e;
	}
	
	while (&beg[j] != end)
	{
		
		beg[e] = mergeSort_buffer[j];
		++j;
		++e;
	}
	return;
}

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
    mergeSort(&array[beg], &array[end]);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}
