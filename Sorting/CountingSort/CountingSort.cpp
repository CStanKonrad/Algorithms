/*
The MIT License (MIT)

Copyright (c) 2015 CStanKonrad

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

int countingSortBufferArr[MAX_TAB_SIZE + 7];
int countingSortCountingArr[MAX_VAL + 7];
void countingSort(int _beg, int _end, int *_arr)    //[_beg;_end)
{
    int maxVal = _arr[_beg];
    for (int i = _beg; i < _end; i++)
        if (_arr[i] > maxVal)
            maxVal = _arr[i];

    for (int i = 0; i <= maxVal; i++)
        countingSortCountingArr[i] = 0;

    for (int i = _beg; i < _end; i++)
    {
        countingSortBufferArr[i] = _arr[i];
        countingSortCountingArr[_arr[i]]++;
    }
    for (int i = 1; i <= maxVal; i++)
        countingSortCountingArr[i] += countingSortCountingArr[i - 1];

    for (int i = _end - 1; i >= _beg; i--)
    {
        countingSortCountingArr[countingSortBufferArr[i]]--;
        _arr[countingSortCountingArr[countingSortBufferArr[i]] + _beg] = countingSortBufferArr[i];
    }

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
    countingSort(beg, end, array);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}
