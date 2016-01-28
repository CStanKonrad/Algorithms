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

struct SNode
{
    long long w;    //added value
    long long W;    //maximum in subtree
};
/*  log2ReservedMemory: 2^log2ReservedMemory >= 2^(log2(pO2NumOfElements)+1) */
template<int log2ReservedMemory=21>
class CIIPlusMaxTree
{
private:
	SNode array[(1<<log2ReservedMemory) + 7];
	bool isInited = false;
	int numOfLeaves;	//number of leaves in tree
	int numOfElements;	//number of used leaves
	
	void update(const int _nodeId, const long long _val)
	{
		array[_nodeId].w += _val;
		array[_nodeId].W = array[_nodeId].w;
		
		if (_nodeId < numOfLeaves)
			array[_nodeId].W += std::max(array[2*_nodeId].W, array[2*_nodeId + 1].W);
		
		return;
	}
	
	long long sumWSmallToRoot(int _nodeId)
	{
		long long result = 0;
		while (_nodeId >= 1)
		{
			result += array[_nodeId].w;
			_nodeId /= 2;
		}
		return result;
	}
	
public:
	void init(int _numOfElements)
	{
		numOfElements = _numOfElements;
		for (numOfLeaves = 1; numOfLeaves < numOfElements; numOfLeaves <<= 1);
		
		if (numOfLeaves + numOfLeaves - 1 > (1<<log2ReservedMemory))
			throw "CIIPlusMaxTree::init: Too many elements";
		
		isInited = true;
	}
	/*add to all elements from interval [_beg;_end] value _val; _beg >= 1*/
	void insert(int _beg, int _end, long long _val)
	{
		if (isInited == false)
			throw "CIIPlusMaxTree::insert: tree not initialized";
		if (_beg <= 0 || _beg > numOfElements || _end <= 0 || _end > numOfElements || _end < _beg)
			throw "CIIPlusMaxTree::insert: wrong _beg or _end values";
		
		int i = numOfLeaves + _beg - 1;
		int j = numOfLeaves + _end - 1;
		
		update(i, _val);
		if (i != j)
			update(j, _val);
		
		while (i/2 != j/2)
		{
			if (i%2 == 0)
				update(i + 1, _val);
			if (j%2 == 1)
				update(j - 1, _val);
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
		return;
	}
	/*sum of elements from interval [_beg;_end]; _beg >= 1*/
	long long query(int _beg, int _end)
	{
		if (isInited == false)
			throw "CIIPlusMaxTree::query: tree not initialized";
		if (_beg <= 0 || _beg > numOfElements || _end <= 0 || _end > numOfElements || _end < _beg)
			throw "CIIPlusMaxTree::query: wrong _beg or _end values";
		
		int i = numOfLeaves + _beg - 1;
		int j = numOfLeaves + _end - 1;
		
		long long rootSumI = sumWSmallToRoot(i / 2);
		long long rootSumJ = sumWSmallToRoot(j / 2);
		
		long long result = std::max(rootSumI + array[i].W, rootSumJ + array[j].W);
		
		while (i/2 != j/2)
		{
			if (i%2 == 0)
				result = std::max(result, rootSumI + array[i + 1].W);
			
			if (j%2 == 1)
				result = std::max(result, rootSumJ + array[j - 1].W);
			
			i /= 2;
			j /= 2;
			rootSumI -= array[i].w;
			rootSumJ -= array[j].w;
		}
		return result;
	}
	
};
CIIPlusMaxTree<21> tree;
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	tree.init(n);
	for (int i = 1, t, a, b, c; i <= m; i++)
	{
		try
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
		catch(const char *_err)
		{
			printf("ERROR:%s\n", _err);
			return -1;
		}
	}
    return 0;
}
