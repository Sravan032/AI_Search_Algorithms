#include <iostream>
#include <vector>
#include <utility>
using namespace std;

bool dfs_with_history(
    int current_node,
    int goal_node,
    const vector<vector<pair<int, int>>>& adj_list,
    vector<bool>& visited,
    vector<int>& path_history,
    int& total_cost
) {
    visited[current_node] = true;
    path_history.push_back(current_node);

    if (current_node == goal_node) {
        return true;
    }

    for (const auto& edge : adj_list[current_node]) {
        int neighbor = edge.first;
        int weight = edge.second;
        if (!visited[neighbor]) {
            total_cost += weight;
            if (dfs_with_history(neighbor, goal_node, adj_list, visited, path_history, total_cost)) {
                return true;
            }
            total_cost -= weight;
        }
    }

    path_history.pop_back();
    return false;
}

int main() {
    int num_vertices = 5;
    vector<vector<pair<int, int>>> adj_list(num_vertices);

    // Hardcoded weighted undirected graph
    adj_list[0].push_back({1, 2});
    adj_list[0].push_back({2, 4});
    adj_list[1].push_back({0, 2});
    adj_list[1].push_back({3, 1});
    adj_list[2].push_back({0, 4});
    adj_list[2].push_back({4, 3});
    adj_list[3].push_back({1, 1});
    adj_list[4].push_back({2, 3});

    int start_node = 0;
    int goal_node = 3;

    vector<bool> visited(num_vertices, false);
    vector<int> path;
    int total_cost = 0;

    if (dfs_with_history(start_node, goal_node, adj_list, visited, path, total_cost)) {
        cout << "Path found: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << "\nTotal cost of the path: " << total_cost << "\n";
    } else {
        cout << "No path found from " << start_node << " to " << goal_node << ".\n";
    }

    return 0;
}
