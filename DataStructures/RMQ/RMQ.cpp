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

template<const int log2ReservedMemory = 20>
class CRMQ      //Range Minimum Query
{
private:
    const int numOfElements = (1 << log2ReservedMemory);
    int array[log2ReservedMemory + 1][(1 << log2ReservedMemory) + 7];
    int preProcLog2[(1 << log2ReservedMemory) + 7];
public:
    CRMQ()
    {
        for (int i = 1, tmpLog2 = 0; i <= numOfElements; i++)
        {
            if ((1 << (tmpLog2 + 1)) <= i)
                tmpLog2++;
            preProcLog2[i] = tmpLog2;
        }
    }
    void insert(int _pos, int _val) //_pos >= 1
    {
        array[0][_pos] = _val;
    }
    void calculate()
    {
        for (int i = 1; i <= log2ReservedMemory; i++)
        {
            for (int j = 1; j <= numOfElements; j++)
            {
                array[i][j] = std::min(array[i - 1][j], array[i - 1][std::min(j + (1 << (i - 1)), numOfElements)]);
            }
        }
    }
    int query(int _beg, int _end)   //[_beg;_end]
    {
        int lenLog2 = preProcLog2[(_end - _beg + 1)];
        return std::min(array[lenLog2][_beg], array[lenLog2][_end - (1 << lenLog2) + 1]);
    }

};

CRMQ<20> rmq;
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, tmp; i <= n; i++)
    {
        scanf("%d", &tmp);
        rmq.insert(i, tmp);
    }
    rmq.calculate();
    for (int j = 1, a, b; j <= m; j++)
    {
        scanf("%d%d", &a, &b);
        printf("%d\n", rmq.query(a, b));
    }
    return 0;
}
