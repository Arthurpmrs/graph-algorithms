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
    // check for -h flag
    bool has_dash_h = getParameterValue((char *)"-h", argc, argv);
    if (has_dash_h)
    {
        std::cout << "Algoritmo de Prim\n"
                  << "\n"
                  << "Opções:\n"
                  << "-h           : mostra o help\n"
                  << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n"
                  << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada\n"
                  << "-s           : mostra a solução\n"
                  << "-i           : vértice inicial\n";

        // If the help flag is used, do not execute the code.
        return 0;
    }

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

    // Get the initial vertex
    string initialVertexStr = "";
    getParameterValue((char *)"-i", argc, argv, &initialVertexStr);

    // check if the value is a number.
    int initialVertex = 0;
    if (initialVertexStr == "")
    {
        initialVertex = 1;
    }
    else
    {
        try
        {
            initialVertex = std::stoi(initialVertexStr);
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "Invalid argument: " << initialVertexStr << " is not a number.\n";
            return 1; // Return with error
        }
    }

    Graph mst = prim(graph, initialVertex);

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