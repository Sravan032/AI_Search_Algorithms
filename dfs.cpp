#include <bits/stdc++.h>
using namespace std;

bool dfs_path(int current, int goal,
              const vector<vector<pair<int,int>>>& adj,
              vector<bool>& visited,
              int current_cost,
              vector<int>& current_path,
              vector<int>& final_path,
              int& final_cost) {
    
    visited[current] = true;
    current_path.push_back(current);

    // Goal found
    if (current == goal) {
        final_path = current_path;
        final_cost = current_cost;
        visited[current] = false; 
        current_path.pop_back();
        return true;
    }

    
    for (size_t i = 0; i < adj[current].size(); i++) {
        int neighbor = adj[current][i].first;
        int weight   = adj[current][i].second;

        if (!visited[neighbor]) {
            if (dfs_path(neighbor, goal, adj, visited,
                         current_cost + weight,
                         current_path, final_path, final_cost)) {
                visited[current] = false; 
                current_path.pop_back();
                return true; 
            }
        }
    }

    // Backtracking
    visited[current] = false;
    current_path.pop_back();
    return false;
}

int main() {
    int n = 5;
    vector<vector<pair<int, int>>> adj(n);
    
    adj[0].push_back({1, 2});
    adj[0].push_back({2, 4});
    adj[1].push_back({0, 2});
    adj[1].push_back({3, 1});
    adj[2].push_back({0, 4});
    adj[2].push_back({4, 3});
    adj[3].push_back({1, 1});
    adj[4].push_back({2, 3});

    int start_node = 0, goal_node = 3;

    vector<bool> visited(n, false);
    vector<int> current_path, final_path;
    int final_cost = 0;

    if (dfs_path(start_node, goal_node, adj, visited, 0, current_path, final_path, final_cost)) {
        cout << "Path from " << start_node << " to " << goal_node << ": ";
        for (size_t i = 0; i < final_path.size(); ++i) {
            cout << final_path[i] << (i + 1 == final_path.size() ? "" : " -> ");
        }
        cout << "\nTotal cost: " << final_cost << "\n";
    } else {
        cout << "No path found from " << start_node << " to " << goal_node << "\n";
    }

    return 0;
}
