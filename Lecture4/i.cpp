#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> snowmen(N + 1, 0);
    vector<int> parent(N + 1, 0);
    vector<long long> weight(N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        int t, m;
        cin >> t >> m;
        if (m != 0) {
            snowmen[i] = m;
            parent[i] = t;
            weight[i] = weight[t] + m;
        } else {
            weight[i] = weight[t] - snowmen[t];
            snowmen[i] = snowmen[parent[t]];
            parent[i] = parent[parent[t]];
        }
    }

    long long sum = 0;
    for (int i = 1; i <= N; ++i)
        sum += weight[i];
    cout << sum << '\n';
}