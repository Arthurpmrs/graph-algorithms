#include "graph.h"

using namespace std;

Graph::Graph(int n) : _adjList(n + 1), _predecessors(n + 1, -1), _parents(n + 1, -1)
{
    _visitCount = 0;
    _vertexCount = n + 1;
    for (int i = 0; i < _vertexCount; i++)
    {
        _adjList[i] = vector<Edge>();
    }
}

void Graph::addEdge(int u, int v, int weight)
{
    _adjList[u].push_back({v, weight});
    _adjList[v].push_back({u, weight});
}

int Graph::getSize()
{
    return _adjList.size();
}

int Graph::notVisited(int v)
{
    return _predecessors[v] == -1;
}

void Graph::visit(int v)
{
    _predecessors[v] = _visitCount++;
}

void Graph::resetVisited() {
    _visitCount = 0;
    _predecessors = vector<int>(_vertexCount, -1);
}

void Graph::registerParent(int vertex, int parent)
{
    _parents[vertex] = parent;
}

const vector<Edge> &Graph::getVertexEdges(int v)
{
    return _adjList[v];
}

int Graph::getParent(int v) {
    return _parents[v];
}

Edge *Graph::getSmallestWeightEdge(int v, set<int> &exclude)
{
    Edge *smallestCostEdge = NULL;
    int smallestCost = 1000000000;
    for (int i = 0; i < _adjList[v].size(); ++i)
    {
        int neighbor = _adjList[v][i].neighbor;
        int weight = _adjList[v][i].weight;
        if (exclude.find(neighbor) != exclude.end() && weight < smallestCost)
        {
            smallestCost = weight;
            smallestCostEdge = &_adjList[v][i];
        }
    }
    return smallestCostEdge;
}

void Graph::print()
{
    for (int i = 0; i < _vertexCount; i++)
    {
        cout << i << " -> ";
        for (unsigned int j = 0; j < _adjList[i].size(); j++)
        {
            cout << _adjList[i][j].neighbor << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Graph::printVisited()
{
    cout << "Visited" << endl;
    for (int i = 0; i < _vertexCount; i++)
    {
        cout << i << " : " << _predecessors[i] << endl;
    }
    cout << endl;
}

void Graph::printParents()
{
    cout << "Parents" << endl;
    for (int i = 0; i < _vertexCount; i++)
    {
        cout << i << " : " << _parents[i] << endl;
    }
    cout << endl;
}
