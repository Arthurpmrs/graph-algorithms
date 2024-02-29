#include <iostream>
#include <vector>
#include <set>
#include "../modules/graph.h"

using namespace std;
const int INF = 100000000;

void prim(Graph &graph, Graph &mst)
{
    int n = graph.getSize();
    vector<Edge *> vertexMinWeightEdge(n, NULL);

    set<int> q;

    for (int i = 0; i < graph.getSize(); ++i)
    {
        q.insert(i);
    }

    while (!q.empty())
    {
        cout << "NOVA ITERAÇÃO--------\n";

        int smallestCostVertex = *q.begin();
        cout << "smallestVertexInit: " << smallestCostVertex << endl;
        int smallestCost = INF;
        for (int v : q)
        {
            if (vertexMinWeightEdge[v] != NULL &&
                vertexMinWeightEdge[v]->weight < smallestCost)
            {
                cout << "entrei no if (" << v << ")" << endl;
                smallestCost = vertexMinWeightEdge[v]->weight;
                smallestCostVertex = v;
                cout << "     smallestCost = " << smallestCost << endl;
            }
        }

        cout << "smallestVertex = " << smallestCostVertex << endl;

        q.erase(smallestCostVertex);

        int sw = INF;
        Edge *swEdge = NULL;
        vector<Edge> *vEdges = graph.GetVertexEdges2(smallestCostVertex);
        for (int i = 0; i < vEdges->size(); ++i)
        {
            int neighbor = (*vEdges)[i].neighbor;
            int weight = (*vEdges)[i].weight;

            if (q.find(neighbor) != q.end())
            {
                if (vertexMinWeightEdge[neighbor] != NULL &&
                    weight < vertexMinWeightEdge[neighbor]->weight)
                {
                    vertexMinWeightEdge[neighbor]->weight = weight;
                }
                else
                {
                    vertexMinWeightEdge[neighbor] = &(*vEdges)[i];
                }

                if (weight < sw)
                {
                    sw = weight;
                    swEdge = &(*vEdges)[i];
                }
            }
        }
        if (swEdge == NULL)
        {
            continue;
        }
        vertexMinWeightEdge[smallestCostVertex] = swEdge;
        mst.addEdge(smallestCostVertex, swEdge->neighbor, swEdge->weight);

        cout << "---SET---" << endl;
        for (int v : q)
        {
            cout << v << endl;
        }
        cout << "--pesos minimos----" << endl;

        for (int i = 0; i < n; ++i)
        {
            Edge *e = vertexMinWeightEdge[i];
            if (e == NULL)
            {
                cout << "null\n";
            }
            else
            {
                cout << i << ": (w=" << e->weight << " ,neig=" << e->neighbor << ")\n";
            }
        }
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

int getTotalCost(Graph &graph)
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

    Graph graph(n + 1);
    readGraph(graph, m);
    graph.print();
    Graph mst(n + 1);
    prim(graph, mst);
    mst.print();
    cout << "Total Weight = " << getTotalCost(mst) << endl;
}