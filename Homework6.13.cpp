//22520201
//Võ Thành Danh
//Session 06 - Exercise 13

#include <iostream>
#include <climits> // For INT_MAX

using namespace std;

const int MAX_NODES = 100; // Maximum number of intersections

// Function to find the node with the smallest distance that hasn't been visited
int findMinDistance(int dist[], bool visited[], int N) {
    int minDist = INT_MAX, minIndex = -1;

    for (int i = 0; i < N; ++i) {
        if (!visited[i] && dist[i] < minDist) {
            minDist = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Dijkstra's Algorithm to find the shortest path
void dijkstra(int graph[MAX_NODES][MAX_NODES], int N, int source, int destination) {
    int dist[N];          // Array to store shortest distances from source
    bool visited[N];      // Array to keep track of visited nodes
    int prev[N];          // Array to reconstruct the path

    // Initialize distances and visited array
    for (int i = 0; i < N; ++i) {
        dist[i] = INT_MAX;
        visited[i] = false;
        prev[i] = -1;
    }
    dist[source] = 0;

    // Find shortest paths to all nodes
    for (int count = 0; count < N - 1; ++count) {
        int u = findMinDistance(dist, visited, N);
        if (u == -1) break; // If no reachable node remains
        visited[u] = true;

        for (int v = 0; v < N; ++v) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u; // Update the path
            }
        }
    }

    // Output the shortest distance
    cout << "Shortest distance from " << source << " to " << destination << ": ";
    if (dist[destination] == INT_MAX) {
        cout << "Unreachable\n";
        return;
    }
    cout << dist[destination] << "\n";

    // Reconstruct the path
    cout << "Path: ";
    int path[MAX_NODES], pathLength = 0;
    for (int at = destination; at != -1; at = prev[at]) {
        path[pathLength++] = at;
    }
    for (int i = pathLength - 1; i >= 0; --i) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

// Function to identify bottlenecks by counting connected roads
void identifyBottlenecks(int graph[MAX_NODES][MAX_NODES], int N) {
    cout << "Traffic Bottlenecks:\n";
    for (int i = 0; i < N; ++i) {
        int connections = 0;
        for (int j = 0; j < N; ++j) {
            if (graph[i][j] != 0) {
                connections++;
            }
        }
        if (connections > 2) { // Bottleneck if more than 2 connections
            cout << "Intersection " << i << " is a potential bottleneck (connections: " << connections << ")\n";
        }
    }
}

int main() {
    int N = 6; // Number of intersections (nodes)
    int graph[MAX_NODES][MAX_NODES] = { 0 };

    // Add roads (edges) to the graph
    // Format: graph[u][v] = weight
    graph[0][1] = 4; graph[1][0] = 4;
    graph[0][2] = 2; graph[2][0] = 2;
    graph[1][2] = 5; graph[2][1] = 5;
    graph[1][3] = 10; graph[3][1] = 10;
    graph[2][4] = 3; graph[4][2] = 3;
    graph[3][4] = 4; graph[4][3] = 4;
    graph[3][5] = 11; graph[5][3] = 11;
    graph[4][5] = 2; graph[5][4] = 2;

    // Identify bottlenecks
    identifyBottlenecks(graph, N);

    // Find shortest path between two intersections
    int source = 0, destination = 5;
    dijkstra(graph, N, source, destination);

    return 0;
}