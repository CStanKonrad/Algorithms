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
#include <assert.h>

constexpr int REAL_SAFE_P2_SIZE_ALLOCATED_MEMORY_(const int ALLOCATED_MEMORY_log2_)
{
	return (1<<ALLOCATED_MEMORY_log2_) + 7;
}

template <const int ALLOCATED_MEMORY_log2_ = 21, typename T = long long>
class CIIPlusPlusTree
{
private:
	struct SNode
	{
		T w = 0;	//modification
		T W = 0;	//sum in subtree
	}storage[REAL_SAFE_P2_SIZE_ALLOCATED_MEMORY_(ALLOCATED_MEMORY_log2_)];
	
	int numOfLeaves;
	bool isInited = false;
	
	
	void recurInsert(int pos, int beg, int end, T val, int p2)
	{
		int left = pos*p2;
		int right = pos*p2 + p2 - 1;
		
		if ((right < beg) || (left > end))
		{
			return;
		}
		else if ((beg <= left) && (right <= end))
		{
			storage[pos].w += val;
			storage[pos].W += val*p2;
			return;
		}
		else
		{
			recurInsert(2*pos, beg, end, val, p2>>1);
			recurInsert(2*pos + 1, beg, end, val, p2>>1);
			
			storage[pos].W = storage[2*pos].W + storage[2*pos + 1].W;
			storage[pos].W += p2*storage[pos].w;
		}
	}
	
	T recurQuery(int pos, int beg, int end, int p2, T sum)
	{
		int left = pos*p2;
		int right = pos*p2 + p2 - 1;
		
		if ((right < beg) || (left > end))
		{
			return 0;
		}
		else if ((beg <= left) && (right <= end))
		{
			return storage[pos].W + sum*p2;
		}
		else
		{
			sum += storage[pos].w;
			return recurQuery(2*pos, beg, end, p2>>1, sum) + recurQuery(2*pos + 1, beg, end, p2>>1, sum);
		}
	}
	
public:
	/* O(log(2, numOfElements)) */
	void init(int numOfElements)
	{
		for (numOfLeaves = 2; numOfLeaves < numOfElements; numOfLeaves <<= 1);
		
		isInited = true;
	}
	
	/* O(log(2, numOfLeaves));
	 * adds to elements on interval [beg; end] value val
	 * beg >= 1
	 * end <= numOfLeaves */
	void insert(int beg, int end, T val)
	{
		assert(isInited); assert(beg <= end); assert(beg >= 1); assert(end <= numOfLeaves);
		beg = numOfLeaves + beg - 1;
		end = numOfLeaves + end - 1;
		
		recurInsert(1, beg, end, val, numOfLeaves);
	}
	
	/* O(log(2, numOfLeaves));
	 * returns sum of elements on interval [beg; end]
	 * beg >= 1
	 * end <= numOfLeaves */
	T query(int beg, int end)
	{
		assert(isInited); assert(beg <= end); assert(beg >= 1); assert(end <= numOfLeaves);
		
		beg = numOfLeaves + beg - 1;
		end = numOfLeaves + end - 1;
		
		
		return recurQuery(1, beg, end, numOfLeaves, 0);
		
	}
};



CIIPlusPlusTree<21, long long> tree;
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
