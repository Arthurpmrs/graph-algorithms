#include <iostream>
#include <vector>
#include <queue>

#include "../modules/graph.h"
#include "../modules/utils.h"
#include "../modules/unionfind.h"

using namespace std;

Graph kruskal(Graph &graph)
{
    Graph mst(graph.getSize() - 1);

    UnionFind sets(graph.getSize() - 1);
    priority_queue<Edge> q;

    // Union-find and priority queue setup
    for (int i = 0; i < graph.getSize(); ++i)
    {
        sets.makeSet(i);
        for (Edge e : graph.getVertexEdges(i))
        {
            if (e.source < e.neighbor)
            {
                q.push(e);
            }
        }
    }

    while (!q.empty())
    {
        Edge e = q.top();
        q.pop();

        if (sets.find(e.source) != sets.find(e.neighbor))
        {
            mst.addEdge(e.source, e.neighbor, e.weight);
            sets.unite(sets.find(e.source), sets.find(e.neighbor));
        }
    }

    return mst;
}

int main(int argc, char *argv[])
{
    // check for -h flag
    bool has_dash_h = getParameterValue((char *)"-h", argc, argv);
    if (has_dash_h)
    {
        std::cout << "Algoritmo de Kruskal\n"
                  << "\n"
                  << "Opções:\n"
                  << "-h           : mostra o help\n"
                  << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n"
                  << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada\n"
                  << "-s           : mostra a solução\n";

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

    Graph graph = createGraphFromFile(filename);

    Graph mst = kruskal(graph);

    // check for -s flag. If exists, print the solution instead of the total weight
    bool has_dash_s = getParameterValue((char *)"-s", argc, argv);
    if (has_dash_s)
    {
        printMstSolution(mst);
    }
    else
    {
        cout << getTotalWeight(mst) << endl;
    }

    // check for a -o flag
    string output_filename;
    bool has_dash_o = getParameterValue((char *)"-o", argc, argv, &output_filename);

    if (has_dash_o)
    {
        writeMstEdgesToFile(mst, output_filename);
    }

    return 0;
}