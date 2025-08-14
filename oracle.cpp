#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

struct Link {
    int dest;
    int weight;
};

void shortestPathDijkstra(int startNode, int targetNode,
                          const vector<vector<Link>>& adjList,
                          vector<int>& prevNode, int& pathCost) {
    int N = adjList.size();
    vector<int> dist(N, numeric_limits<int>::max());
    prevNode.assign(N, -1);

    using NodePair = pair<int,int>; // distance, node
    priority_queue<NodePair, vector<NodePair>, greater<NodePair>> pq;

    dist[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
    pair<int,int> topPair = pq.top();
    int curCost = topPair.first;
    int u = topPair.second;
    pq.pop();
    
    if (curCost > dist[u]) continue;
    if (u == targetNode) break;

    for (auto &edge : adjList[u]) {
        int v = edge.dest;
        int newDist = curCost + edge.weight;
        if (newDist < dist[v]) {
            dist[v] = newDist;
            prevNode[v] = u;
            pq.push({newDist, v});
        }
    }
}

    pathCost = dist[targetNode];
}

int main() {
    int nodes = 5;
    vector<vector<Link>> adj(nodes);

    // Hardcoded undirected graph
    adj[0].push_back({1, 2});
    adj[0].push_back({2, 4});
    adj[1].push_back({0, 2});
    adj[1].push_back({3, 1});
    adj[2].push_back({0, 4});
    adj[2].push_back({4, 3});
    adj[3].push_back({1, 1});
    adj[4].push_back({2, 3});

    int startNode = 0;
    int targetNode = 3;

    vector<int> prevNode;
    int totalDistance = 0;

    shortestPathDijkstra(startNode, targetNode, adj, prevNode, totalDistance);

    vector<int> finalPath;
    for (int at = targetNode; at != -1; at = prevNode[at]) {
        finalPath.push_back(at);
    }
    reverse(finalPath.begin(), finalPath.end());

    if (finalPath.empty() || finalPath[0] != startNode || totalDistance == numeric_limits<int>::max()) {
        cout << "No path found from " << startNode << " to " << targetNode << "\n";
    } else {
        cout << "Shortest path: ";
        for (size_t i = 0; i < finalPath.size(); i++) {
            cout << finalPath[i];
            if (i + 1 < finalPath.size()) cout << " -> ";
        }
        cout << "\nTotal cost: " << totalDistance << "\n";
    }

    return 0;
}
