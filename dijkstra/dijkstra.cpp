#include <iostream>
#include <vector>
#include <queue>
#include "../modules/graph.h"

using namespace std;

void dijkstra(Graph &graph, int source){
    graph._distances[source] = 0;

    priority_queue<Edge> pq;
    pq.push({source, 0});

    while (!pq.empty()) {
        int u = pq.top().neighbor; pq.pop(); // remove and return the top element

        for (Edge neighbors : graph.getVertexEdges(u)) {
            int w = neighbors.neighbor;
            int weight = neighbors.weight;
            if (graph._distances[w] > graph._distances[u] + weight) {
                graph._distances[w] = graph._distances[u] + weight;
                pq.push({w, graph._distances[w]});
            }
        }
    }
}

void checkDistances(Graph &graph){
    for (int i = 0; i < graph.getSize(); i++) {
        if (graph._distances[i] == 1e9) {
            graph._distances[i] = -1;
        }
    }
}

void readGraph(Graph &graph, int edgeCount){
    for(int i = 0; i < edgeCount; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    
}

int main(){
    int n, m;
    cin >> n >> m;

    Graph graph(n);
    readGraph(graph, m);
    // graph.print();

    int source = 1;

    dijkstra(graph, source);
    checkDistances(graph);

    for (int i = 1; i < graph.getSize(); i++)
        cout << i << ":" << graph._distances[i] << " ";
    cout << endl;

    return 0;
}


/*
void dijkstra(Graph &graph, int source){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> distances(graph.getSize(), 1e9);
    distances[source] = 0;

    pq.push({0, source});

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        for(auto edge : graph.getVertexEdges(u)){
            int v = edge.neighbor;
            int weight = edge.weight;
            if(distances[v] > distances[u] + weight){
                distances[v] = distances[u] + weight;
                pq.push({distances[v], v});
            }
        }
    }

    for(int i = 0; i < graph.getSize(); i++){
        cout << "Distance from " << source << " to " << i << " is " << distances[i] << endl;
    }
}
*/