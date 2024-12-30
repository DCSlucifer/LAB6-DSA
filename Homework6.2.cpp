//22520201
//Võ Thành Danh
//Session 06 - Exercise 02

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
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

    // Recursive Depth-First Search
    void dfsRecursive(int start, set<int>& visited) {
        if (visited.count(start)) return;

        cout << start << " ";
        visited.insert(start);

        for (int neighbor : adjacencyList[start]) {
            dfsRecursive(neighbor, visited);
        }
    }

    // Iterative Depth-First Search
    void dfsIterative(int start) {
        set<int> visited;
        stack<int> s;
        s.push(start);

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited.count(current)) {
                cout << current << " ";
                visited.insert(current);

                for (auto it = adjacencyList[current].rbegin(); it != adjacencyList[current].rend(); ++it) {
                    s.push(*it);
                }
            }
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

    // Adding edges
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);
    graph.addEdge(3, 3);

    // Display the adjacency list and matrix
    graph.displayAdjacencyList();
    graph.displayAdjacencyMatrix();

    // Perform DFS
    cout << "\nDFS Recursive starting from vertex 2:" << endl;
    set<int> visited;
    graph.dfsRecursive(2, visited);

    cout << "\nDFS Iterative starting from vertex 2:" << endl;
    graph.dfsIterative(2);

    return 0;
}