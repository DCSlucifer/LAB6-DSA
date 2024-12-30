//22520201
//Võ Thành Danh
//Session 06 - Exercise 12
#include <iostream>
using namespace std;

const int MAX_USERS = 1000; // Adjust this value as needed

void dfs(int node, bool visited[], int graph[][MAX_USERS], int community[], int& communitySize) {
    visited[node] = true;
    community[communitySize++] = node;

    for (int i = 0; i < MAX_USERS; ++i) {
        if (graph[node][i] && !visited[i]) {
            dfs(i, visited, graph, community, communitySize);
        }
    }
}

void detectCommunities(int graph[][MAX_USERS], int N) {
    bool visited[MAX_USERS] = { 0 };
    int community[MAX_USERS];

    cout << "\nCommunities Detected:\n";
    int communityCount = 0;

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            int communitySize = 0;
            dfs(i, visited, graph, community, communitySize);

            // Print the community
            cout << "Community " << ++communityCount << ": ";
            for (int j = 0; j < communitySize; ++j) {
                cout << community[j] << " ";
            }
            cout << endl;
        }
    }
}

void calculateDegreeCentrality(int graph[][MAX_USERS], int N) {
    int degree[MAX_USERS] = { 0 };

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (graph[i][j]) {
                degree[i]++;
            }
        }
    }

    cout << "\nDegree Centrality:\n";
    for (int i = 0; i < N; ++i) {
        cout << "User " << i << ": " << degree[i] << endl;
    }
}

int main() {
    int N = 8;
    int graph[MAX_USERS][MAX_USERS] = { 0 };

    graph[0][1] = graph[0][2] = 1;
    graph[1][0] = graph[1][3] = 1;
    graph[2][0] = graph[2][3] = 1;
    graph[3][1] = graph[3][2] = 1;
    graph[4][5] = graph[4][6] = 1;
    graph[5][4] = graph[5][6] = 1;
    graph[6][4] = graph[6][5] = graph[6][7] = 1;
    graph[7][6] = 1;

    calculateDegreeCentrality(graph, N);
    detectCommunities(graph, N);

    return 0;
}