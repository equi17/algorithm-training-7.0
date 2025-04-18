#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<vector<pair<int, int>>> bricks_by_color(K); // (length, id)
    for (int i = 0; i < N; ++i) {
        int l, c;
        cin >> l >> c;
        bricks_by_color[c - 1].emplace_back(l, i + 1);
    }

    int max_length = 0; // length of first wall
    for (auto& p : bricks_by_color[0]) {
        max_length += p.first;
    }

    vector<vector<int>> dp(K, vector<int>(max_length + 1, -1));
    // base case
    for (int i = 0; i < K; ++i) {
        dp[i][0] = 0;
    }

    for (int i = 0; i < K; ++i) {
        int m = bricks_by_color[i].size();
        for (int j = 0; j < m; ++j) {
            int len = bricks_by_color[i][j].first;
            for (int k = max_length - len; k >= 0; --k) {
                if (dp[i][k] != -1 && dp[i][k + len] == -1) {
                    dp[i][k + len] = j;
                }
            }
        }
    }

    int target_length = 0;
    for (int i = 1; i <= max_length; ++i) {
        bool ok = true;
        for (int j = 0; j < K; ++j) {
            if (dp[j][i] == -1) {
                ok = false;
                break;
            }
        }
        if (ok) {
            target_length = i;
            break;
        }
    }

    if (target_length == 0) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    vector<int> result;
    for (int i = 0; i < K; ++i) {
        int x = target_length;
        while (x > 0) {
            int idx = dp[i][x];
            result.push_back(bricks_by_color[i][idx].second);
            x -= bricks_by_color[i][idx].first;
        }
    }

    for (int br : result) {
        cout << br << ' ';
    }
}