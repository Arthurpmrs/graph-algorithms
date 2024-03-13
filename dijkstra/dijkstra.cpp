#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../modules/graph.h"
#include "../modules/utils.h"

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
    pq.push({0, source, 0});

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
                graph.registerParent(v, u);
                pq.push({0, v, graph._distances[v]});
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
    ofstream file(output_filename);
    for (int i = 1; i < graph.getSize(); i++)
    {
        file << i << ":" << graph._distances[i] << " ";
    }

    file << endl;

    file.close();
}

void printDistances(Graph &graph)
{
    for (int i = 1; i < graph.getSize(); i++)
    {
        cout << i << ":" << graph._distances[i] << " ";
    }

    cout << endl;
}

int main(int argc, char *argv[])
{
    // check for -h flag
    bool has_dash_h = getParameterValue((char *)"-h", argc, argv);
    if (has_dash_h)
    {
        std::cout << "Algoritmo de Dijkstra\n"
                  << "\n"
                  << "Opções:\n"
                  << "-h           : mostra o help\n"
                  << "-o <arquivo> : redireciona a saida para o 'arquivo'\n"
                  << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada\n"
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

    string initialVertexStr;
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

    dijkstra(graph, initialVertex);
    printDistances(graph);

    // check for a -o flag
    string output_filename;
    bool has_dash_o = getParameterValue((char *)"-o", argc, argv, &output_filename);

    if (has_dash_o)
    {
        writeDistances(graph, output_filename);
    }

    return 0;
}