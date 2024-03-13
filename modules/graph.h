#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int source;
    int neighbor;
    int weight;
    bool operator<(const Edge &other) const
    {
        return weight > other.weight;
    }
};

class Graph
{
private:
    vector<vector<Edge>> _adjList;
    vector<int> _predecessors;
    vector<int> _parents;
    int _visitCount;
    int _visitPostorderCount;
    int _vertexCount;

public:
    Graph(int n);
    void addEdge(int u, int v, int weight);
    void addEdge2(int u, int v);
    int getSize();
    int notVisited(int v);
    void visit(int v);
    void resetVisited();
    void visitPostorder(int v);
    int getParent(int v);
    void registerParent(int vertex, int parent);
    const vector<Edge> &getVertexEdges(int v);
    void print();
    void printVisited();
    void printParents();
    void printVisitedPO();

    vector<int> _distances;
    vector<int> _postorder;
};

#endif