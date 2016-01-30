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

Based on ILOCAMP lecture
*/

#include <cstdio>
#include <vector>

const int MAX_NUM_OF_LEFT_V = 50000;
const int MAX_NUM_OF_RIGHT_V = 50000;

struct SLeftVerticle
{
	std::vector<int> adj;	//Adjacent
	bool isMatched = false;
	bool isVisited = false;
} left[MAX_NUM_OF_LEFT_V + 7];

int rightVertMatch[MAX_NUM_OF_RIGHT_V + 7];	//0 means unmatched else id of matched left verticle

int n, m, p;	//number of left, right verticles and number of edges

bool dfs(int _leftId)
{
	left[_leftId].isVisited = true;
	for (unsigned i = 0, r; i < left[_leftId].adj.size(); ++i)
	{
		r = left[_leftId].adj[i];
		if (rightVertMatch[r] == false || (!left[rightVertMatch[r]].isVisited && dfs(rightVertMatch[r])))
		{
			rightVertMatch[r] = _leftId;
			left[_leftId].isMatched = true;
			return true;
		}
	}
	return false;
}

int turboMatching()
{
	bool find;
	int maximumMatching = 0;
	do
	{
		find = false;
		for (int i = 1; i <= n; ++i)
		{
			if (!left[i].isVisited && !left[i].isMatched && dfs(i))
			{
				++maximumMatching;
				find = true;
			}
		}
		
		for (int i = 1; i <= n; ++i)
			left[i].isVisited = false;
		
	} while(find == true);	//while I can extend matching
	return maximumMatching;
}

int main()
{
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 1, l, r; i <= p; ++i)
	{
		scanf("%d%d", &l, &r);
		left[l].adj.push_back(r);
	}
	int maximumMatching = turboMatching();	//maximumNumberOfMatches
	printf("%d\n", maximumMatching);
	return 0;
}