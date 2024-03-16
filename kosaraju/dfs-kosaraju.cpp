#include <iostream>
#include <vector>
#include "../modules/graph.h"

using namespace std;

void DFSRec(Graph &graph, int v, bool toPrint)
{
    graph.visit(v);

    const vector<Edge> &edges = graph.getVertexEdges(v);
    for (unsigned int i = 0; i < edges.size(); i++)
    {
        if (graph.notVisited(edges[i].neighbor))
        {
            if (toPrint) cout << edges[i].neighbor << " ";
            graph.registerParent(edges[i].neighbor, v);
            DFSRec(graph, edges[i].neighbor, toPrint);
        }
    }

    graph.visitPostorder(v);
}

int DFSPriority(Graph &graph, vector<int> postorder, int scc = 0)
{
    for (int i = 1; i < graph.getSize(); i++)
    {
        int v = postorder[i];
        // cout << "teste: " << v << endl;
        if (graph.notVisited(v))
        {
            cout << v << " ";
            scc++;
            DFSRec(graph, v, true);
            cout << endl;
        }
    }

    return scc;
}

void DFS(Graph &graph, bool ignoreZero = true)
{
    int firstVertex;
    if (ignoreZero)
    {
        firstVertex = 1;
    }
    else
    {
        firstVertex = 0;
    }

    for (int v = firstVertex; v < graph.getSize(); v++)
    {
        if (graph.notVisited(v))
        {
            DFSRec(graph, v, false);
        }
    }
}