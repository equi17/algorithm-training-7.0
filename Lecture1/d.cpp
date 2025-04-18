#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> weights(N);

    for (int i = 0; i < N; ++i) {
        cin >> weights[i];
    }

    vector<bool> dp(M + 1, false);
    int max = 0;

    // base case
    dp[0] = true;

    for (int i = 0; i < N; ++i) {
        int idx = M - weights[i];
        while (idx > -1) {
            if (dp[idx]) {
                int step = idx + weights[i];
                dp[step] = true;
                if (step > max)
                    max = step;
            }
            --idx;
        }
    }
    cout << max;
}