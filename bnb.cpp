#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct PathState {
    int node;
    int totalCost;
    vector<int> steps;
    bool operator>(const PathState &other) const {
        return totalCost > other.totalCost;
    }
};

int vertexCount, edgeCount;
vector<vector<pair<int, int>>> adj;

bool branchBoundSearch(int src, int dst) {
    priority_queue<PathState, vector<PathState>, greater<PathState>> frontier;
    frontier.push({src, 0, {src}});

    while (!frontier.empty()) {
        PathState curr = frontier.top();
        frontier.pop();

        if (curr.node == dst) {
            cout << "Path: ";
            for (size_t i = 0; i < curr.steps.size(); ++i) {
                cout << curr.steps[i];
                if (i + 1 < curr.steps.size()) cout << " -> ";
            }
            cout << "\nCost: " << curr.totalCost << "\n";
            return true;
        }

        for (auto &edge : adj[curr.node]) {
            bool already = false;
            for (int prior : curr.steps) {
                if (prior == edge.first) {
                    already = true;
                    break;
                }
            }
            if (!already) {
                vector<int> newSteps = curr.steps;
                newSteps.push_back(edge.first);
                frontier.push({edge.first, curr.totalCost + edge.second, newSteps});
            }
        }
    }
    return false;
}

int main() {
    vertexCount = 5;
    edgeCount = 6;

    adj.assign(vertexCount, {});

    // Hardcoded edges (undirected)
    adj.push_back({1, 2});
    adj.push_back({2, 4});
    adj.push_back({0, 2});
    adj.push_back({3, 1});
    adj.push_back({0, 4});
    adj.push_back({4, 3});
    adj.push_back({1, 1});
    adj.push_back({2, 3});

    int source = 0;
    int destination = 3;

    if (!branchBoundSearch(source, destination))
        cout << "No path found\n";

    return 0;
}
