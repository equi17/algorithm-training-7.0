#include <iostream>

using namespace std;

unsigned int bits(unsigned int num){
    int res = 0;

    while (num) {
        num >>= 1;
        ++res;
    }

    return res;
}

int main() {
    unsigned int N;
    cin >> N;
    unsigned int shift = N;

    unsigned int len = bits(N);
    unsigned int max = 0;

    do {
        unsigned int last_digit = (shift & 1) != 0 ? 1 : 0;
        shift >>= 1;
        shift |= last_digit << (len - 1);

        if (shift > max)
            max = shift;
    } while (shift != N);

    cout << max;
}