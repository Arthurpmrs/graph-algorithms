#ifndef UNIONFIND_H
#define UNIONFIND_H

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
    UnionFind(int n);
    void makeSet(int v);
    void unite(int v, int u);
    int find(int v);
    void print();
};

#endif // UNIONFIND_H