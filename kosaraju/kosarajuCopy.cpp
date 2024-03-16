#include <iostream>
#include "../modules/graph.h"
#include "../modules/utils.h"
#include "dfs-kosarajuCopy.cpp"

using namespace std;

void reverseGraph(Graph &graph, Graph &reversedGraph){
    for(int i = 0; i < graph.getSize(); i++){
        const vector<Edge> &edges = graph.getVertexEdges(i);
        for(int j = 0; j < edges.size(); j++){
            reversedGraph.addEdge2(edges[j].neighbor, i);
        }
    }
}

// Função para ordenar o vetor de postorder por ordem de visitação e invertê-lo
void reversePO(vector<int> &postorder){
    vector<int> aux = postorder; 
    for(int i = 1; i < postorder.size(); i++){ // Colocar os vetores na ordem
        postorder[aux[i]] = i;
    }
    aux = postorder;
    
    for(int i = 0; i < postorder.size(); i++){ // Inverter o vetor
        postorder[i] = aux[aux.size() - i];
    }
}


int main(int argc, char *argv[])
{
    // check for -h flag
    bool has_dash_h = getParameterValue((char *)"-h", argc, argv);
    if (has_dash_h)
    {
        std::cout << "Algoritmo de Kosaraju\n"
                    << "\n"
                    << "Opções:\n"
                    << "-h           : mostra o help\n"
                    << "-o <arquivo> : redireciona a saida para o 'arquivo'\n"
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

    // check for a -o flag
    string output_filename;
    bool has_dash_o = getParameterValue((char *)"-o", argc, argv, &output_filename);

    Graph graph = createGraphFromFile(filename);

    Graph reversedGraph(graph.getSize());
    reverseGraph(graph, reversedGraph);
    DFS(reversedGraph);
    
   
    reversePO(reversedGraph._postorder); // Use the postorder with i = 1 to size;

    int scc = DFSPriority(graph, reversedGraph._postorder, output_filename);


    return 0;
}