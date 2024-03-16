#include <iostream>
#include <vector>
#include "../modules/graph.h"
#include "../modules/utils.h"

#define INF 1e9

using namespace std;

void bellmanFord(Graph &graph, int s){
    graph._distances[s] = 0;

    
}

void readGraph(Graph &graph, int edgeCount){
    for(int i = 0; i < edgeCount; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    Graph graph(n);
    readGraph(graph, m);

    bellmanFord(graph, 1);

    for(int i = 1; i <= n; i++){
        cout << graph._distances[i] << " ";
    }
    cout << endl;

}
