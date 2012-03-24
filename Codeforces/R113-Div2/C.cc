#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, x;
    while (cin >> n >> x) {
        vector<int> a;
        a.push_back(-1);
        for (int i = 0; i < n; i++) {
            int t;
            cin >> t;
            a.push_back(t);
        }

        int mid = (n + 1) >> 1;
        sort(a.begin(), a.end());

        int cnt = 0;
        while (a[mid] != x) {
            a.push_back(x);
            sort(a. begin(), a.end());
            mid = (++n + 1) >> 1;
            cnt++;
        }

        cout << cnt << endl;
    }

    return 0;
}

