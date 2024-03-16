#include <iostream>
#include <vector>
#include "../modules/graph.h"
#include "../modules/utils.h"

#define INF 1e9

using namespace std;

/**
 * @brief Bellman-Ford algorithm to find the shortest path in a graph.
 *
 * @param graph reference to the graph to be processed
 * @param s is the initial vertex
 */
void bellmanFord(Graph &graph, int s){
    graph._distances[s] = 0;

     // Relax all edges |V| - 1 times. 
    for (int l = 1; l < graph.getSize() - 1; l++) {
        // Iterate over all edges
        for (int u = 1; u < graph.getSize(); u++){ 
          vector<Edge> edges = graph.getVertexEdges(u);
          // Iterate over all edges of the vertex u
            for (int i = 0; i < edges.size(); i++){
                int v = edges[i].neighbor;
                int w = edges[i].weight;

                if(graph._distances[u] + w < graph._distances[v]){
                    graph._distances[v] = graph._distances[u] + w;
                }

            }
        }
    }
}

/**
 * @brief Writes the distances to a file
 * @param graph reference to the graph to be processed
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

/**
 * @brief Get the first vertex with more edges
 * 
 * @param graph reference to the graph to be processed
 * @return int the first vertex with more edges
 */
int getFirstVertex(Graph &graph)
{
    int initialVertex = 1;
    int moreEdges = graph.getVertexEdges(initialVertex).size();

    for (int i = 1; i < graph.getSize(); i++)
    {
        if (graph.getVertexEdges(i).size() > moreEdges)
        {
            initialVertex = i;
            moreEdges = graph.getVertexEdges(i).size();
        }
    }
    return initialVertex;
}

int main(int argc, char *argv[])
{
    // Check for -h flag
    bool has_dash_h = getParameterValue((char *)"-h", argc, argv);
    if (has_dash_h)
    {
        std::cout << "Algoritmo de Bellman-Ford\n"
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

    Graph graph = createGraphFromFile3(filename);

    string initialVertexStr;
    getParameterValue((char *)"-i", argc, argv, &initialVertexStr);

    // Check if the value is a number.
    int initialVertex = 0;
    if (initialVertexStr == "")
    {
        initialVertex = getFirstVertex(graph);
        cout << "Initial vertex not specified. Using vertex " << initialVertex << " as the initial vertex." << endl;
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

    // Run the algorithm
    bellmanFord(graph, initialVertex);

    // Check for a -o flag
    string output_filename;
    bool has_dash_o = getParameterValue((char *)"-o", argc, argv, &output_filename);

    if (has_dash_o)
    {
        for(int i = 1; i < graph.getSize(); i++)
            graph._distances[i] = graph._distances[i] == INF ? -1 : graph._distances[i];

        writeDistances(graph, output_filename);
    }

    return 0;
}