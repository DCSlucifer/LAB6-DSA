//22520201
//Võ Thành Danh
//Session 06 - Exercise 14

#include <iostream>
#include <cmath> // For sqrt
#include <iomanip> // For formatted output

using namespace std;

const int MAX_USERS = 100;
const int MAX_ITEMS = 100;

// Function to calculate cosine similarity between two users
double cosineSimilarity(int user1[], int user2[], int numItems) {
    int dotProduct = 0, norm1 = 0, norm2 = 0;

    for (int i = 0; i < numItems; ++i) {
        dotProduct += user1[i] * user2[i];
        norm1 += user1[i] * user1[i];
        norm2 += user2[i] * user2[i];
    }

    if (norm1 == 0 || norm2 == 0) return 0.0; // Handle case of zero vectors
    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}

// Function to recommend items to a target user
void recommendItems(int targetUser, int userItemMatrix[MAX_USERS][MAX_ITEMS], int numUsers, int numItems) {
    double similarity[MAX_USERS] = { 0.0 };
    double itemScores[MAX_ITEMS] = { 0.0 };
    bool targetUserItems[MAX_ITEMS] = { false };

    // Record items already interacted with by the target user
    for (int i = 0; i < numItems; ++i) {
        if (userItemMatrix[targetUser][i] > 0) {
            targetUserItems[i] = true;
        }
    }

    // Calculate similarity between the target user and other users
    for (int u = 0; u < numUsers; ++u) {
        if (u != targetUser) {
            similarity[u] = cosineSimilarity(userItemMatrix[targetUser], userItemMatrix[u], numItems);
        }
    }

    // Calculate scores for items based on similar users
    for (int u = 0; u < numUsers; ++u) {
        if (u == targetUser) continue;

        for (int i = 0; i < numItems; ++i) {
            if (!targetUserItems[i] && userItemMatrix[u][i] > 0) {
                itemScores[i] += similarity[u] * userItemMatrix[u][i];
            }
        }
    }

    // Print recommendations
    cout << "Recommendations for User " << targetUser << ":\n";
    for (int i = 0; i < numItems; ++i) {
        if (!targetUserItems[i] && itemScores[i] > 0) {
            cout << "Item " << i << " with score " << fixed << setprecision(2) << itemScores[i] << endl;
        }
    }
}

int main() {
    // Example user-item interaction matrix (rows: users, columns: items)
    // 1 indicates interaction, 0 indicates no interaction
    int userItemMatrix[MAX_USERS][MAX_ITEMS] = {
        {1, 0, 1, 0, 0}, // User 0
        {0, 1, 1, 0, 1}, // User 1
        {1, 1, 0, 1, 0}, // User 2
        {0, 0, 1, 1, 1}  // User 3
    };

    int numUsers = 4;  // Number of users
    int numItems = 5;  // Number of items
    int targetUser = 0; // User for whom recommendations are generated

    recommendItems(targetUser, userItemMatrix, numUsers, numItems);

    return 0;
}