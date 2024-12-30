//22520201
//Võ Thành Danh
//Session 06 - Exercise 16

#include <iostream>
#include <queue>
#include <cmath> // For abs()

using namespace std;

const int MAX_SIZE = 100;
const int INF = 1e9;

// Directions for moving in the grid (up, down, left, right)
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

// Node structure
struct Node {
    int x, y;
    int gCost, hCost;

    // Total cost fCost = gCost + hCost
    int fCost() const {
        return gCost + hCost;
    }
};

// Priority queue comparison
bool operator<(const Node& a, const Node& b) {
    return a.fCost() > b.fCost();
}

// Heuristic: Manhattan distance
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* Algorithm
void aStar(int grid[MAX_SIZE][MAX_SIZE], int rows, int cols, int startX, int startY, int goalX, int goalY) {
    // Cost and visited arrays
    int gCost[MAX_SIZE][MAX_SIZE];
    bool visited[MAX_SIZE][MAX_SIZE] = { false };
    pair<int, int> parent[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            gCost[i][j] = INF;
            parent[i][j] = { -1, -1 };
        }
    }

    priority_queue<Node> pq;
    gCost[startX][startY] = 0;
    pq.push({ startX, startY, 0, heuristic(startX, startY, goalX, goalY) });

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int x = current.x, y = current.y;

        if (visited[x][y]) continue;
        visited[x][y] = true;

        // Goal check
        if (x == goalX && y == goalY) {
            cout << "Path found:\n";
            vector<pair<int, int>> path;
            while (x != -1 && y != -1) {
                path.push_back({ x, y });
                tie(x, y) = parent[x][y];
            }

            // Output path
            for (int i = path.size() - 1; i >= 0; --i) {
                cout << "(" << path[i].first << ", " << path[i].second << ") ";
            }
            cout << endl;
            return;
        }

        // Explore neighbors
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 0 && !visited[nx][ny]) {
                int newGCost = gCost[x][y] + 1;

                if (newGCost < gCost[nx][ny]) {
                    gCost[nx][ny] = newGCost;
                    parent[nx][ny] = { x, y };
                    pq.push({ nx, ny, newGCost, heuristic(nx, ny, goalX, goalY) });
                }
            }
        }
    }

    cout << "No path found.\n";
}

int main() {
    int grid[MAX_SIZE][MAX_SIZE] = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0}
    };

    int rows = 5, cols = 5;
    int startX = 0, startY = 0; // Start position
    int goalX = 4, goalY = 4;   // Goal position

    aStar(grid, rows, cols, startX, startY, goalX, goalY);

    return 0;
}