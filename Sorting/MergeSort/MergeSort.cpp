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

#define MAX_TAB_SIZE 1000000



int mergeSortArrary[MAX_TAB_SIZE + 7];
void mergeSort(int _beg, int _end, int *_arr)   //sorts [_beg;_end): a[i] <= a[j] for i < j
{
    int mid = (_end + _beg) / 2;
    if (_end - _beg > 2)
    {
        mergeSort(_beg, mid, _arr);
        mergeSort(mid, _end, _arr);
    }

    for (int i = _beg; i < _end; i++)
        mergeSortArrary[i] = _arr[i];

    int i = _beg;
    int j = mid;
    int e = _beg;

    while (i < mid && j < _end)
    {
        if (mergeSortArrary[i] <= mergeSortArrary[j])
        {
            _arr[e] = mergeSortArrary[i];
            e++;
            i++;
        }
        else
        {
            _arr[e] = mergeSortArrary[j];
            e++;
            j++;
        }
    }

    while (i < mid)
    {
        _arr[e] = mergeSortArrary[i];
        e++;
        i++;
    }
    while (j < _end)
    {

        _arr[e] = mergeSortArrary[j];
        e++;
        j++;
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
    mergeSort(beg, end, array);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}
