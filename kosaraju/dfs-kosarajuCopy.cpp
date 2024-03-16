#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../modules/graph.h"

using namespace std;

void DFSRec(Graph &graph, int v, bool toPrint, string output_filename)
{
    ofstream file(output_filename);
    graph.visit(v);

    const vector<Edge> &edges = graph.getVertexEdges(v);
    for (unsigned int i = 0; i < edges.size(); i++)
    {
        if (graph.notVisited(edges[i].neighbor))
        {
            file << edges[i].neighbor << " ";
            graph.registerParent(edges[i].neighbor, v);
            DFSRec(graph, edges[i].neighbor, toPrint, output_filename);
        }
    }

    graph.visitPostorder(v);
}

int DFSPriority(Graph &graph, vector<int> postorder, string output_filename, int scc = 0)
{
    ofstream file(output_filename);

    for (int i = 1; i < graph.getSize(); i++)
    {
        int v = postorder[i];
        if (graph.notVisited(v))
        {
            file << v << " ";
            scc++;
            DFSRec(graph, v, true, output_filename);
            file << endl;
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
            DFSRec(graph, v, false, "");
        }
    }
}