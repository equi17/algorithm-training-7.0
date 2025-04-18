#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> groups(N);
    for(int i = 0; i < N; ++i) {
        int students;
        cin >> students;
        groups[i].first = students + 1; // accounting for the teacher
        groups[i].second = i;
    }

    vector<pair<int, int>> classes(M); // [room_capacity, id]
    for(int i = 0; i < M; ++i) {
        cin >> classes[i].first;
        classes[i].second = i + 1;
    }

    sort(groups.begin(), groups.end(), std::greater<pair<int, int>>());
    sort(classes.begin(), classes.end(), std::greater<pair<int, int>>());

    int count = 0;
    vector<int> result(N, 0);
    int last_used_room = -1;

    for(auto& [group_size, group_idx]: groups) {
        if(last_used_room == M - 1) break; // have gone through all the rooms already
        int idx = last_used_room + 1;

        while(idx < M) {
            int room_cap = classes[idx].first;
            int room_id = classes[idx].second;
            if (group_size <= room_cap) {
                last_used_room = idx;
                result[group_idx] = room_id;
                ++count;
                break;
            }
            ++idx;
        }
    }

    cout << count << '\n';
    for(int i = 0; i < N; ++i) {
        cout << result[i] << '\n';
    }
}