#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct SearchState {
    int loc;
    int g;
    int h;
    vector<int> seq;
    bool operator>(const SearchState &other) const {
        return (g + h) > (other.g + other.h);
    }
};

int nodes, edges;
vector<vector<pair<int, int>>> adj;
vector<int> hScore;
vector<int> visitTrail;

bool heuristicBranchBound(int src, int dst) {
    priority_queue<SearchState, vector<SearchState>, greater<SearchState>> openSet;
    openSet.push({src, 0, hScore[src], {src}});
    visitTrail.push_back(src);

    while (!openSet.empty()) {
        SearchState now = openSet.top();
        openSet.pop();

        if (now.loc == dst) {
            cout << "Path: ";
            for (size_t i = 0; i < now.seq.size(); ++i) {
                cout << now.seq[i];
                if (i + 1 < now.seq.size()) cout << " -> ";
            }
            cout << "\nCost: " << now.g << "\n";
            cout << "Visited history: ";
            for (size_t i = 0; i < visitTrail.size(); ++i) {
                cout << visitTrail[i];
                if (i + 1 < visitTrail.size()) cout << " -> ";
            }
            cout << "\n";
            return true;
        }

        for (auto &nbr : adj[now.loc]) {
            bool seen = false;
            for (int step : now.seq) {
                if (step == nbr.first) {
                    seen = true;
                    break;
                }
            }
            if (!seen) {
                vector<int> newSeq = now.seq;
                newSeq.push_back(nbr.first);
                openSet.push({nbr.first, now.g + nbr.second, hScore[nbr.first], newSeq});
                visitTrail.push_back(nbr.first);
            }
        }
    }
    return false;
}

int main() {
    nodes = 5;
    edges = 6;
    adj.assign(nodes, {});
    hScore.assign(nodes, 0);

    // Hardcoded edges (undirected)
    adj.push_back({1, 2});
    adj.push_back({2, 4});
    adj.push_back({0, 2});
    adj.push_back({3, 1});
    adj.push_back({0, 4});
    adj.push_back({4, 3});
    adj.push_back({1, 1});
    adj.push_back({2, 3});

    // Hardcoded heuristic values
    hScore = {5, 4, 7, 0, 6};

    int startVertex = 0;
    int goalVertex = 3;

    visitTrail.clear();
    if (!heuristicBranchBound(startVertex, goalVertex))
        cout << "No path found\n";

    return 0;
}
