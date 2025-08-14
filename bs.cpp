#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct State {
    int node;
    int gCost;
    vector<int> pathTaken;
};

int totalNodes, totalEdges, bw;
vector<vector<pair<int,int>>> adj;
vector<int> hVals;

struct StateCmp {
    bool operator()(const State &x, const State &y) const {
        int fX = x.gCost + hVals[x.node];
        int fY = y.gCost + hVals[y.node];
        return fX > fY;
    }
};

bool runBeamSearch(int startNode, int goalNode) {
    priority_queue<State, vector<State>, StateCmp> frontier;
    frontier.push({startNode, 0, {startNode}});

    while (!frontier.empty()) {
        vector<State> chosen;
        int taken = 0;
        while (!frontier.empty() && taken < bw) {
            chosen.push_back(frontier.top());
            frontier.pop();
            taken++;
        }
        if (chosen.empty()) return false;

        priority_queue<State, vector<State>, StateCmp> nextLevel;
        for (auto &cur : chosen) {
            if (cur.node == goalNode) {
                cout << "Path: ";
                for (size_t i = 0; i < cur.pathTaken.size(); i++) {
                    cout << cur.pathTaken[i];
                    if (i + 1 < cur.pathTaken.size()) cout << " -> ";
                }
                cout << "\nCost: " << cur.gCost << "\n";
                return true;
            }
            for (auto &nbr : adj[cur.node]) {
                vector<int> newP = cur.pathTaken;
                newP.push_back(nbr.first);
                nextLevel.push({nbr.first, cur.gCost + nbr.second, newP});
            }
        }

        int pushed = 0;
        while (!nextLevel.empty() && pushed < bw) {
            frontier.push(nextLevel.top());
            nextLevel.pop();
            pushed++;
        }
    }
    return false;
}

int main() {
    totalNodes = 5;
    totalEdges = 6;

    adj.assign(totalNodes, {});
    hVals.assign(totalNodes, 0);

    // Hardcoded edges
    adj[0].push_back({1, 2});
    adj[0].push_back({2, 4});
    adj[1].push_back({0, 2});
    adj[1].push_back({3, 1});
    adj[2].push_back({0, 4});
    adj[2].push_back({4, 3});
    adj[3].push_back({1, 1});
    adj[4].push_back({2, 3});

    hVals = {5, 4, 7, 0, 6};
    bw = 2;

    int startNode = 0;
    int goalNode = 3;

    if (!runBeamSearch(startNode, goalNode))
        cout << "No path found\n";

    return 0;
}
