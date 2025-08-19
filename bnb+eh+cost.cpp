#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct SearchState {
    int position;
    int accumCost;
    vector<int> trace;
    bool operator>(const SearchState &other) const {
        return accumCost > other.accumCost;
    }
};

int nodeCount, edgeCount;
vector<vector<pair<int,int>>> adjMatrix;

bool runBranchBound(int src, int dest) {
    priority_queue<SearchState, vector<SearchState>, greater<SearchState>> openSet;
    openSet.push({src, 0, {src}});

    while (!openSet.empty()) {
        SearchState st = openSet.top();
        openSet.pop();

        if (st.position == dest) {
            cout << "Path: ";
            for (size_t i = 0; i < st.trace.size(); i++) {
                cout << st.trace[i];
                if (i + 1 < st.trace.size()) cout << " -> ";
            }
            cout << "\nCost: " << st.accumCost << "\n";
            return true;
        }
        for (auto &nbr : adjMatrix[st.position]) {
            bool wasVisited = false;
            for (int step : st.trace) {
                if (step == nbr.first) {
                    wasVisited = true;
                    break;
                }
            }
            if (!wasVisited) {
                vector<int> freshTrace = st.trace;
                freshTrace.push_back(nbr.first);
                openSet.push({nbr.first, st.accumCost + nbr.second, freshTrace});
            }
        }
    }
    return false;
}

int main() {
    nodeCount = 5;
    edgeCount = 6;
    adjMatrix.assign(nodeCount, {});

    // Hardcoded edges (undirected)
    adjMatrix.push_back({1, 2});
    adjMatrix.push_back({2, 4});
    adjMatrix.push_back({0, 2});
    adjMatrix.push_back({3, 1});
    adjMatrix.push_back({0, 4});
    adjMatrix.push_back({4, 3});
    adjMatrix.push_back({1, 1});
    adjMatrix.push_back({2, 3});

    int startingNode = 0;
    int goalNode = 3;

    if (!runBranchBound(startingNode, goalNode))
        cout << "No path found\n";

    return 0;
}
