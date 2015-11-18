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
#include <cstring>

/* returns: number of patterns int _text */
#define KMP_TAB_SIZE 1000000
int kmpTab[KMP_TAB_SIZE + 7];

int KMP(const char *_pattern, const char *_text)
{

    int lenOfPattern = strlen(_pattern);
    int lenOfText = strlen(_text);
    int howMany = 0;

    kmpTab[0] = -1;
    for (int i = 1, p; i < lenOfPattern; i++)
    {
        p = kmpTab[i - 1];
        while (p != -1 && _pattern[p + 1] != _pattern[i])
            p = kmpTab[p];

        if (_pattern[p + 1] == _pattern[i])
            p++;
        kmpTab[i] = p;
    }
    for (int i = 0, p, q = -1; i < lenOfText; i++)
    {
        p = q;
        while (p != -1 && _pattern[p + 1] != _text[i])
            p = kmpTab[p];

        if (_pattern[p + 1] == _text[i])
            p++;
        q = p;

        if (q == lenOfPattern - 1)
            howMany++;
    }
    return howMany;
}

#define MAX_TEXT_LENGTH 1000000

char pattern[KMP_TAB_SIZE + 7], text[MAX_TEXT_LENGTH + 7];
int main()
{

    scanf("%s%s", pattern, text);
    printf("%d\n", KMP(pattern, text));

    return 0;
}
