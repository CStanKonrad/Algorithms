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

struct SPoint
{
	SPoint() {}
	SPoint(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	int x, y;
	bool operator<(const SPoint &_b) const
	{
		if (y < _b.y)
			return true;
		else if (y > _b.y)
			return false;
		else
		{
			return (x < _b.x);
		}
	}
};

struct SSheep
{
	SPoint pos;
	int id;
	bool operator<(const SSheep &_b) const
	{
		return (pos < _b.pos);
	}
};

long long dist2(const SPoint &_a, const SPoint &_b)
{
	return (_b.x - _a.x)*(_b.x - _a.x) + (_b.y - _a.y)*(_b.y - _a.y);
}

long long detCalc(const SPoint &_mnt, const SPoint &_b, const SPoint &_a)
{
	return (_b.x - _mnt.x)*(_a.y - _mnt.y) - (_b.y - _mnt.y)*(_a.x - _mnt.x);
}


/* in _in shouldn't be any pair of points: a.x == b.x && a.y == b.y && a != b */
double convexHullMonotoneChain(vector<SSheep> &_in, vector<int> &_out)	//places indexes of convexHull verticles form _in in _out and returns circumference as double
{
	_out.clear();
	sort(_in.begin(), _in.end());
	
	for (int i = 0; i < (int)_in.size(); ++i)
	{
		while (_out.size() >= 2 && detCalc(_in[_out[_out.size() - 2]].pos, _in[_out[_out.size() - 1]].pos, _in[i].pos) <= 0)
			_out.pop_back();
		_out.push_back(i);
	}
	int firstSliceSize = _out.size();
	for (int i = _in.size() - 2; i >= 0; --i)
	{
		while ((int)_out.size() > firstSliceSize && detCalc(_in[_out[_out.size() - 2]].pos, _in[_out[_out.size() - 1]].pos, _in[i].pos) <= 0)
			_out.pop_back();
		_out.push_back(i);
	}
	double circumference = 0.0;
	for (int i = 1; i < (int)_out.size(); ++i)
	{
		circumference += sqrt(dist2(_in[_out[i - 1]].pos, _in[_out[i]].pos));
	}
	
	_out.pop_back();
	return circumference;
}

int t;
int n;
map<SPoint, bool> isSheepHere;	//used to make code more clean
vector<SSheep> sheep;
vector<int> result;


int main()
{
	scanf("%d", &t);
	
	while (t--)
	{
		isSheepHere.clear();
		sheep.clear();
		
		scanf("%d", &n);
		SSheep tmp;
		for (int i = 1; i <= n; ++i)
		{
			tmp.id = i;
			scanf("%d%d", &tmp.pos.x, &tmp.pos.y);
			if (isSheepHere.find(tmp.pos) == isSheepHere.end())
			{
				isSheepHere[tmp.pos] = true;
				sheep.push_back(tmp);
			}
		}
		if (sheep.size() == 1)
		{
			puts("0.00");
			puts("1");
		}
		else
		{
			printf("%.2lf\n", convexHullMonotoneChain(sheep, result));
			for (int i = 0; i < (int)result.size(); ++i)
			{
				printf("%d ", sheep[result[i]].id);
			}
			puts("");
		}
		
		
		
	}
	return 0;
}
