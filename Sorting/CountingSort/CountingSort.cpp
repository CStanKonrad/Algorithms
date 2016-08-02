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
#include <algorithm>

#define MAX_TAB_SIZE 10000000
#define MAX_VAL 1000000

int countingSort_buffer[MAX_TAB_SIZE + 7];
int countingSort_counter[MAX_VAL + 7];
/* let n = _end - _beg + 1
 * let v = max{_arr[_beg], ..., _arr[_end - 1]}
 * O(n + v)
 * Works only for positive + {0} integers <= MAX_VAL
 * stable */
void countingSort(int *beg, int *end)    //[_beg;_end)
{
    int maxVal = 0;
    for (int i = 0; &beg[i] != end; ++i)
    {
		maxVal = std::max(maxVal, beg[i]);
		countingSort_buffer[i] = beg[i];
	}
	
	for (int i = 0; i <= maxVal; ++i)
		countingSort_counter[i] = 0;
	
	for (int i = 0; &beg[i] != end; ++i)
		countingSort_counter[beg[i]]++;
	
	for (int i = 1; i <= maxVal; ++i)
		countingSort_counter[i] += countingSort_counter[i - 1];
		
	for (int i = (end - beg - 1); i >= 0; --i)
	{
		beg[countingSort_counter[countingSort_buffer[i]] - 1] = countingSort_buffer[i];
		--countingSort_counter[countingSort_buffer[i]];
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
    countingSort(&array[beg], &array[end]);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}
