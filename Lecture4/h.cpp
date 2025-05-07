#include <utility>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

class DSU {
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int size) { 
        parent.resize(size, 0);
        iota(parent.begin(), parent.end(), 0);

        rank.resize(size, 0);
    };

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]); //path compression
    }

    void union_sets(int a, int b) { // by rank
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                ++rank[a];
        }
    }
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    DSU islands(N);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
    }

    vector<pair<string, pair<int, int>>> commands(K);
    for (int i = 0; i < K; ++i) {
        string com;
        int u, v;
        cin >> com >> u >> v;
        if (u > v)
            swap(u, v);
        commands[i] = {com, {u, v} };
    }

    vector<string> result;

    for (int i = K - 1; i >= 0; --i) {
        const auto& [op, edge] = commands[i];
        const auto& [u, v] = edge;
        if (op == "cut") {
            islands.union_sets(u - 1, v - 1);
        } else if (op == "ask") {
            bool connected = (islands.find_set(u - 1) == islands.find_set(v - 1));
            result.push_back(connected ? "YES" : "NO");
        }
    }

    reverse(result.begin(), result.end());
    for (const string& ans : result) {
        cout << ans << '\n';
    }
}