#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Link {
    int dest;
    int weight;
};

struct State {
    int node;
    int fVal;
    int gVal;
    bool operator>(const State &other) const {
        return fVal > other.fVal;
    }
};

int numNodes, numEdges;
vector<vector<Link>> adjList;
vector<int> hFunction;

vector<int> buildPath(unordered_map<int,int> &cameFrom, int end) {
    vector<int> seq;
    while (cameFrom.find(end) != cameFrom.end()) {
        seq.push_back(end);
        end = cameFrom[end];
    }
    seq.push_back(end);
    reverse(seq.begin(), seq.end());
    return seq;
}

bool runAStar(int start, int goal) {
    priority_queue<State, vector<State>, greater<State>> openSet;
    vector<int> gValue(numNodes, 1e9);
    unordered_map<int,int> prevMap;
    gValue[start] = 0;
    openSet.push({start, hFunction[start], 0});

    while (!openSet.empty()) {
        State curr = openSet.top();
        openSet.pop();
        if (curr.node == goal) {
            vector<int> seq = buildPath(prevMap, goal);
            cout << "Path: ";
            int total = 0;
            for (size_t i = 0; i < seq.size(); i++) {
                cout << seq[i];
                if (i + 1 < seq.size()) cout << " -> ";
            }
            for (size_t i = 0; i + 1 < seq.size(); i++) {
                int u = seq[i], v = seq[i + 1];
                for (auto &lnk : adjList[u]) {
                    if (lnk.dest == v) {
                        total += lnk.weight;
                        break;
                    }
                }
            }
            cout << "\nCost: " << total << "\n";
            return true;
        }
        for (auto &lnk : adjList[curr.node]) {
            int tempG = gValue[curr.node] + lnk.weight;
            if (tempG < gValue[lnk.dest]) {
                prevMap[lnk.dest] = curr.node;
                gValue[lnk.dest] = tempG;
                int newF = tempG + hFunction[lnk.dest];
                openSet.push({lnk.dest, newF, tempG});
            }
        }
    }
    return false;
}

int main() {
    numNodes = 5;
    numEdges = 6;
    adjList.assign(numNodes, {});
    hFunction.assign(numNodes, 0);

    // Hardcoded graph edges
    adjList.push_back({1, 2});
    adjList.push_back({2, 4});
    adjList.push_back({0, 2});
    adjList.push_back({3, 1});
    adjList.push_back({0, 4});
    adjList.push_back({4, 3});
    adjList.push_back({1, 1});
    adjList.push_back({2, 3});

    // Hardcoded heuristic values
    hFunction = {5, 4, 7, 0, 6};

    int sourceNode = 0;
    int destNode = 3;

    if (!runAStar(sourceNode, destNode))
        cout << "No path found\n";

    return 0;
}
