#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../modules/graph.h"
#include "../modules/utils.h"

using namespace std;
const int INF = 100000000;

struct VertexCost
{
    int cost;
    int vertex;
    bool operator<(const VertexCost &other) const
    {
        return cost > other.cost;
    }
};

/**
 * @brief Prim's algorithm implementation
 *
 * @param graph reference to the graph to find the minimum spanning tree
 */
Graph prim(Graph &graph, int initialVertex = 1)
{
    vector<int> cost(graph.getSize());
    priority_queue<VertexCost> q;

    for (int i = 1; i < graph.getSize(); ++i)
    {
        cost[i] = INF;
        q.push({cost[i], i});
    }

    // Start with the initialVertex
    cost[initialVertex] = 0;
    q.push({cost[initialVertex], initialVertex});

    while (!q.empty())
    {
        int u = q.top().vertex;
        q.pop();

        graph.visit(u);

        vector<Edge> neighbors = graph.getVertexEdges(u);

        for (Edge edge : neighbors)
        {
            int v = edge.neighbor;
            if (edge.weight < cost[v] && graph.notVisited(v))
            {
                cost[v] = edge.weight;
                graph.registerParent(v, u);
                q.push({cost[v], v});
            }
        }
    }

    // Construct the MST graph
    Graph mst(graph.getSize() - 1);

    for (int i = 0; i < graph.getSize(); ++i)
    {
        if (graph.getParent(i) == -1)
        {
            continue;
        }
        mst.addEdge(i, graph.getParent(i), cost[i]);
    }

    return mst;
}

int main(int argc, char *argv[])
{
    // Check for a -f flag
    string filename = "";
    getParameterValue((char *)"-f", argc, argv, &filename);

    // It is mandatory to have a filename
    if (filename == "")
    {
        cout << "Please, enter a valid input file." << endl;
        return 1;
    }

    Graph graph = createGraphFromFile(filename);

    Graph mst = prim(graph);

    // check for -s flag. If exists, print the solution instead of the total weight
    bool has_dash_s = getParameterValue((char *)"-s", argc, argv);
    if (has_dash_s)
    {
        printMstSolution(mst);
    }
    else
    {
        cout << getTotalWeight(mst) << endl;
    }

    // check for a -o flag
    string output_filename;
    bool has_dash_o = getParameterValue((char *)"-o", argc, argv, &output_filename);

    if (has_dash_o)
    {
        writeMstEdgesToFile(mst, output_filename);
    }

    return 0;
}