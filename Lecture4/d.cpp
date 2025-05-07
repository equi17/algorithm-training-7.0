#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();

    vector<string> res;
    vector<string> apps;

    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);

        if (line.find("Run") == 0) {
            string app_name;
            if (line.size() > 4) {
                app_name = line.substr(4);
            } else {
                app_name = "";
            }
            res.push_back(app_name);
            apps.insert(apps.begin(), app_name);
        } else {
            int tab_count = 0;
            size_t pos = 3;
            while ((pos = line.find("+Tab", pos)) != string::npos) {
                tab_count++;
                pos += 4;
            }

            int size = apps.size();
            if (size == 0) continue;
            int idx = tab_count % size;

            string app_name = apps[idx];
            apps.erase(apps.begin() + idx);
            apps.insert(apps.begin(), app_name);

            res.push_back(app_name);
        }
    }

    for (auto& elem : res)
        cout << elem << '\n';
}