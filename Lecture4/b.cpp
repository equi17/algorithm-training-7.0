#include <iostream>
#include <queue>

using namespace std;

class Queue {
    queue<int> q;
public:
    void push(int n) {
        q.push(n);
        cout << "ok\n";
    }

    void pop() {
        if (q.empty()) {
            cout << "error\n";
            return;
        }
        cout << q.front() << '\n';
        q.pop();
    }

    void front() {
        if (q.empty()) {
            cout << "error\n";
            return;
        }
        cout << q.front() << '\n';
    }

    void size() {
        cout << q.size() << '\n';
    }

    void clear() {
        while (!q.empty()) q.pop();
        cout << "ok\n";
    }
};

int main() {
    Queue q;
    string op;
    while (cin >> op) {
        if (op == "push") {
            int n;
            cin >> n;
            q.push(n);
        }
        else if (op == "pop") {
            q.pop();
        }
        else if (op == "front") {
            q.front();
        }
        else if (op == "size") {
            q.size();
        }
        else if (op == "clear") {
            q.clear();
        }
        else if (op == "exit") {
            cout << "bye\n";
            return 0;
        }
    }
}