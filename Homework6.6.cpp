//22520201
//Võ Thành Danh
//Session 06 - Exercise 06

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
#include <queue>
#include <climits>
#include <algorithm>
#include <iterator>
#include <utility>
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
        adjacencyList[to].emplace_back(from, weight); // Ensure undirected graph
    }

    // Display the adjacency list
    void displayAdjacencyList() {
        cout << "Adjacency List:" << endl;
        for (const auto& entry : adjacencyList) {
            int key = entry.first;
            const vector<pair<int, int>>& neighbors = entry.second;

            cout << key << ": ";
            for (const auto& neighbor : neighbors) {
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

    // Find all connected components using DFS
    void findConnectedComponents() {
        set<int> visited;
        vector<vector<int>> components;

        for (int i = 0; i < vertexCount; ++i) {
            if (!visited.count(i)) {
                vector<int> component;
                stack<int> s;
                s.push(i);

                while (!s.empty()) {
                    int current = s.top();
                    s.pop();

                    if (!visited.count(current)) {
                        visited.insert(current);
                        component.push_back(current);

                        for (const auto& neighbor : adjacencyList[current]) {
                            if (!visited.count(neighbor.first)) {
                                s.push(neighbor.first);
                            }
                        }
                    }
                }

                components.push_back(component);
            }
        }

        cout << "\nConnected Components:" << endl;
        for (const auto& component : components) {
            for (int vertex : component) {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph graph;

    // Adding vertices
    graph.addVertex(); // Vertex 0
    graph.addVertex(); // Vertex 1
    graph.addVertex(); // Vertex 2
    graph.addVertex(); // Vertex 3
    graph.addVertex(); // Vertex 4

    // Adding edges with weights
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(3, 4, 1);

    // Display the adjacency list
    graph.displayAdjacencyList();

    // Perform Dijkstra's algorithm from source vertex 0
    cout << "\nShortest paths from vertex 0:" << endl;
    vector<int> shortestPaths = graph.dijkstra(0);
    for (int i = 0; i < shortestPaths.size(); i++) {
        cout << "Vertex " << i << " : " << shortestPaths[i] << endl;
    }

    // Find all connected components
    graph.findConnectedComponents();

    return 0;
}