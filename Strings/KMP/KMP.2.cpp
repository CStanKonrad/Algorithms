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

#include <iostream>
#include <algorithm>
#include <string>

const int MAX_INPUT_SIZE = 2*1000000;

int kmpArr[MAX_INPUT_SIZE + 7];	//pref-suf info array
int kmp(std::string _text)
{
	int patLen;
	for (patLen = 0; _text[patLen] != '#'; ++patLen);
	
	int numOfOccurr = 0;
	
	kmpArr[0] = -1;
	for (int i = 1, p; i < _text.size(); ++i)
	{
		p = kmpArr[i - 1];
		while (p != -1 && _text[p + 1] != _text[i])
			p = kmpArr[p];
		
		kmpArr[i] = p;
		if (_text[p + 1] == _text[i])
			++kmpArr[i];
		
		if (kmpArr[i] == patLen - 1)
			++numOfOccurr;
	}
	return numOfOccurr;
}

std::string pattern, text;
int main()
{
	std::cin >> pattern >> text;
	std::cout << kmp(pattern + std::string("#") + text) << std::endl;
	return 0;
}