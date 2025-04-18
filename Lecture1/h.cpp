#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int count_even(string& str) {
    int count = 0;;
    for (int i = 0; i < str.size(); ++i) {
        if (i % 2 == 0 && str[i] == 'S')
            ++count;
    }
    return count;
}

int count_odd(string& str) {
    int count = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (i % 2 == 1 && str[i] == 'S')
            ++count;
    }
    return count;
}

int main() {
    int N;
    cin >> N;

    vector<string> days(N);
    bool has_odd_len = false;
    for (int i = 0; i < N; ++i) {
        cin >> days[i];
        if (days[i].size() % 2 == 1) {
            has_odd_len = true;
        }
    }

    int res = 0;
    if (!has_odd_len) {
        for (auto& x : days) 
            res += count_even(x);
    } else {
        vector<pair<int, int>> odd;
        for (auto& x : days) {
            if (x.size() % 2 == 0) {
                res += max(count_even(x), count_odd(x));
            } else {
                odd.emplace_back(count_even(x), count_odd(x));
            }
        }

        sort(odd.begin(), odd.end(), [](pair<int, int> a, pair<int, int> b){ 
            return (a.first - a.second) < (b.first - b.second); 
        });

        int parity = 0;
        int left = 0;
        int right = odd.size() - 1;
        while (left <= right) {
            if (parity == 0) {
                res += odd[right].first;
                --right;
            } else {
                res += odd[left].second;
                ++left;
            }
            parity = 1 - parity;
        }
    }
    cout << res;
}
