#include "unionfind.h"

using namespace std;

UnionFind::UnionFind(int n) : _parents(n + 1, -1), _ranks(n + 1, 0)
{
    size = n + 1;
}

void UnionFind::makeSet(int v)
{
    _parents[v] = v;
}

void UnionFind::unite(int v, int u)
{
    if (_ranks[v] >= _ranks[u])
    {
        _parents[u] = v;

        if (_ranks[v] == _ranks[u])
        {
            _ranks[v]++;
        }
    }
    else
    {
        _parents[v] = u;
    }
}

int UnionFind::find(int v)
{
    if (_parents[v] != v)
    {
        _parents[v] = find(_parents[v]);
    }
    return _parents[v];
}

void UnionFind::print()
{
    for (int i = 0; i < size; ++i)
    {
        printf("(v=%d, parent=%d, rank=%d)\n", i, _parents[i], _ranks[i]);
    }
}
