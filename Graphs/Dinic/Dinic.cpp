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

Based on was.zaa.mimuw lecture
*/

#include <cstdio>
#include <limits>
#include <vector>
#include <queue>

const int MAX_N = 5000;
const int INT_INF = std::numeric_limits<int>::max();

int N, M;

struct SVerticle
{
	int ptr;	//to not visit one edge two or more times at one phase
	int dist;	//from source
	std::vector<int> adj;	//Adjacent
}V[MAX_N + 7];

long long capacity[MAX_N + 7][MAX_N + 7];	//capacity of edge

long long dfs(int _pos, int _des, long long _minCapacity)	//position, destination
{
	long long result = 0;
	if (_pos == _des || _minCapacity == 0)
		return _minCapacity;
	
	for (int &i = V[_pos].ptr, e; i < V[_pos].adj.size(); ++i)
	{
		e = V[_pos].adj[i];
		if (V[_pos].dist + 1 == V[e].dist && capacity[_pos][e] > 0)	//checks if e is on next layer
		{
			long long f = dfs(e, _des, std::min(_minCapacity, capacity[_pos][e]));
			capacity[_pos][e] -= f;
			capacity[e][_pos] += f;
			_minCapacity -= f;
			result += f;
			if (_minCapacity == 0)
				break;
		}
	}
	return result;
}

std::queue<int> bfs_Queue;
bool bfs(int _start, int _des)
{
	while (!bfs_Queue.empty())
		bfs_Queue.pop();
	
	for (int i = 1; i <= N; ++i)
		V[i].dist = INT_INF;
	
	V[_start].dist = 0;
	bfs_Queue.push(_start);
	int proc;
	while (!bfs_Queue.empty())
	{
		proc = bfs_Queue.front();
		bfs_Queue.pop();
		
		if (proc == _des)
			return true;
		
		for (int i = 0, e; i < V[proc].adj.size(); ++i)
		{
			e = V[proc].adj[i];
			if (V[e].dist == INT_INF && capacity[proc][e] > 0)
			{
				V[e].dist = V[proc].dist + 1 ;
				bfs_Queue.push(e);
			}
		}
	}
	return false;
}

long long dinic(int _source, int _sink)
{
	long long result = 0;
	while (bfs(_source, _sink))	//while _sink is reachable from _source
	{
		for (int i = 1; i <= N; ++i)
			V[i].ptr = 0;
		
		result += dfs(_source, _sink, std::numeric_limits<long long>::max());
	}
	return result;
}

int main()
{
	scanf("%d%d", &N, &M);
	
	for (int i = 0, A, B, C; i < M; ++i)
	{
		scanf("%d%d%d", &A, &B, &C);
		if (A == B)
			continue;
		
		if (capacity[A][B] == 0)
		{
			V[A].adj.push_back(B);
			V[B].adj.push_back(A);
		}
		capacity[A][B] += C;
		capacity[B][A] += C;
		
	}
	printf("%lld\n", dinic(1, N));
	return 0;
}