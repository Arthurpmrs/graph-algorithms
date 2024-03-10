#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../modules/graph.h"

using namespace std;
const int INF = 100000000;

struct VertexCost {
    int cost;
    int vertex;
    bool operator<(const VertexCost& other) const {
        return cost > other.cost;
    }
};

void printq(priority_queue<VertexCost> q) {
    cout << "################# FILA INTEIRA #######" << endl;
    while (!q.empty()) {
        VertexCost vc = q.top();
        q.pop();
        cout << "(" << vc.vertex << "," << vc.cost << ")" << endl;
    }
    cout << "#############################################" << endl;

}

void prim(Graph &graph, Graph &mst)
{
    vector<int> cost(graph.getSize());
    priority_queue<VertexCost> q;

    cost[1] = 0;
    for (int i = 1; i < graph.getSize(); ++i) {
        cost[i] = INF;
        q.push({cost[i], i});
    }

    while (!q.empty()) {
    // for (int i = 1; i < graph.getSize(); ++i) {
        VertexCost vertexCost = q.top();
        q.pop();
        int u = vertexCost.vertex;
        graph.visit(u);
        // cout <<"fila: "<< vertexCost.vertex << " " << vertexCost.cost << endl;

        vector<Edge> neighbors = graph.getVertexEdges(u);
        // cout << "   vizinhos dele: " << endl;
        for (Edge edge : neighbors) {
            int v = edge.neighbor;
            // cout << "   (" << edge.neighbor << "," << edge.weight << ")" << endl;
            if (edge.weight < cost[v] && graph.notVisited(v)) {
            // if (edge.weight < cost[v]) {
                // cout << "       atualizar esse" << endl;
                cost[v] = edge.weight;
                graph.registerParent(v, u);
                q.push({cost[v], v});
            }
        }

        // printq(q);
    }

    

    for (int i = 0; i < graph.getSize(); ++i) {
        // cout << i << ":" << "w" << graph.getParent(i) << endl;

        if (graph.getParent(i) == -1) {
            continue;
        }

        mst.addEdge(i, graph.getParent(i), cost[i]);
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

int getTotalWeight(Graph &graph)
{
    int totalWeight = 0;
    for (int v = 0; v < graph.getSize(); ++v)
    {
        for (Edge e : graph.getVertexEdges(v))
        {
            totalWeight += e.weight;
        }
    }
    return totalWeight / 2;
}

Graph create_graph_from_file(string filename) {
    ifstream file(filename);

    int n, m;
    string line;

    getline(file, line);

    istringstream iss(line);
    iss >> n >> m;

    Graph graph(n);

    while (getline(file, line)) {
        istringstream iss(line);
        int u, v, w;
        iss >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    file.close();

    return graph;
}

int get_paremeter_value(char* parameter, int argc, char* argv[], string* value) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(parameter, argv[i]) == 0) {
            if (i + 1 == argc || argv[i + 1][0] == '-') {
                *value = "";
                return 1;
            } else {
                *value = string(argv[i + 1]);
                return 2;
            }
        }
    }
    return 0;
}

void print_mst_solution(Graph &mst, string output_filename = "") {
    if (output_filename != "") {
        ofstream file(output_filename);
        for (int i = 0; i < mst.getSize(); i++) {
            for (Edge e : mst.getVertexEdges(i)) {
                if (mst.notVisited(e.neighbor)) {
                    file << "(" << i << "," << e.neighbor << ") ";
                }
            }
            mst.visit(i);
        }
        mst.resetVisited();
        file << endl;
        file.close();
        return;
    }
    
    for (int i = 0; i < mst.getSize(); i++) {
        for (Edge e : mst.getVertexEdges(i)) {
            if (mst.notVisited(e.neighbor)) {
                cout << "(" << i << "," << e.neighbor << ") ";
            }
        }
        mst.visit(i);
    }
    mst.resetVisited();
    cout << endl;
}


int main(int argc, char* argv[])
{
    // string filename = "prim/arquivo-entrada.dat";
    string filename = "";
    get_paremeter_value((char*)"-f", argc, argv, &filename);
    
    if (filename == "") {
        cout << "Invalid parameter" << endl;
        return 1;
    }

    Graph graph = create_graph_from_file(filename);
    // graph.print();
        
    Graph mst(graph.getSize() - 1);

    prim(graph, mst);
    // mst.print();

    string value;
    int is_s_option_present = get_paremeter_value((char*)"-s", argc, argv, &value);

    if (is_s_option_present == 1) {
        print_mst_solution(mst);
    } else {
        cout << getTotalWeight(mst) << endl;
    }

    string output_filename;
    get_paremeter_value((char*)"-o", argc, argv, &output_filename);

    if (output_filename != "") {
        print_mst_solution(mst, output_filename);
    }


    return 0;
}