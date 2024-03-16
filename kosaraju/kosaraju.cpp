#include <iostream>
#include "../modules/graph.h"
#include "dfs-kosaraju.cpp"

using namespace std;

void readGraph(Graph &graph, int edgeCount){
    for(int i = 0; i < edgeCount; i++){
        int u, v;
        cin >> u >> v;
        graph.addEdge2(u, v);
    }
}

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

int main(){
    int n, m;
    cin >> n >> m;

    Graph graph(n);
    readGraph(graph, m);
    // graph.print();

    Graph reversedGraph(n);
    reverseGraph(graph, reversedGraph);
    // reversedGraph.print();
    DFS(reversedGraph);

    // reversedGraph.printVisitedPO();
    reversePO(reversedGraph._postorder); // Utilizar o _postorder com i = 1 ate size;
    // cout << "Reverse ";
    // reversedGraph.printVisitedPO();

    int scc = DFSPriority(graph, reversedGraph._postorder);
    cout << endl << "scc: " << scc << endl;

    return 0;
}