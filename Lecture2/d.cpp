#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int next_power_of_2(int n) {
    return pow(2, ceil(log2(n)));
}

int query_max(
    vector<int>& tree,
    int query_left, int query_right,
    int seg_left, int seg_right,
    int idx
) {
    if (query_left <= seg_left && query_right >= seg_right)
        return tree[idx];
    
    if (query_right < seg_left || query_left > seg_right)
        return INT_MIN;

    int mid = (seg_left + seg_right) / 2;
    auto left_result = query_max(tree, query_left, query_right, seg_left, mid, 2 * idx + 1);
    auto right_result = query_max(tree, query_left, query_right, mid + 1, seg_right, 2 * idx + 2);

    if (left_result >= right_result)
        return left_result;
    else
        return right_result;
}

void sub_element(vector<int>& tree, int size, int pos, int new_value) {
    int idx = size - 1 + pos;
    tree[idx] = new_value;

    while (idx > 0) {
        idx = (idx - 1) / 2;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        tree[idx] = max(tree[left], tree[right]);
    }
}

int main() {
    int N;
    cin >> N;
    int size = next_power_of_2(N);

    vector<int> tree(2 * size - 1, INT_MIN);

    for (int i = 0; i < N; ++i) {
        cin >> tree[size - 1 + i];
    }

    for (int i = size - 2; i >= 0; --i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (tree[left] >= tree[right]) {
            tree[i] = tree[left];
        }
        else {
            tree[i] = tree[right];
        }
    }

    int K;
    cin >> K;
    vector<int> results;

    for (int i = 0; i < K; ++i) {
        char command;
        int L, R;
        cin >> command >> L >> R;
        if (command == 's')
            results.push_back(query_max(tree, L, R, 1, size, 0));
        else
            sub_element(tree, size, L - 1, R);
    }

    for (auto& res : results)
        cout << res << ' ';
}
