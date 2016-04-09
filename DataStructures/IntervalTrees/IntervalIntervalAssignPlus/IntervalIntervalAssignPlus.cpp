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
#include <bits/stdc++.h>


struct SNode
{
	long long w = 0;
	long long W = 0;
	bool isNew = 0;
};

template<int log2ReservedMemory=21>
class CIIAssignPlusTree
{
private:
	SNode array[(1 << 21) + 7];
	bool isInited = false;
	
	int numOfLeaves;	//number of leaves in tree
	int log2NumOfLeaves;
	int numOfElements;	//number of used leaves
	
	void updateNew(const int _nodeId, const long long _val, const int _howManyInSubTree)
	{
		array[_nodeId].w = _val;
		array[_nodeId].isNew = true;
		array[_nodeId].W = _howManyInSubTree*array[_nodeId].w;
		
		//if (_nodeId < numOfLeaves)
			//array[_nodeId].W += array[2*_nodeId].W + array[2*_nodeId + 1].W;
		
		return;
	}
	void updateOld(const int _nodeId)
	{
		
		if (_nodeId < numOfLeaves)
		{
			
			array[_nodeId].W = array[2*_nodeId].W + array[2*_nodeId + 1].W;
			//printf("uo:%d:%lld %lld %lld\n", _nodeId, array[2*_nodeId].W, array[2*_nodeId + 1].W, array[_nodeId].W);
		}
		else
			array[_nodeId].W = array[_nodeId].w;
		
		return;
	}
	
	void pushDownNew(int _beg, int _end, int _p2, int _pos = 1)	
	{
		//printf("[%d %d]: p2:%d pos:%d\n", _beg, _end, _p2, _pos);
		if ((_pos*(1<<_p2) > _beg && _pos*(1<<_p2) + (1<<_p2) - 1 < _end) || !(((_pos*(1<<_p2) >= _beg && _pos*(1<<_p2) <= _end) || (_pos*(1<<_p2) + (1<<_p2) - 1 >= _beg && _pos*(1<<_p2) + (1<<_p2) - 1 <= _end)) || (_pos*(1<<_p2) <= _beg && _pos*(1<<_p2) + (1<<_p2) - 1 >= _end)) || _pos > numOfLeaves)	//_pos represents interval inside [_beg;_end] or _pos represents interval without common points with [_beg;_end]
			return;
		//printf("%d====ok\n", _pos);
		//if (_pos >= numOfLeaves)
			//return;
		
		if (array[_pos].isNew == true)
		{
			//puts("new");
			//array[2*_pos + 1].w = array[2*_pos].w = array[_pos].w;
			updateNew(2*_pos + 1, array[_pos].w, (1<<(_p2 - 1)));
			updateNew(2*_pos, array[_pos].w, (1<<(_p2 - 1)));
			//array[2*_pos + 1].isNew = array[2*_pos].isNew = true;
			array[_pos].isNew = false;
			
		}
		updateOld(_pos);
		pushDownNew(_beg, _end, _p2 - 1, 2*_pos);
		pushDownNew(_beg, _end, _p2 - 1, 2*_pos + 1);
		
	}
public:
	void init(int _numOfElements)
	{
		numOfElements = _numOfElements;
		for (numOfLeaves = 1; numOfLeaves < numOfElements; numOfLeaves <<= 1)
			++log2NumOfLeaves;
		
		if (numOfLeaves + numOfLeaves - 1 > (1<<log2ReservedMemory))
			throw "CIIPlusPlusTree::init: Too many elements";
		
		isInited = true;
	}
	void insert(int _beg, int _end, long long _val)
	{
		if (isInited == false)
			throw "CIIPlusPlusTree::insert: tree not initialized";
		if (_beg <= 0 || _beg > numOfElements || _end <= 0 || _end > numOfElements || _end < _beg)
			throw "CIIPlusPlusTree::insert: wrong _beg or _end values";
		
		//printf("=-=-=-=-=-=%d-%d\n", _beg, _end);
		int i = numOfLeaves + _beg - 1;
		int j = numOfLeaves + _end - 1;
		//std::cerr << log2NumOfLeaves << std::endl;
		pushDownNew(i, j, log2NumOfLeaves);
		
		
		int howManyInSubTree = 1;
		
		updateNew(i, _val, howManyInSubTree);
		if (i != j)
			updateNew(j, _val, howManyInSubTree);
		
		while (i/2 != j/2)
		{
			//printf("%d=%lld %lld %lld\n", i, array[i].W, array[2*i].W, array[2*i + 1].W);
			//printf("%d=%lld %lld %lld\n", j, array[j].W, array[2*j].W, array[2*j + 1].W);
			if (i%2 == 0)
				updateNew(i + 1, _val, howManyInSubTree);
			if (j%2 == 1)
				updateNew(j - 1, _val, howManyInSubTree);
			i /= 2;
			j /= 2;
			array[i].isNew = array[j].isNew = false;
			howManyInSubTree *= 2;
			updateOld(i);
			updateOld(j);
		}
		
		updateOld(i);
		i /= 2;
		howManyInSubTree *= 2;
		while (i >= 1)
		{
			array[i].isNew = array[j].isNew = false;
			updateOld(i);
			i /= 2;
			howManyInSubTree *= 2;
		}
		return;
		
		
		
	}
	
	long long query(int _beg, int _end)
	{
		//return array[1].W;
		if (isInited == false)
			throw "CIIPlusPlusTree::query: tree not initialized";
		if (_beg <= 0 || _beg > numOfElements || _end <= 0 || _end > numOfElements || _end < _beg)
			throw "CIIPlusPlusTree::query: wrong _beg or _end values";
		
		
		int i = numOfLeaves + _beg - 1;
		int j = numOfLeaves + _end - 1;
		pushDownNew(i, j, log2NumOfLeaves);
		//pushDownNew(_beg, _end, log2NumOfLeaves);
		
		int howManyInSubTree = 1;
		
		long long result = array[i].W;
		if (i != j)
			result += array[j].W;
		//printf("%d=%lld %lld %lld\n", i, array[i].W, array[2*i].W, array[2*i + 1].W);
		//printf("%d=%lld %lld %lld\n", j, array[j].W, array[2*j].W, array[2*j + 1].W);
		while (i/2 != j/2)
		{
			//printf("%d=%lld %lld %lld\n", i, array[i].W, array[2*i].W, array[2*i + 1].W);
			//printf("%d=%lld %lld %lld\n", j, array[j].W, array[2*j].W, array[2*j + 1].W);
			//if (i%2 == 0)
			if (i%2 == 0)
			{
				//updateOld(i + 1);
				result += array[i + 1].W;
			}
			
			if (j%2 == 1)
			{
				//updateOld(j - 1);
				result += array[j - 1].W;
			}
			
			i /= 2;
			j /= 2;
			
			howManyInSubTree *= 2;
			//updateOld(i);
			//updateOld(i);

		}
		return result;
		
	}
};

CIIAssignPlusTree<21> tree;
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
