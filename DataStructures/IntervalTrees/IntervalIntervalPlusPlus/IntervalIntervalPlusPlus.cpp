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


struct SNode
{
    long long w = 0;
    long long W = 0;
};

/*  log2ReservedMemory: 2^log2ReservedMemory >= 2^(log2(pO2NumOfElements)+1) */
template<int log2ReservedMemory = 21>
class CIIPlusPlusTree
{
private:
    int numOfElements = 0;  //number of elements
    int pO2NumOfElements = 0;   //smallest power of 2 wihich is >= than numOfElements
    int log2pO2NumOfElements = 0;
    int preProcLog2[(1<<log2ReservedMemory) + 7];
    SNode arrary[(1<<log2ReservedMemory) + 7];

    int howManyInSubTree(int _id)
    {
        //int l2;
        //for (l2 = 0; (1<<(l2 + 1)) <= _id; l2++);

        return (1 << (log2pO2NumOfElements - preProcLog2[_id]));

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

    void update(int _id, long long _val)
    {
        arrary[_id].w += _val;
        arrary[_id].W = arrary[_id].w*howManyInSubTree(_id);
        if (_id < pO2NumOfElements)
            arrary[_id].W += arrary[2*_id].W + arrary[2*_id + 1].W;
    }

public:
	CIIPlusPlusTree() {}
    void init(int _numOfElements)
    {
        numOfElements = _numOfElements;
        for (log2pO2NumOfElements = 1; (1 << log2pO2NumOfElements) < numOfElements; log2pO2NumOfElements++);
        pO2NumOfElements = (1 << log2pO2NumOfElements);

        if (pO2NumOfElements > (1<<(log2ReservedMemory - 1)))
            throw "CIIPlusPlusTree-init(...): Not enough memory reserved";

        for (int i = 1, tmpLog2 = 0; i < (1<<log2ReservedMemory) + 7; i++)
        {
            if ((1 << (tmpLog2 + 1)) <=  i)
                tmpLog2++;
            preProcLog2[i] = tmpLog2;
        }
    }
    /*add _val on interval [_beg; _end]; _beg >= 1 */
    void insert(int _beg, int _end, const long long _val)
    {
        if ((_beg < 1) || (_beg > numOfElements) || (_end > numOfElements) || (_beg > _end))
            throw "CIIPlusPlusTree-insert(...): _beg or _end - wrong values";

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
    /*returns sum of values from interval [_beg; _end]; _beg >= 1 */
    long long query(int _beg, int _end)
    {
        if ((_beg < 1) || (_beg > numOfElements) || (_end > numOfElements) || (_beg > _end))
            throw "CIIPlusPlusTree-query(...): _beg or _end - wrong values";

        int i = pO2NumOfElements + _beg - 1;
        int j = pO2NumOfElements + _end - 1;

        long long sumI = sumWSmallToRoot(i / 2);
        long long sumJ = sumWSmallToRoot(j / 2);

        long long result = sumI + arrary[i].W;
        if (i != j)
            result += sumJ + arrary[j].W;

        while (i/2 != j/2)
        {
            if (i%2 == 0)
            {
                result += sumI*howManyInSubTree(i + 1) + arrary[i + 1].W;
            }
            if (j%2 == 1)
            {
                result += sumJ*howManyInSubTree(j - 1) + arrary[j - 1].W;
            }
            i /= 2;
            j /= 2;
            sumI -= arrary[i].w;
            sumJ -= arrary[j].w;
        }

        return result;

    }


};

CIIPlusPlusTree<21> tree;
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
