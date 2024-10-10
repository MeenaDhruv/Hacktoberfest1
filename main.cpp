#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    vector<Edge> edges;
};

struct subset {
    int parent;
    int rank;
};

int find(subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

bool compare(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

void KruskalMST(Graph& graph) {
    vector<Edge> result(graph.V);
    int e = 0, i = 0;

    sort(graph.edges.begin(), graph.edges.end(), compare);

    subset* subsets = new subset[graph.V];
    for (int v = 0; v < graph.V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < graph.V - 1 && i < graph.E) {
        Edge next_edge = graph.edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    cout << "Following are the edges in the constructed MST\n";
    for (i = 0; i < e; ++i)
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
    delete[] subsets;
}

int main() {
    Graph graph;
    graph.V = 4;
    graph.E = 5;
    graph.edges = { {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4} };
    KruskalMST(graph);
    return 0;
}
