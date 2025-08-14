#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct State {
    int node;
    int pathCost;
    vector<int> pathTaken;
};

int totalVerts, edgeCount, beamW;
vector<vector<pair<int,int>>> adj;
vector<int> hVal;
vector<int> visitOrder;

struct StateCmp {
    bool operator()(const State &a, const State &b) const {
        int fA = a.pathCost + hVal[a.node];
        int fB = b.pathCost + hVal[b.node];
        return fA > fB;
    }
};

bool beamSearchRun(int start, int goal) {
    priority_queue<State, vector<State>, StateCmp> frontier;
    frontier.push({start, 0, {start}});
    visitOrder.push_back(start);

    while (!frontier.empty()) {
        vector<State> levelNodes;
        int taken = 0;
        while (!frontier.empty() && taken < beamW) {
            levelNodes.push_back(frontier.top());
            frontier.pop();
            taken++;
        }
        if (levelNodes.empty()) return false;

        priority_queue<State, vector<State>, StateCmp> nextFrontier;
        for (auto &cur : levelNodes) {
            if (cur.node == goal) {
                cout << "Path: ";
                for (size_t i = 0; i < cur.pathTaken.size(); i++) {
                    cout << cur.pathTaken[i];
                    if (i + 1 < cur.pathTaken.size()) cout << " -> ";
                }
                cout << "\nCost: " << cur.pathCost << "\n";

                cout << "Visited history: ";
                for (size_t i = 0; i < visitOrder.size(); i++) {
                    cout << visitOrder[i];
                    if (i + 1 < visitOrder.size()) cout << " -> ";
                }
                cout << "\n";
                return true;
            }
            for (auto &edge : adj[cur.node]) {
                vector<int> newPath = cur.pathTaken;
                newPath.push_back(edge.first);
                nextFrontier.push({edge.first, cur.pathCost + edge.second, newPath});
                visitOrder.push_back(edge.first);
            }
        }

        int pushed = 0;
        while (!nextFrontier.empty() && pushed < beamW) {
            frontier.push(nextFrontier.top());
            nextFrontier.pop();
            pushed++;
        }
    }
    return false;
}

int main() {
    totalVerts = 5;
    edgeCount = 6;
    adj.assign(totalVerts, {});
    hVal.assign(totalVerts, 0);

    // Hardcoded graph
    adj[0].push_back({1, 2});
    adj[0].push_back({2, 4});
    adj[1].push_back({0, 2});
    adj[1].push_back({3, 1});
    adj[2].push_back({0, 4});
    adj[2].push_back({4, 3});
    adj[3].push_back({1, 1});
    adj[4].push_back({2, 3});

    hVal = {5, 4, 7, 0, 6};
    beamW = 2;

    int startNode = 0;
    int goalNode = 3;

    visitOrder.clear();
    if (!beamSearchRun(startNode, goalNode))
        cout << "No path found\n";

    return 0;
}
