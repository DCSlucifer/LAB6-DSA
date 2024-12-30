//22520201
//Võ Thành Danh
//Session 06 - Exercise 09

#include <iostream>
#include <cmath>
using namespace std;

const int MAX_N = 1000; // Adjust this value as needed
const double DAMPING_FACTOR = 0.85;
const double CONVERGENCE_THRESHOLD = 1e-6;

int edges[MAX_N][2];
int inLinks[MAX_N][MAX_N];
int outDegree[MAX_N];
double ranks[MAX_N];
double newRanks[MAX_N];

int main() {
    int N; int  E;
    int maxIterations = 100; // Define and initialize maxIterations

    // Initialize arrays
    for (int i = 0; i < MAX_N; ++i) {
        outDegree[i] = 0;
        ranks[i] = 1.0 / N;
        newRanks[i] = 0.0;
        for (int j = 0; j < MAX_N; ++j) {
            inLinks[i][j] = -1;
        }
    }

    // Read edges and initialize inLinks and outDegree
    for (int i = 0; i < E; ++i) {
        int from = edges[i][0];
        int to = edges[i][1];
        inLinks[to][outDegree[to]] = from;
        outDegree[from]++;
    }

    for (int iter = 0; iter < maxIterations; ++iter) {
        bool converged = true;

        for (int i = 0; i < N; ++i) {
            newRanks[i] = (1.0 - DAMPING_FACTOR) / N;
            for (int j = 0; j < outDegree[i]; ++j) {
                int from = inLinks[i][j];
                if (from != -1) {
                    newRanks[i] += DAMPING_FACTOR * (ranks[from] / outDegree[from]);
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (fabs(newRanks[i] - ranks[i]) > CONVERGENCE_THRESHOLD) {
                converged = false;
            }
            ranks[i] = newRanks[i];
        }

        if (converged) {
            cout << "hoi tu sau  " << iter + 1 << " lan lap " << endl;
            break;
        }
    }

    cout << "PageRanks cuoi cung :" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "Trang " << i << ": " << ranks[i] << endl;
    }

    return 0;
}