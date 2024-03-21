#include <iostream>
#include <vector>
#include "../modules/graph.h"

using namespace std;

/**
 * @param graph reference to the graph
 * @param v the vertex to start the DFS
 * @param toPrint boolean to print the strongly connected components
 */
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

/**
 * @brief DFS algorithm that use the postorder vector to find the strongly connected components
 *
 * @param graph reference to the graph
 * @param postorder vector with the postorder of the graph
 * @param scc number of strongly connected components
 */
int DFSPriority(Graph &graph, vector<int> postorder, int scc = 0)
{
    for (int i = 1; i < graph.getSize(); i++)
    {
        int v = postorder[i];
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

/**
 * @brief Postorder DFS algorithm
 *
 * @param graph reference to the graph to find the postorder
 */
void DFS(Graph &graph)
{
    for (int v = 1; v < graph.getSize(); v++)
    {
        if (graph.notVisited(v))
        {
            DFSRec(graph, v, false);
        }
    }
}