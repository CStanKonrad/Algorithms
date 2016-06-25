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
	SPoint(){}
	SPoint(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	int x, y;
};

struct SSegment
{
	SSegment(){}
	SSegment(SPoint _beg, SPoint _end)
	{
		beg = _beg;
		end = _end;
	}
	SPoint beg, end; 
};

long long detCalc(const SPoint &_mnt, const SPoint &_a, const SPoint &_b)
{
	return ((long long)_a.x - _mnt.x)*((long long)_b.y - _mnt.y) - ((long long)_a.y - _mnt.y)*((long long)_b.x - _mnt.x);
}

bool isOnSegment(const SPoint &_p, const SSegment &_seg)
{
	return (min(_seg.beg.x, _seg.end.x) <= _p.x &&  _p.x <= max(_seg.beg.x, _seg.end.x) &&
			min(_seg.beg.y, _seg.end.y) <= _p.y &&  _p.y <= max(_seg.beg.y, _seg.end.y));
}

bool checkCross(const SSegment &_a, const SSegment &_b)	//returns true if crossing detected
{
	long long det1 = detCalc(_a.beg, _a.end, _b.beg);
	long long det2 = detCalc(_a.beg, _a.end, _b.end);
	long long det3 = detCalc(_b.beg, _b.end, _a.beg);
	long long det4 = detCalc(_b.beg, _b.end, _a.end);
	
	if (((det1 < 0 && det2 > 0) || (det1 > 0 && det2 < 0))
	 && ((det3 < 0 && det4 > 0) || (det3 > 0 && det4 < 0)))
	{
		return true;
	}
	if ((det1 == 0 && isOnSegment(_b.beg, _a))
	 || (det2 == 0 && isOnSegment(_b.end, _a))
	 || (det3 == 0 && isOnSegment(_a.beg, _b))
	 || (det4 == 0 && isOnSegment(_a.end, _b)))
	return true;
	
	return false;
}

int n;
int xs, ys, xe, ye, xl, yt, xr, yb;
int main()
{
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d%d%d%d%d%d%d%d", &xs, &ys, &xe, &ye, &xl, &yt, &xr, &yb);
		SSegment line(SPoint(xs, ys), SPoint(xe, ye));
		/* if line is inside rectangle */
		if (min(xl, xr) < line.beg.x && line.beg.x < max(xl, xr)
		&& min(yt, yb) < line.beg.y && line.beg.y < max(yt, yb))
			puts("T");
		else
		{
			if (checkCross(line, SSegment(SPoint(xl, yb), SPoint(xr, yb))) || checkCross(line, SSegment(SPoint(xr, yb), SPoint(xr, yt)))
			 || checkCross(line, SSegment(SPoint(xr, yt), SPoint(xl, yt))) || checkCross(line, SSegment(SPoint(xl, yt), SPoint(xl, yb))))
				puts("T");
			else
				puts("F");
		}
	}
}
