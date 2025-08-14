#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

struct NodeInfo {
    int id;
    int cost;
    vector<int> path;
};

void find_path_bfs(
    int num_vertices,
    const vector<vector<pair<int, int>>>& adj_list,
    int start_node,
    int goal_node
) {
    if (start_node < 0 || start_node >= num_vertices || goal_node < 0 || goal_node >= num_vertices) {
        cout << "Invalid start or goal node.\n";
        return;
    }

    queue<NodeInfo> q;
    vector<bool> visited(num_vertices, false);

    q.push({start_node, 0, {start_node}});
    visited[start_node] = true;

    bool path_found = false;
    NodeInfo result_info;

    while (!q.empty()) {
        NodeInfo current_info = q.front();
        q.pop();

        if (current_info.id == goal_node) {
            result_info = current_info;
            path_found = true;
            break;
        }

        for (const auto& edge : adj_list[current_info.id]) {
            int neighbor = edge.first;
            int weight = edge.second;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                NodeInfo neighbor_info;
                neighbor_info.id = neighbor;
                neighbor_info.cost = current_info.cost + weight;
                neighbor_info.path = current_info.path;
                neighbor_info.path.push_back(neighbor);
                q.push(neighbor_info);
            }
        }
    }

    if (path_found) {
        cout << "Path from " << start_node << " to " << goal_node << ": ";
        for (size_t i = 0; i < result_info.path.size(); ++i) {
            cout << result_info.path[i] << (i + 1 < result_info.path.size() ? " -> " : "");
        }
        cout << "\nTotal cost of the path: " << result_info.cost << "\n";
    } else {
        cout << "No path found from " << start_node << " to " << goal_node << ".\n";
    }
}

int main() {
    int num_vertices = 5;
    vector<vector<pair<int, int>>> adj_list(num_vertices);

    // Hardcoded graph (undirected with weights)
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

    find_path_bfs(num_vertices, adj_list, start_node, goal_node);

    return 0;
}
