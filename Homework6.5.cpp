//22520201
//Võ Thành Danh
//Session 06 - Exercise 05

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
#include <queue>
#include <climits>
#include <iterator>
#include <functional>
#include <algorithm>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<pair<int, int>>> adjacencyList; // For adjacency list with weights
    int vertexCount;

public:
    // Constructor
    Graph() : vertexCount(0) {}

    // Method to add a vertex
    void addVertex() {
        vertexCount++;
        adjacencyList[vertexCount - 1] = vector<pair<int, int>>();
    }

    // Method to add an edge with weight
    void addEdge(int from, int to, int weight) {
        if (from >= vertexCount || to >= vertexCount) {
            cout << "Invalid vertices: " << from << " -> " << to << endl;
            return;
        }

        // Add edge to adjacency list
        adjacencyList[from].emplace_back(to, weight);
    }

    // Display the adjacency list
    void displayAdjacencyList() {
        cout << "Adjacency List:" << endl;
        for (const auto& entry : adjacencyList) {
            int key = entry.first;
            const vector<pair<int, int>>& value = entry.second;

            cout << key << ": ";
            for (const auto& neighbor : value) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    // Dijkstra's algorithm to find shortest paths
    vector<int> dijkstra(int source) {
        vector<int> distances(vertexCount, INT_MAX);
        distances[source] = 0;

        // Min-heap to store (distance, vertex)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, source);

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int currentVertex = pq.top().second;
            pq.pop();

            // Skip processing if we already found a shorter path
            if (currentDistance > distances[currentVertex]) continue;

            for (const auto& neighbor : adjacencyList[currentVertex]) {
                int nextVertex = neighbor.first;
                int weight = neighbor.second;

                if (distances[currentVertex] + weight < distances[nextVertex]) {
                    distances[nextVertex] = distances[currentVertex] + weight;
                    pq.emplace(distances[nextVertex], nextVertex);
                }
            }
        }

        return distances;
    }
};

int main() {
    Graph graph;

    // Adding vertices
    graph.addVertex(); // Vertex 0
    graph.addVertex(); // Vertex 1
    graph.addVertex(); // Vertex 2
    graph.addVertex(); // Vertex 3

    // Adding edges with weights
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 6);
    graph.addEdge(2, 3, 3);

    // Display the adjacency list
    graph.displayAdjacencyList();

    // Perform Dijkstra's algorithm from source vertex 0
    cout << "\nShortest paths from vertex 0:" << endl;
    vector<int> shortestPaths = graph.dijkstra(0);
    for (int i = 0; i < shortestPaths.size(); i++) {
        cout << "Vertex " << i << " : " << shortestPaths[i] << endl;
    }

    return 0;
}