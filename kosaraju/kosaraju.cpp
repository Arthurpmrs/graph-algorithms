#include <iostream>
#include "../modules/utils.h"
#include "../modules/graph.h"
#include "dfs-kosaraju.cpp"

using namespace std;

/**
 * @brief Function to get the reversed graph
 *
 * @param graph reference to the original graph 
 * @param reversedGraph reference to the graph that will be reversed
 */
void reverseGraph(Graph &graph, Graph &reversedGraph){
    for(int i = 0; i < graph.getSize(); i++){
        const vector<Edge> &edges = graph.getVertexEdges(i);
        for(int j = 0; j < edges.size(); j++){
            reversedGraph.addEdge2(edges[j].neighbor, i);
        }
    }
}

/**
 * @brief Function to sort the postorder vector by visitation order and reverse it
 *
 * @param postorder reference to the vector that will be sorted and reversed
 */
void reversePO(vector<int> &postorder){
    // To put the vectors in order
    vector<int> aux = postorder; 
    for(int i = 1; i < postorder.size(); i++){
        postorder[aux[i]] = i;
    }

    aux = postorder;

    // To reverse the vector
    for(int i = 0; i < postorder.size(); i++){ 
        postorder[i] = aux[aux.size() - i];
    }
}

int main(int argc, char *argv[]){
    // Check for -h flag
    bool has_dash_h = getParameterValue((char *)"-h", argc, argv);
    if (has_dash_h)
    {
        std::cout << "Algoritmo de Kosaraju\n"
                    << "\n"
                    << "Opções:\n"
                    << "-h           : mostra o help\n"
                    << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada\n";

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

    // Create the graph from the file
    Graph graph = createGraphFromFile2(filename);

    // Create the reversed graph
    Graph reversedGraph(graph.getSize() - 1);
    reverseGraph(graph, reversedGraph);

    // Run the DFS on the reversed graph to get the postorder
    DFS(reversedGraph);
    reversePO(reversedGraph._postorder);

    // Run the DFS on the original graph using the postorder from the reversed graph
    int scc = DFSPriority(graph, reversedGraph._postorder);

    return 0;
}
