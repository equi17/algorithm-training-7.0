#include <vector>
#include <iostream>
#include <numeric>

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

    bool union_sets(int a, int b) { // by rank
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                ++rank[a];
            return true;
        }
        return false;
    }
};

int main() {
    int N, M;
    cin >> N >> M;

    DSU islands(N);
    int last_idx = -1;

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        bool success = islands.union_sets(u - 1, v - 1);
        if (success) {
            last_idx = i + 1;
        }
    }

    cout << last_idx;
}