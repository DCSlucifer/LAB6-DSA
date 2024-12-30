//22520201
//Võ Thành Danh
//Session 06 - Exercise 01

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> adjacencyList; // For adjacency list
    vector<vector<int>> adjacencyMatrix;          // For adjacency matrix
    int vertexCount;

public:
    // Constructor
    Graph() : vertexCount(0) {}

    // Method to add a vertex
    void addVertex() {
        vertexCount++;

        // Expand the adjacency matrix
        for (auto& row : adjacencyMatrix) {
            row.push_back(0);
        }
        adjacencyMatrix.push_back(vector<int>(vertexCount, 0));

        // Add entry for adjacency list
        adjacencyList[vertexCount - 1] = vector<int>();
    }

    // Method to add an edge
    void addEdge(int from, int to) {
        if (from >= vertexCount || to >= vertexCount) {
            cout << "Invalid vertices: " << from << " -> " << to << endl;
            return;
        }

        // Add edge to adjacency list
        adjacencyList[from].push_back(to);

        // Add edge to adjacency matrix
        adjacencyMatrix[from][to] = 1;
    }

    // Display the adjacency list
    void displayAdjacencyList() {
        cout << "Adjacency List:" << endl;
        for (const auto& pair : adjacencyList) {
            int key = pair.first;
            const vector<int>& value = pair.second;

            cout << key << ": ";
            for (int v : value) {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    // Display the adjacency matrix
    void displayAdjacencyMatrix() {
        cout << "Adjacency Matrix:" << endl;
        for (const auto& row : adjacencyMatrix) {
            for (int value : row) {
                cout << value << " ";
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

    // Adding edges
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);

    // Display the adjacency list and matrix
    graph.displayAdjacencyList();
    graph.displayAdjacencyMatrix();

    return 0;
}