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
#include <cstdio>
#include <algorithm>
#include <assert.h>

template <const int ALLOCATED_MEMORY_log2_ = 21, typename T = long long>
class CIIPlusMaxTree
{
private:
	static const int ALLOCATED_MEMORY_ = (1<<ALLOCATED_MEMORY_log2_) + 7;
	struct SNode
	{
		T w = 0;	//modification
		T W = 0;	//max in subtree
	}storage[ALLOCATED_MEMORY_];
	
	int numOfLeaves;
	bool isInited = false;
	
	
	void update(int id, T val)
	{
		storage[id].w += val;
		storage[id].W = storage[id].w;
		if (id < numOfLeaves)
		{
			storage[id].W += std::max(storage[2*id].W, storage[2*id + 1].W);
		}
	}
	
	T sum_w_toRoot(int pos)
	{
		T result = 0;
		while (pos >= 1)
		{
			result += storage[pos].w;
			pos>>=1;
		}
		return result;
	}
	
public:
	/* O(log(2, numOfElements)) */
	void init(int numOfElements)
	{
		for (numOfLeaves = 2; numOfLeaves < numOfElements; numOfLeaves <<= 1);
		
		isInited = true;
	}
	
	/* O(log(2, numOfLeaves));
	 * adds to elements on interval [beg; end] value val */
	void insert(int beg, int end, T val)
	{
		assert(isInited); assert(beg <= end); assert(beg >= 1); assert(end <= numOfLeaves);
		int i = numOfLeaves + beg - 1;
		int j = numOfLeaves + end - 1;
		
		update(i, val);
		if ( i!= j)
			update(j, val);
		
		while (i/2 != j/2)
		{
			if (i%2 == 0)
				update(i + 1, val);
			if (j%2 == 1)
				update(j - 1, val);
			i /= 2;
			j /= 2;
			update(i, 0);
			update(j, 0);
		}
		
		i /= 2;
		while (i >= 1)
		{
			update(i, 0);
			i /= 2;
		}
	}
	
	/* O(log(2, numOfLeaves));
	 * returns maximum on interval [beg; end] */
	T query(int beg, int end)
	{
		assert(isInited); assert(beg <= end); assert(beg >= 1); assert(end <= numOfLeaves);
		
		int i = numOfLeaves + beg - 1;
		int j = numOfLeaves + end - 1;
		
		T sumLeft = sum_w_toRoot(i/2);
		T sumRight = sum_w_toRoot(j/2);
		
		T result = std::max(storage[i].W + sumLeft, storage[j].W + sumRight);
		
		while (i/2 != j/2)
		{
			if (i%2 == 0)
				result = std::max(result, storage[i + 1].W + sumLeft);
			if (j%2 == 1)
				result = std::max(result, storage[j - 1].W + sumRight);
			i /= 2;
			j /= 2;
			sumLeft -= storage[i].w;
			sumRight -= storage[j].w;
		}
		return result;
	}
};



CIIPlusMaxTree<21, long long> tree;
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	tree.init(n);
	for (int i = 1, t, a, b, c; i <= m; i++)
	{
		scanf("%d", &t);
		if (t == 1)
		{
			scanf("%d%d%d", &a, &b, &c);
			tree.insert(a, b, c);
		}
		else
		{
			scanf("%d%d", &a, &b);
			printf("%lld\n", tree.query(a, b));
		}
	}
    return 0;
}
