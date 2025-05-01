#include <iostream>
#include <vector>

using namespace std;

int main() {
    unsigned int N;
    cin >> N;

    vector<unsigned int> res(N);
    vector<vector<unsigned int>> input(N, vector<unsigned int>(N));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> input[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            res[i] |= input[i][j];
            res[j] |= input[i][j];
        }
    }

    for (auto elem : res)
        cout << elem << ' ';
}