#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Link {
    int node;
    int weight;
};

int vertexCount, edgeCount;
vector<vector<Link>> adjList;
vector<int> hScore;
vector<int> routeParent;
vector<int> visitOrder;

bool climbHill(int startV, int targetV) {
    int currentV = startV;
    routeParent.assign(vertexCount, -1);
    visitOrder.clear();
    visitOrder.push_back(currentV);

    while (currentV != targetV) {
        int bestNext = -1;
        int bestH = 1e9;

        for (auto &lnk : adjList[currentV]) {
            if (hScore[lnk.node] < bestH) {
                bestH = hScore[lnk.node];
                bestNext = lnk.node;
            }
        }

        if (bestNext == -1 || hScore[bestNext] >= hScore[currentV]) {
            return false;
        }

        routeParent[bestNext] = currentV;
        currentV = bestNext;
        visitOrder.push_back(currentV);
    }
    return true;
}

void showPathAndCost(int targetV) {
    vector<int> seq;
    int v = targetV;
    int totalCost = 0;

    while (v != -1) {
        seq.push_back(v);
        v = routeParent[v];
    }
    reverse(seq.begin(), seq.end());

    cout << "Path: ";
    for (size_t i = 0; i < seq.size(); i++) {
        cout << seq[i] << (i + 1 < seq.size() ? " -> " : "");
    }

    for (size_t i = 0; i + 1 < seq.size(); i++) {
        for (auto &lnk : adjList[seq[i]]) {
            if (lnk.node == seq[i + 1]) {
                totalCost += lnk.weight;
                break;
            }
        }
    }
    cout << "\nCost: " << totalCost << "\n";

    cout << "Visited history: ";
    for (size_t i = 0; i < visitOrder.size(); i++) {
        cout << visitOrder[i] << (i + 1 < visitOrder.size() ? " -> " : "");
    }
    cout << "\n";
}

int main() {
    vertexCount = 5;
    edgeCount = 6;

    adjList.assign(vertexCount, {});
    hScore.assign(vertexCount, 0);

    // Hardcoded edges
    adjList[0].push_back({1, 2});
    adjList[0].push_back({2, 4});
    adjList[1].push_back({0, 2});
    adjList[1].push_back({3, 1});
    adjList[2].push_back({0, 4});
    adjList[2].push_back({4, 3});
    adjList[3].push_back({1, 1});
    adjList[4].push_back({2, 3});

    hScore = {5, 4, 7, 0, 6};

    int startV = 0;
    int targetV = 3;

    if (climbHill(startV, targetV))
        showPathAndCost(targetV);
    else
        cout << "No path found\n";

    return 0;
}
