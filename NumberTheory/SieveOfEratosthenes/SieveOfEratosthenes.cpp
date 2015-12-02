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
#include <cmath>

#define MAX_VAL 10000000


int sieveOfEratosthenesSmallestDivisor[MAX_VAL + 7];
void sieveOfEratosthenes(int _end)  //[2;_end]
{
    sieveOfEratosthenesSmallestDivisor[1] = 1;
    int sqrtVal = ceil(sqrt(_end));

    for (int i = 2, j; i <= sqrtVal; i++)
    {
        if (sieveOfEratosthenesSmallestDivisor[i] != 0)
            continue;
        for (j = i*i; j <= _end; j += i)
        {
            if (sieveOfEratosthenesSmallestDivisor[j] == 0)
                sieveOfEratosthenesSmallestDivisor[j] = i;
        }
    }
}

void printPrimes(int _end)
{
    for (int i = 2; i <= _end; i++)
    {
        if (sieveOfEratosthenesSmallestDivisor[i] == 0)
            printf("%d ", i);
    }
}


int main()
{
    sieveOfEratosthenes(MAX_VAL);
    printPrimes(MAX_VAL);
    return 0;
}
