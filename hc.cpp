#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Link {
    int dest;
    int weight;
};

int totalNodes, totalEdges;
vector<vector<Link>> adj;
vector<int> hVals;
vector<int> prevNode;

bool hillClimbSearch(int startNode, int targetNode) {
    int currentNode = startNode;
    prevNode.assign(totalNodes, -1);

    while (currentNode != targetNode) {
        int chosenNode = -1;
        int smallestH = 1e9;

        for (auto &edge : adj[currentNode]) {
            if (hVals[edge.dest] < smallestH) {
                smallestH = hVals[edge.dest];
                chosenNode = edge.dest;
            }
        }

        if (chosenNode == -1 || hVals[chosenNode] >= hVals[currentNode]) {
            return false;
        }

        prevNode[chosenNode] = currentNode;
        currentNode = chosenNode;
    }
    return true;
}

void displayRoute(int targetNode) {
    vector<int> route;
    int temp = targetNode;
    int travelCost = 0;

    while (temp != -1) {
        route.push_back(temp);
        temp = prevNode[temp];
    }

    reverse(route.begin(), route.end());

    cout << "Path: ";
    for (int i = 0; i < (int)route.size(); i++) {
        cout << route[i];
        if (i != (int)route.size() - 1) cout << " -> ";
    }

    for (int i = 0; i + 1 < (int)route.size(); i++) {
        int from = route[i];
        int to = route[i + 1];
        for (auto &edge : adj[from]) {
            if (edge.dest == to) {
                travelCost += edge.weight;
                break;
            }
        }
    }
    cout << "\nCost: " << travelCost << "\n";
}

int main() {
    totalNodes = 5;
    totalEdges = 6;

    adj.assign(totalNodes, {});
    hVals.assign(totalNodes, 0);

    adj[0].push_back({1, 2});
    adj[0].push_back({2, 4});
    adj[1].push_back({0, 2});
    adj[1].push_back({3, 1});
    adj[2].push_back({0, 4});
    adj[2].push_back({4, 3});
    adj[3].push_back({1, 1});
    adj[4].push_back({2, 3});

    hVals = {5, 4, 7, 0, 6};

    int startNode = 0;
    int targetNode = 3;

    if (hillClimbSearch(startNode, targetNode))
        displayRoute(targetNode);
    else
        cout << "No path found\n";

    return 0;
}
