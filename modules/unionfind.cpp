#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
private:
    vector<int> _parents;
    vector<int> _ranks;
    int size;

public:
    UnionFind(int n) : _parents(n + 1, -1), _ranks(n + 1, 0)
    {
        size = n + 1;
    }

    void makeSet(int v)
    {
        _parents[v] = v;
    }

    void unite(int v, int u)
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

    int find(int v)
    {
        if (_parents[v] != v)
        {
            _parents[v] = find(_parents[v]);
        }
        return _parents[v];
    }

    void print()
    {
        for (int i = 0; i < size; ++i)
        {
            printf("(v=%d, parent=%d, rank=%d)\n", i, _parents[i], _ranks[i]);
        }
    }
};