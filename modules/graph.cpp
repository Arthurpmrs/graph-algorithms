#include "graph.h"

using namespace std;

Graph::Graph(int n) : _adjList(n + 1), _predecessors(n + 1, -1), _parents(n + 1, -1), _postorder(n + 1, -1) , _distances(n + 1, 1e9)
{
    _visitCount = 0;
    _visitPostorderCount = 0;
    _vertexCount = n;
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

// Versão sem peso e direcionado
void Graph::addEdge2(int u, int v){
    _adjList[u].push_back({v, -1});
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

void Graph::visitPostorder(int v)
{
    _postorder[v] = _visitPostorderCount++;
}

int Graph::getParent(int v) {
    return _parents[v];
}

void Graph::registerParent(int vertex, int parent)
{
    _parents[vertex] = parent;
}

const vector<Edge> &Graph::getVertexEdges(int v)
{
    return _adjList[v];
}

void Graph::print()
{
    for (int i = 1; i < _vertexCount+1; i++)
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
    for (int i = 1; i < _vertexCount + 1; i++)
    {
        cout << i << " : " << _predecessors[i] << endl;
    }
    cout << endl;
}

void Graph::printVisitedPO()
{
    cout << "Post Order Visited" << endl;
    for (int i = 1; i < _vertexCount + 1; i++)
    {
        cout << i << " : " << _postorder[i] << endl;
    }
    cout << endl;
}

void Graph::printParents()
{
    cout << "Parents" << endl;
    for (int i = 1; i < _vertexCount + 1; i++)
    {
        cout << i << " : " << _parents[i] << endl;
    }
    cout << endl;
}
