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



constexpr int REAL_SAFE_P2_SIZE_ALLOCATED_MEMORY_(const int ALLOCATED_MEMORY_log2_)
{
	return (1<<ALLOCATED_MEMORY_log2_) + 7;
}

template <const int USED_MEMORY_log2_ = 20, typename T = int>
class CRMQ //Range minimum query
{
private:
	const int USED_MEMORY_ = (1<<USED_MEMORY_log2_);
	
	
	T storage[USED_MEMORY_log2_][REAL_SAFE_P2_SIZE_ALLOCATED_MEMORY_(USED_MEMORY_log2_) ];
	int preProc_log2[ REAL_SAFE_P2_SIZE_ALLOCATED_MEMORY_(USED_MEMORY_log2_) ];
	
	bool isCalculated = false;
public:
	/* O(USED_MEMORY_) */
	CRMQ()
	{
		preProc_log2[1] = 0;
		int l2 = 0;
		for (int i = 2; i <= USED_MEMORY_; ++i)
		{
			if ((1<<(l2 + 1)) <= i)
				++l2;
			preProc_log2[i] = l2;
		}
	}
	
	/* O(1)
	 * pos >= 1 */
	void insert(int pos, T val)
	{
		storage[0][pos] = val;
		isCalculated = false;
	}
	
	/* O(log(USED_MEMORY_)*USED_MEMORY_) */
	void calculate()
	{
		for (int l2 = 1; l2 < USED_MEMORY_log2_; ++l2)
		{
			for (int i = 1; (i + (1<<(l2 - 1)) <= USED_MEMORY_); ++i)
			{
				storage[l2][i] = std::min(storage[l2 - 1][i], storage[l2 - 1][i + (1<<(l2 - 1))]);
			}
		}
		isCalculated = true;
	}
	
	/* O(1)
	 * returns min value on interval [beg;end] */
	T query(int beg, int end)
	{
		assert(isCalculated); assert(beg <= end); assert(1 <= beg); assert(end <= USED_MEMORY_);
		
		int l2 = preProc_log2[(end - beg)];
		return std::min(storage[l2][beg], storage[l2][end - (1<<l2) + 1]);
		
	}

	
};

CRMQ<20> rmq;
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, tmp; i <= n; i++)
    {
        scanf("%d", &tmp);
        rmq.insert(i, tmp);
    }
    rmq.calculate();
    for (int j = 1, a, b; j <= m; j++)
    {
        scanf("%d%d", &a, &b);
        printf("%d\n", rmq.query(a, b));
    }
    return 0;
}
