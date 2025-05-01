#include <iostream>

using namespace std;

int main() {
    int x1, y1;
    cin >> x1 >> y1;
    
    int x2, c;
    cin >> x2 >> c;
    
    cout << (x1 ^ y1) << '\n';
    cout << (x2 ^ c) << '\n';
}