#include <iostream>
#include <vector>
#include <queue>
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

void readGraph(Graph &graph, int edgeCount)
{
    for (int i = 0; i < edgeCount; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    Graph graph(n);
    readGraph(graph, m);
    // graph.print();

    int source = 1;

    dijkstra(graph, source);

    for (int i = 1; i < graph.getSize(); i++)
        cout << i << ":" << graph._distances[i] << " ";
    cout << endl;

    return 0;
}