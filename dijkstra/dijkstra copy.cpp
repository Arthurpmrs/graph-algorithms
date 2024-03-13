#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../modules/graph.h"

using namespace std;

/**
 * @brief Dijkstra's algorithm implementation
 *
 * @param graph reference to the graph to find the shortest paths between nodes
 * @param source the source node to start the algorithm
 */
void dijkstra(Graph &graph, int source)
{
    graph._distances[source] = 0;

    priority_queue<Edge> pq;
    pq.push({source, 0});

    while (!pq.empty())
    {
        int u = pq.top().neighbor;
        pq.pop();

        vector<Edge> neighbors = graph.getVertexEdges(u);

        for (Edge edge : neighbors)
        {
            int v = edge.neighbor;
            int weight = edge.weight;
            if (graph._distances[v] > graph._distances[u] + weight)
            {
                graph._distances[v] = graph._distances[u] + weight;
                pq.push({v, graph._distances[v]});
            }
        }
    }

    // Check the distances and set -1 to the nodes that are not reachable
    for (int i = 0; i < graph.getSize(); i++)
    {
        if (graph._distances[i] == 1e9)
        {
            graph._distances[i] = -1;
        }
    }
}

/**
 * @brief Writes the minimum spanning tree edges to a file.
 *
 * @param mst reference to the graph that represents the minimum spanning tree
 * @param output_filename name of the file to write the edges
 */
void writeDistances(Graph &graph, string output_filename)
{
    
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

    int source = 1;

    dijkstra(graph, source);

    // check for a -o flag
    string output_filename;
    bool has_dash_o = getParameterValue((char *)"-o", argc, argv, &output_filename);

    if (has_dash_o)
    {
        writeDistances(graph, output_filename);
    }

    return 0;
}