#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int next_power_of_2(int n) {
    return pow(2, ceil(log2(n)));
}

pair<int, int> query_max_with_count(
    vector<int>& tree, 
    vector<int>& count,
    int query_left, int query_right,
    int seg_left, int seg_right,
    int idx
) {
    if (query_left <= seg_left && query_right >= seg_right)
        return { tree[idx], count[idx] };
    
    if (query_right < seg_left || query_left > seg_right)
        return { INT_MIN, 0 };

    int mid = (seg_left + seg_right) / 2;
    auto left_result = query_max_with_count(tree, count, query_left, query_right, seg_left, mid, 2 * idx + 1);
    auto right_result = query_max_with_count(tree, count, query_left, query_right, mid + 1, seg_right, 2 * idx + 2);

    if (left_result.first > right_result.first)
        return left_result;
    else if (left_result.first < right_result.first)
        return right_result;
    else
        return { left_result.first, left_result.second + right_result.second };
}

int main() {
    int n;
    cin >> n;
    int size = next_power_of_2(n);

    vector<int> tree(2 * size - 1, INT_MIN);
    vector<int> count(2 * size - 1, 0);

    for (int i = 0; i < n; ++i) {
        cin >> tree[size - 1 + i];
        count[size - 1 + i] = 1;
    }

    for (int i = size - 2; i >= 0; --i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (tree[left] > tree[right]) {
            tree[i] = tree[left];
            count[i] = count[left];
        }
        else if (tree[left] < tree[right]) {
            tree[i] = tree[right];
            count[i] = count[right];
        }
        else {
            tree[i] = tree[left];
            count[i] = count[left] + count[right];
        }
    }

    int K;
    cin >> K;
    vector<pair<int, int>> results(K);

    for (int i = 0; i < K; ++i) {
        int L, R;
        cin >> L >> R;
        results[i] = query_max_with_count(tree, count, L, R, 1, size, 0);
    }

    for (auto& res : results)
        cout << res.first << ' ' << res.second << '\n';
}
