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

void reversePO(vector<int> &postorder){
    int size = postorder.size();

    vector<int> orderPO(size);
    for (int i = 1; i < size; i++)
    {
        orderPO[i] = postorder[postorder[i]];
    }

    
    cout << "postorder" << endl;
    for (int i = 1; i < size; i++)
    {
        cout << "vetor " << i << " : posição " << postorder[i] << endl;
    }
    cout << endl;
    cout << "orderPO" << endl;
    for (int i = 1; i < size; i++)
    {
        cout << "vetor " << i << " : posição " << orderPO[i] << endl;
    }
    cout << endl;
    
    
    for (int i = 1; i < size; i++)
    {
        postorder[i] = orderPO[size - i];
    }


    cout << "reversed postorder" << endl;
    for (int i = 1; i < size; i++)
    {
        cout << i << " : " << postorder[i] << endl;
    }
    cout << endl;
    
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
    cout << "scc: " << scc << endl;

    return 0;
}