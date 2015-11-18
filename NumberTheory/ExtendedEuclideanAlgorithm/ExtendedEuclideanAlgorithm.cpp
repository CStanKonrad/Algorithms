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



struct SExEuclideanResult
{
    SExEuclideanResult() {}
    SExEuclideanResult(long long _x, long long _y, long long _d)
    {
        x = _x;
        y = _y;
        d = _d;
    }
    long long x;
    long long y;
    long long d;  //d = gcd(a, b);
};
/* should be used only for positive numbers */
SExEuclideanResult exEuclideanAlgorithm(long long _a, long long _b)
{
    if (_b == 0)
        return SExEuclideanResult(1, 0, _a);
    else
    {
        SExEuclideanResult buf = exEuclideanAlgorithm(_b, _a%_b);
        return SExEuclideanResult(buf.y, buf.x - buf.y*(_a/_b), buf.d);
    }
}

long long a, b;
int main()
{
    scanf("%lld%lld", &a, &b);
    SExEuclideanResult result = exEuclideanAlgorithm(a, b);
    printf("%lld %lld %lld\n", result.x, result.y, result.d);
    return 0;
}
