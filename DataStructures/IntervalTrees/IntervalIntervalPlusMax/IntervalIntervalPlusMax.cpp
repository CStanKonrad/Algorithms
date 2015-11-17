/*
The MIT License (MIT)

Copyright (c) 2015 CStanKonrad

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
    long long w;
    long long W;
};

template<int log2ReservedMemory = 20>
class CIIPlusMaxTree
{
private:
    int numOfElements;
    int pO2NumOfElements = 0;   //smallest power of 2 wihich is >= than numOfElements
    SNode arrary[(1<<log2ReservedMemory) + 7];

    inline void update(const int &_nodeId, long long _val)
    {
        arrary[_nodeId].w += _val;
        arrary[_nodeId].W = arrary[_nodeId].w;
        if (_nodeId < pO2NumOfElements)
            arrary[_nodeId].W += std::max(arrary[2*_nodeId].W, arrary[2*_nodeId + 1].W);
    }

    long long sumWSmallToRoot(int _id)
    {
        long long result = 0;
        while (_id >= 1)
        {
            result += arrary[_id].w;
            _id /= 2;
        }
        return result;
    }

public:
    void init(int _numOfElements)
    {
        numOfElements = _numOfElements;
        for (pO2NumOfElements = 1; pO2NumOfElements < numOfElements; pO2NumOfElements <<= 1);

        if (pO2NumOfElements > (1<<log2ReservedMemory))
            throw "CIIPlusMaxTree-init(...): Not enough memory reserved";
    }
    void clear()
    {
        for (int i = 1; i <= numOfElements + pO2NumOfElements - 1; i++)
            arrary[i].W = arrary[i].w = 0;
    }
    /*add _val on interval [_beg; _end]; _beg >= 1 */
    void insert(int _beg, int _end, long long _val)
    {
        if ((_beg < 1) || (_beg > numOfElements) || (_end > numOfElements) || (_beg > _end))
            throw "CIIPlusMaxTree-insert(...): _beg or _end - wrong values";

        int i = pO2NumOfElements + _beg - 1;
        int j = pO2NumOfElements + _end - 1;

        update(i, _val);
        if (i != j)
            update(j, _val);

        while (i/2 != j/2)
        {
            if (i%2 == 0)
            {
                update(i + 1, _val);
            }
            if (j%2 == 1)
            {
                update(j - 1, _val);
            }
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
    /*returns maximum value from interval [_beg; _end]; _beg >= 1 */
    long long query(int _beg, int _end)
    {
        if ((_beg < 1) || (_beg > numOfElements) || (_end > numOfElements) || (_beg > _end))
            throw "CIIPlusMaxTree-query(...): _beg or _end - wrong values";

        int i = pO2NumOfElements + _beg - 1;
        int j = pO2NumOfElements + _end - 1;

        long long sumI = sumWSmallToRoot(i / 2);
        long long sumJ = sumWSmallToRoot(j / 2);

        long long result = arrary[i].W + sumI;
        result = std::max(result, arrary[j].W + sumJ);

        while (i/2 != j/2)
        {
            if (i%2 == 0)
            {
                result = std::max(result, arrary[i + 1].W + sumI);
            }
            if (j%2 == 1)
            {
                result = std::max(result, arrary[j - 1].W + sumJ);
            }
            i /= 2;
            j /= 2;
            sumI -= arrary[i].w;
            sumJ -= arrary[j].w;
        }

        return result;
    }
};
CIIPlusMaxTree<20> tree;
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
