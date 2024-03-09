#include <iostream>
#include <vector>
#include <set>
#include "../modules/graph.h"

using namespace std;
const int INF = 100000000;

void prim(Graph &graph, Graph &mst)
{
    int n = graph.getSize();
    cout << "size = " << n << endl;
    vector<Edge> minWeightEdge(n, {-1, INF});
    set<Edge> edgeQ;

    // This is necessary to check if the graph provided starts at 0 or 1.
    for (int i = 0; i < n; ++i)
    {
        if (graph.getVertexEdges(i).size() > 0)
        {
            edgeQ.insert({i, INF});
            break;
        }
    }

    // Main algorithm
    for (int i = 0; i < n; ++i)
    {
        if (edgeQ.empty())
        {
            cout << "No MST!" << endl;
            break;
        }

        int v = edgeQ.begin()->neighbor;
        edgeQ.erase(edgeQ.begin());

        graph.visit(v);

        for (Edge e : graph.getVertexEdges(v))
        {
            if (graph.notVisited(e.neighbor) &&
                e.weight < minWeightEdge[e.neighbor].weight)
            {
                minWeightEdge[e.neighbor] = {v, e.weight};
                edgeQ.insert({e.neighbor, e.weight});
            }
        }
    }

    // Build the MST based on the minWeightEdge vector
    for (int i = 0; i < n; ++i)
    {
        if (minWeightEdge[i].neighbor == -1)
        {
            continue;
        }

        mst.addEdge(i, minWeightEdge[i].neighbor, minWeightEdge[i].weight);
    }
}

void readGraph(Graph &graph, int edgeCount)
{
    for (int i = 0; i < edgeCount; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
}

int getTotalWeight(Graph &graph)
{
    int totalWeight = 0;
    for (int v = 0; v < graph.getSize(); ++v)
    {
        for (Edge e : graph.getVertexEdges(v))
        {
            totalWeight += e.weight;
        }
    }
    return totalWeight / 2;
}

int main()
{
    int n, m;
    cin >> n >> m;

    Graph graph(n);
    Graph mst(n);
    readGraph(graph, m);

    prim(graph, mst);
    mst.print();

    cout << "Total Weight = " << getTotalWeight(mst) << endl;
}