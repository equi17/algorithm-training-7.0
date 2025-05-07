#include <iostream>
#include <vector>

using namespace std;

class Stack {
    vector<int> st;
public:
    void push(int n) {
        st.push_back(n);
        cout << "ok\n";
    }

    void back() {
        if (st.size() == 0) {
            cout << "error\n";
            return;
        }
        cout << st.back() << '\n';
    }

    void pop() {
        if (st.size() == 0) {
            cout << "error\n";
            return;
        }
        cout << st.back() << '\n';
        st.pop_back();
    }

    void size() {
        cout << st.size() << '\n';
    }

    void clear() {
        st.clear();
        cout << "ok\n";
    }
};

int main() {
    Stack st;
    while(true) {
        string op;
        cin >> op;
        if (op == "push") {
            int n;
            cin >> n;
            st.push(n);
        }
        else if (op == "back") {
            st.back();
        }
        else if (op == "pop") {
            st.pop();
        }
        else if (op == "size") {
            st.size();
        }
        else if (op == "clear") {
            st.clear();
        }
        else if (op == "exit") {
            cout << "bye\n";
            return 0;
        }
    }
}
