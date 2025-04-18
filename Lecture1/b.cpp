#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void print(const vector<int>& vec) {
    for(auto& x : vec) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main() {
    int t;
    cin >> t;
    
    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;

        vector<int> segments;
        int segment_len = 0;
        int lowest_seg_value = INT_MAX;

        for (int j = 0; j < n; ++j) {
            int current;
            cin >> current;

            if (current < lowest_seg_value)
                lowest_seg_value = current;
            
            if (lowest_seg_value < segment_len + 1) {
                //cout << "!!\n";
                segments.push_back(segment_len);
                segment_len = 0;
                lowest_seg_value = current;
            }

            ++segment_len;
        }
        segments.push_back(segment_len);
        cout << segments.size() << '\n';
        print(segments);
    }
}