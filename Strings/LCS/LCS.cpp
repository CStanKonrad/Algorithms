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

#include <bits/stdc++.h>
using namespace std;

const int MAX_NM = 100;


struct SLCS
{
	int len = 0;
	char dir = 0;	//direction to move to restore sequence (w = up (firstID - 1), a = left (secondID - 1), q = left & up)
}LCSArray[MAX_NM + 7][MAX_NM + 7];

/* strings _a and _b are numbered from 1 */
void calcLCS(const int *_a, const int _a_len, const int *_b, const int _b_len, SLCS (*_out)[MAX_NM + 7])
{
	for (int i = 1; i <= _a_len; ++i)
	{
		for (int j = 1; j <= _b_len; ++j)
		{
			if (_a[i] == _b[j])
			{
				_out[i][j].len = _out[i - 1][j - 1].len + 1;
				_out[i][j].dir = 'q';
			}
			else
			{
				if (_out[i][j - 1].len > _out[i - 1][j].len)
				{
					_out[i][j].len = _out[i][j - 1].len;
					_out[i][j].dir = 'a';
				}
				else
				{
					_out[i][j].len = _out[i - 1][j].len;
					_out[i][j].dir = 'w';
				}
			}
		}
	}
}

void printLCS(const int *_a, const int _a_len, const int *_b, const int _b_len, const SLCS (*_lcsArr)[MAX_NM + 7])
{
	pair<int, int> pos = make_pair(_a_len, _b_len);
	//printf("%d\n", _lcsArr[pos.first][pos.second].len);
	
	vector<int> buffer;
	
	while (pos.first >= 1 && pos.second >= 1)
	{
		if (_lcsArr[pos.first][pos.second].dir == 'q')
		{
			buffer.push_back(_a[pos.first]);
			--pos.first;
			--pos.second;
		}
		else if (_lcsArr[pos.first][pos.second].dir == 'a')
		{
			--pos.second;
		}
		else
		{
			--pos.first;
		}
	}
	reverse(buffer.begin(), buffer.end());
	for (unsigned i = 0; i < buffer.size(); ++i)
	{
		printf("%d ", buffer[i]);
	}
	printf("\n");
	 
}

int n, m;
int a[MAX_NM + 7], b[MAX_NM + 7];
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; ++i)
		scanf("%d", &b[i]);
	calcLCS(a, n, b, m, &LCSArray[0]);
	printLCS(a, n, b, m, &LCSArray[0]);
}
