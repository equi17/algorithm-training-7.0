#include <iostream>
#include <vector>

using namespace std;

struct FenwickTree {
    vector<long long> bit;
    int n;

    FenwickTree(int n) {
        bit.resize(n, 0);
        this->n = n;
    }

    long long sum(int r) {
        long long res = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            res += bit[r];
        return res;
    }

    long long sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for(; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

    void update(int idx, int num) {
        int old = sum(idx, idx);
        int delta = num - old;
        add(idx, delta);
    }
};

int main() {
    int N, K;
    cin >> N >> K;

    FenwickTree tree(N);

    vector<long long> queries;

    for (int i = 0; i < K; ++i) {
        char command;
        cin >> command;

        if (command == 'A') {
            int i, x;
            cin >> i >> x;
            tree.update(i - 1, x);
        }

        if (command == 'Q') {
            int l, r;
            cin >> l >> r;
            queries.push_back(tree.sum(l - 1, r - 1));
        }
    }

    for (long long x : queries)
        cout << x << '\n';
}