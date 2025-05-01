#include <iostream>

using namespace std;

int main() {
    unsigned long long n;
    cin >> n;

    unsigned long long mask = 1;
    unsigned long long count = 0;
    
    while (n >= mask) {
        if (n & mask)
            ++count;
        mask = mask << 1;
    }

    cout << count;
}