#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int next_power_of_2(int n) {
    return pow(2, ceil(log2(n)));
}

pair<int, int> query_max_with_index(
    vector<int>& tree, 
    vector<int>& index,
    int query_left, int query_right,
    int seg_left, int seg_right,
    int idx
) {
    if (query_left <= seg_left && query_right >= seg_right)
        return { tree[idx], index[idx] };
    
    if (query_right < seg_left || query_left > seg_right)
        return { INT_MIN, 0 };

    int mid = (seg_left + seg_right) / 2;
    auto left_result = query_max_with_index(tree, index, query_left, query_right, seg_left, mid, 2 * idx + 1);
    auto right_result = query_max_with_index(tree, index, query_left, query_right, mid + 1, seg_right, 2 * idx + 2);

    if (left_result.first >= right_result.first)
        return left_result;
    else
        return right_result;
}

int main() {
    int n;
    cin >> n;
    int size = next_power_of_2(n);

    vector<int> tree(2 * size - 1, INT_MIN);
    vector<int> index(2 * size - 1, 0);

    for (int i = 0; i < n; ++i) {
        cin >> tree[size - 1 + i];
        index[size - 1 + i] = i + 1;
    }

    for (int i = size - 2; i >= 0; --i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (tree[left] >= tree[right]) {
            tree[i] = tree[left];
            index[i] = index[left];
        }
        else {
            tree[i] = tree[right];
            index[i] = index[right];
        }
    }

    int K;
    cin >> K;
    vector<int> results(K);

    for (int i = 0; i < K; ++i) {
        int L, R;
        cin >> L >> R;
        results[i] = query_max_with_index(tree, index, L, R, 1, size, 0).second;
    }

    for (auto& res : results)
        cout << res << '\n';
}
