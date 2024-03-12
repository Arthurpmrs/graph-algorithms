#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../modules/graph.h"

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

/**
 * @brief Get the total weight of the minimum spanning tree
 *
 * @param mst reference to the graph that represents the minimum spanning tree
 * @return int
 */
int getTotalWeight(Graph &mst)
{
    int totalWeight = 0;
    for (int v = 0; v < mst.getSize(); ++v)
    {
        for (Edge e : mst.getVertexEdges(v))
        {
            totalWeight += e.weight;
        }
    }
    return totalWeight / 2;
}

/**
 * @brief Create a graph from a given input file
 *
 * @param filename input filename
 * @return Graph
 */
Graph createGraphFromFile(string filename)
{
    ifstream file(filename);

    int n, m;
    string line;

    getline(file, line);

    istringstream iss(line);
    iss >> n >> m;

    Graph graph(n);

    while (getline(file, line))
    {
        istringstream iss(line);
        int u, v, w;
        iss >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    file.close();

    return graph;
}

/**
 * @brief Gets the value of a parameter from the command line arguments.
 *
 * @param parameter the parameter to look for
 * @param argc number of arguments
 * @param argv array of arguments
 * @param value pointer to a string to store the value of the parameter
 * @return true if the parameter was found, false otherwise
 */
bool getParameterValue(char *parameter, int argc, char *argv[], string *value = NULL)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(parameter, argv[i]) == 0)
        {
            if ((strcmp(parameter, "-f") == 0 ||
                 strcmp(parameter, "-o") == 0 ||
                 strcmp(parameter, "-i") == 0) &&
                i + 1 < argc)
            {
                *value = string(argv[i + 1]);
                return true;
            }
            else if ((strcmp(parameter, "-h") == 0 ||
                      strcmp(parameter, "-s") == 0))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

/**
 * @brief Writes the minimum spanning tree edges to a file.
 *
 * @param mst reference to the graph that represents the minimum spanning tree
 * @param output_filename name of the file to write the edges
 */
void writeMstEdgesToFile(Graph &mst, string output_filename)
{
    ofstream file(output_filename);
    for (int i = 0; i < mst.getSize(); i++)
    {
        for (Edge e : mst.getVertexEdges(i))
        {
            if (mst.notVisited(e.neighbor))
            {
                file << i << " " << e.neighbor << " " << e.weight << endl;
            }
        }
        mst.visit(i);
    }
    mst.resetVisited();
    file.close();
}

/**
 * @brief Prints the minimum spanning tree solution to cout.
 *
 * @param mst reference to the graph that represents the minimum spanning tree
 */
void printMstSolution(Graph &mst)
{
    for (int i = 0; i < mst.getSize(); i++)
    {
        for (Edge e : mst.getVertexEdges(i))
        {
            if (mst.notVisited(e.neighbor))
            {
                cout << "(" << i << "," << e.neighbor << ") ";
            }
        }
        mst.visit(i);
    }
    mst.resetVisited();
    cout << endl;
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