//22520201
//Võ Thành Danh
//Session 06 - Exercise 07

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
    int V; // Number of vertices
    list<int>* adj; // Adjacency list

    void bridgeUtil(int v, bool visited[], int disc[], int low[], int parent[], vector<pair<int, int>>& bridges);

public:
    Graph(int V);
    void addEdge(int v, int w);
    void findBridges();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // Since the graph is undirected
}

void Graph::bridgeUtil(int v, bool visited[], int disc[], int low[], int parent[], vector<pair<int, int>>& bridges) {
    static int time = 0;
    visited[v] = true;
    disc[v] = low[v] = ++time;

    for (int i : adj[v]) {
        if (!visited[i]) {
            parent[i] = v;
            bridgeUtil(i, visited, disc, low, parent, bridges);

            low[v] = min(low[v], low[i]);

            if (low[i] > disc[v]) {
                bridges.push_back({ v, i });
            }
        }
        else if (i != parent[v]) {
            low[v] = min(low[v], disc[i]);
        }
    }
}

void Graph::findBridges() {
    bool* visited = new bool[V];
    int* disc = new int[V];
    int* low = new int[V];
    int* parent = new int[V];
    vector<pair<int, int>> bridges;

    for (int i = 0; i < V; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            bridgeUtil(i, visited, disc, low, parent, bridges);
        }
    }

    for (auto bridge : bridges) {
        cout << bridge.first << " -- " << bridge.second << endl;
    }

    delete[] visited;
    delete[] disc;
    delete[] low;
    delete[] parent;
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    cout << "Bridges in the graph are:\n";
    g.findBridges();

    return 0;
}