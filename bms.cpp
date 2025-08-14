#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

struct Node {
    int vertex;
    int cost;
    vector<int> path;
    bool operator>(const Node &other) const {
        return cost > other.cost;
    }
};

int main() {
    int n = 5;
    vector<vector<pair<int, int>>> graph(n);
    graph[0].push_back({1, 2});
    graph[0].push_back({2, 4});
    graph[1].push_back({0, 2});
    graph[1].push_back({3, 1});
    graph[2].push_back({0, 4});
    graph[2].push_back({4, 3});
    graph[3].push_back({1, 1});
    graph[4].push_back({2, 3});

    int start = 0;
    int goal = 3;
    int beamWidth = 2;

    vector<Node> currentLevel;
    currentLevel.push_back({start, 0, {start}});

    bool found = false;
    vector<int> resultPath;
    int resultCost = numeric_limits<int>::max();

    while (!currentLevel.empty() && !found) {
        vector<Node> nextLevel;
        for (const auto &node : currentLevel) {
            if (node.vertex == goal) {
                found = true;
                if (node.cost < resultCost) {
                    resultCost = node.cost;
                    resultPath = node.path;
                }
                continue;
            }
            for (const auto &edge : graph[node.vertex]) {
                int nextVertex = edge.first;
                int newCost = node.cost + edge.second;
                if (find(node.path.begin(), node.path.end(), nextVertex) == node.path.end()) {
                    vector<int> newPath = node.path;
                    newPath.push_back(nextVertex);
                    nextLevel.push_back({nextVertex, newCost, newPath});
                }
            }
        }
        if (found) break;
        sort(nextLevel.begin(), nextLevel.end(), [](const Node &a, const Node &b) {
            return a.cost < b.cost;
        });
        if ((int)nextLevel.size() > beamWidth) {
            nextLevel.resize(beamWidth);
        }
        currentLevel = move(nextLevel);
    }

    if (found) {
        cout << "Path found: ";
        for (size_t i = 0; i < resultPath.size(); i++) {
            cout << resultPath[i];
            if (i + 1 < resultPath.size()) cout << " -> ";
        }
        cout << "\nTotal Cost: " << resultCost << "\n";
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
