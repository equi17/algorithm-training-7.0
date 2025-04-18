#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int main() {
    long long M;
    cin >> M;

    vector<long long> cards(31);
    for (int i = 0; i < 31; ++i) {
        cin >> cards[i];
    }
    for (int i = 1; i < 31; ++i) {
        cards[i] = max(cards[i], 2 * cards[i - 1]);
    }
    
    long long cost = 0;
    long long res = LLONG_MAX;
    for (int i = 30; i >= 0; --i) {
        if (M <= cards[i]) {
            res = min((long long)pow(2, i) + cost, res);
        } else {
            cost += pow(2, i);
            M -= cards[i];
        }
    }
    cout << res;
}