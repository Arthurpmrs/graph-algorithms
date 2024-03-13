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
    for(int i = 1; i < size; i++){
        orderPO[postorder[i]] = i-1;
    }

    postorder = orderPO;

    /*
    for(int i = 0; i < size-1; i++){
        cout << postorder[i] << " ";
    }
    cout << endl; 
    */
    
    for (int i = 0; i < size; i++){
        postorder[i] = orderPO[size - i - 1 ];
    }

    /*
    for(int i = 1; i < size; i++){
        cout << postorder[i] << " ";
    }
    cout << endl;
    */
    
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
 
    reversePO(reversedGraph._postorder); // Utilizar o _postorder com i = 1 ate size;
    // reversedGraph.printVisitedPO();

    int scc = DFSPriority(graph, reversedGraph._postorder);
    cout << endl << "ssc: " << scc << endl;

    return 0;
}