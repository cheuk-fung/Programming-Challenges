#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    int n;
    while (cin >> n) {
        vector<int> v[3];
        int a[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] < 0 && v[0].size() == 0) {
                v[0].push_back(a[i]);
                a[i] = INT_MIN;
            } else if (a[i] > 0) {
                v[1].push_back(a[i]);
                a[i] = INT_MIN;
            }
        }
        if (v[1].empty()) {
            for (int i = 0; i < n; i++) {
                if (a[i] < 0 && a[i] != INT_MIN) {
                    v[1].push_back(a[i]);
                    a[i] = INT_MIN;
                }
                if (v[1].size() == 2) break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (a[i] != INT_MIN) {
                v[2].push_back(a[i]);
            }
        }
        for (int i = 0; i < 3; i++) {
            cout << v[i].size() << ' ';
            for (int j = 0; j < (int)v[i].size(); j++) {
                cout << v[i][j] << ' ';
            }
            cout << endl;
        }
    }

    return 0;
}
