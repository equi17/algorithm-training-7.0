#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int next_power_of_2(int n) {
    return pow(2, ceil(log2(n)));
}

pair<int, int> query_min_with_count(
    vector<int>& tree, 
    vector<int>& count,
    int query_left, int query_right,
    int seg_left, int seg_right,
    int idx
) {
    if (query_left > query_right) return { INT_MAX, 0 };

    if (query_left <= seg_left && query_right >= seg_right)
        return { tree[idx], count[idx] };
    
    if (query_right < seg_left || query_left > seg_right)
        return { INT_MAX, 0 };

    int mid = (seg_left + seg_right) / 2;
    auto left_result = query_min_with_count(tree, count, query_left, query_right, seg_left, mid, 2 * idx + 1);
    auto right_result = query_min_with_count(tree, count, query_left, query_right, mid + 1, seg_right, 2 * idx + 2);

    if (left_result.first < right_result.first)
        return left_result;
    else if (left_result.first > right_result.first)
        return right_result;
    else
        return { left_result.first, left_result.second + right_result.second };
}

void update_element(vector<int>& tree, vector<int>& count, int size, int pos, int new_value) {
    int idx = size - 1 + pos;
    tree[idx] = new_value;

    while (idx > 0) {
        idx = (idx - 1) / 2;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        if (tree[left] < tree[right]) {
            tree[idx] = tree[left];
            count[idx] = count[left];
        }
        else if (tree[left] > tree[right]) {
            tree[idx] = tree[right];
            count[idx] = count[right];
        }
        else {
            tree[idx] = tree[left];
            count[idx] = count[left] + count[right];
        }
    }
}

int find_kth_zero(
    vector<int>& tree,
    vector<int>& count,
    int idx,
    int seg_left,
    int seg_right,
    int K,
    int L,
    int R
) {
    if (seg_right < L || seg_left > R || K <= 0) return -1;

    if (seg_left == seg_right) {
        if (tree[idx] == 0 && K == 1 && seg_left >= L && seg_right <= R)
            return seg_left;
        else
            return -1;
    }

    int mid = (seg_left + seg_right) / 2;
    int left_idx = 2 * idx + 1;
    int right_idx = 2 * idx + 2;

    int left_zeros = 0;
    if (tree[left_idx] == 0) {
        int left_seg_start = max(seg_left, L);
        int left_seg_end = min(mid, R);
        if (left_seg_start <= left_seg_end) {
            auto left_res = query_min_with_count(tree, count, left_seg_start, left_seg_end, seg_left, mid, left_idx);
            if (left_res.first == 0)
                left_zeros = left_res.second;
        }
    }

    if (left_zeros >= K) {
        return find_kth_zero(tree, count, left_idx, seg_left, mid, K, L, R);
    } else {
        return find_kth_zero(tree, count, right_idx, mid + 1, seg_right, K - left_zeros, L, R);
    }
}

int main() {
    int N;
    cin >> N;
    int size = next_power_of_2(N);

    vector<int> tree(2 * size - 1, INT_MAX);
    vector<int> count(2 * size - 1, 0);

    for (int i = 0; i < N; ++i) {
        cin >> tree[size - 1 + i];
        count[size - 1 + i] = 1;
    }

    for (int i = size - 2; i >= 0; --i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (tree[left] < tree[right]) {
            tree[i] = tree[left];
            count[i] = count[left];
        }
        else if (tree[left] > tree[right]) {
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
    vector<int> results;

    for (int i = 0; i < K; ++i) {
        char command;
        int L, R, C;
        cin >> command >> L >> R;
        if (command == 's') {
            cin >> C;
            int res = find_kth_zero(tree, count, 0, 0, size - 1, C, L - 1, R - 1);
            results.push_back(res == -1 ? -1 : res + 1);
        } else {
            update_element(tree, count, size, L - 1, R);
        }
    }

    for (auto& res : results)
        cout << res << ' ';
}