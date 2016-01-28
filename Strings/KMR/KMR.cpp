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
#include <assert.h>

const int MAX_INPUT_SIZE = 2097152;
const int LOG2_MAX_INPUT_SIZE = 21;

struct SIdentifier
{
	int first = 0;
	int second = 0;
	int inputId;	//position before sorting by < 
	SIdentifier() {}
	SIdentifier(int _first, int _second, int _inputId)
	{
		first = _first;
		second = _second;
		inputId = _inputId;
	}
	
	bool operator < (const SIdentifier &_b) const
	{
		if (first < _b.first)
			return true;
		else if (first > _b.first)
			return false;
		else
			return second < _b.second;
	}
	
	bool operator > (const SIdentifier &_b) const
	{
		if (first > _b.first)
			return true;
		else if (first < _b.first)
			return false;
		else
			return second > _b.second;
	}
};

bool idSort(const SIdentifier &_a, const SIdentifier &_b)
{
	return (_a.inputId < _b.inputId);
}

SIdentifier kmr_id[LOG2_MAX_INPUT_SIZE + 1][MAX_INPUT_SIZE + 7];

void calcNewId(int _i, const std::string &_text)
{
	bool flag;
	int currentId = 0;
	for (int j = 0; j + (1<<_i) - 1 < _text.size(); ++j)
	{
		flag = false;
		if (j + 1 + (1<<_i) - 1 < _text.size() && (kmr_id[_i][j + 1].first != kmr_id[_i][j].first || kmr_id[_i][j + 1].second != kmr_id[_i][j].second))
			flag = true;
		
		kmr_id[_i][j].first = currentId;
		kmr_id[_i][j].second = 0;
		if (flag)
			++currentId;
	}
}

void kmrPreProc(std::string _text)
{
	for (unsigned i = 0; i < _text.size(); ++i)
	{
		kmr_id[0][i] = SIdentifier(_text[i], 0, i);
	}
	
	std::sort(kmr_id[0], &kmr_id[0][_text.size()]);
	calcNewId(0, _text);
	std::sort(kmr_id[0], &kmr_id[0][_text.size()], idSort);
	
	for (int i = 1, j; (1<<i) <= _text.size(); ++i)
	{
		//printf("%d\n", i);
		for (j = 0; j + (1<<i) - 1 < _text.size(); ++j)
		{
			kmr_id[i][j] = SIdentifier(kmr_id[i - 1][j].first, kmr_id[i - 1][j + (1<<(i - 1))].first, j);
			//printf("%d %d\n", kmr_id[i][j].first, kmr_id[i][j].second);
		}
		
		
		std::sort(kmr_id[i], &kmr_id[i][j]);
		calcNewId(i, _text);
		std::sort(kmr_id[i], &kmr_id[i][j], idSort);
	}
}
/* [_b1;_e1] ...; 0 means equal; -1 first is smaller; 1 first is bigger*/
int kmrCompare(int _b1, int _e1, int _b2, int _e2)
{
	int len = std::min(_e1 - _b1 + 1, _e2 - _b2 + 1);
	int p2 = 0;
	while ((1 << (p2 + 1)) <= len)
		++p2;
	
	
	assert(_b1+len-1 - (1 << p2) + 1 >=0 && _b2+len-1 - (1 << p2) + 1 >= 0);
	SIdentifier a(kmr_id[p2][_b1].first, kmr_id[p2][_b1+len-1 - (1 << p2) + 1].first, 0);
	SIdentifier b(kmr_id[p2][_b2].first, kmr_id[p2][_b2+len-1 - (1 << p2) + 1].first, 0);
	//printf("%d %d-%d %d-%d*%d%d %d%d\n", p2, _b1, _e1, _b2, _e2, a.first, a.second, b.first, b.second);
	if (a < b)
		return -1;
	else if (a > b)
		return 1;
	else
	{
		//puts("hello");
		if (_e1 - _b1 + 1 < _e2 - _b2 + 1)
			return -1;
		else if (_e1 - _b1 + 1 > _e2 - _b2 + 1)
			return 1;
		else
			return 0;
	}
	
}

std::string pattern, text;
int main()
{
	std::cin >> pattern >> text;
	std::string combined = pattern + std::string("#") + text;
	kmrPreProc(combined);
	int howManyOccurr = 0;
	for (int i = pattern.size() + 1; i <  combined.size(); ++i)
	{
		if (kmrCompare(0, pattern.size() - 1, i, i + pattern.size() - 1) == 0)
			++howManyOccurr;
	}
	std::cout << howManyOccurr << std::endl;
	int t;
	std::cin >> t;
	for (int i = 0, b1, e1, b2, e2; i < t; ++i)
	{
		std::cin >> b1 >> e1 >> b2 >> e2;
		std::cout << kmrCompare(b1, e1, b2, e2) << std::endl;
	}
	return 0;
}