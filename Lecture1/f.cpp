#include <vector>
#include <iostream>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> items(N); // [mi, ci]

    for (int i = 0; i < N; ++i) {
        cin >> items[i].first;
    }
    for (int i = 0; i < N; ++i) {
        cin >> items[i].second;
    }
    
    vector<vector<int>> dp(N + 1, vector<int>(M + 1, 0));

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            int cost = items[i - 1].second;
            int weight = items[i - 1].first;
            if (j >= weight)
                dp[i][j] = max(dp[i - 1][j], cost + dp[i - 1][j - weight]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    int i = N;
    int j = M;
    vector<int> result;
    while(i > 0 && j > 0) {
        if (dp[i][j] != dp[i - 1][j]) { // item i was taken
            result.push_back(i); 
            j -= items[i - 1].first;
        }
        --i;        
    }

    for(auto& x: result)
        cout << x << '\n';
}