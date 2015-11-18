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

/*  _num - base; _exponent - exponent;
    returns: (_num^_exponent) mod _mod */
long long fastExponentiation(long long _num, unsigned long long _exponent, unsigned long long _mod)
{
    if (_num == 0 && _exponent == 0)
        throw "fastExponentiation: 0^0 error";
    if (_exponent == 0)
        return 1LL;

    long long result = 1;
    _num %= _mod;

    for (unsigned long long i = 1; i <= _exponent; i <<= 1)
    {
        if ((i & _exponent) != 0)
        {
            result *= _num;
            result %= _mod;
        }
        _num *= _num;
        _num %= _mod;
    }
    return result;
}

long long a;
unsigned long long b, c;
int main()
{
    scanf("%lld%llu%llu", &a, &b, &c);
    if (a < 0)
    {
        a = -a;
        a %= c;
        a = c - a;
    }
    printf("%lld\n", fastExponentiation(a, b, c));
}
