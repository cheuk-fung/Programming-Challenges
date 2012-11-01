#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    int m, k;
    cin >> m >> k;
    vector<int> d, s;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        d.push_back(x);
    }
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        s.push_back(x);
    }
    s.push_back(0);

    int tm = 0, fuel = s[0];
    int mx = s[0];
    for (int i = 0; i < m; i++) {
        while (fuel < d[i]) {
            fuel += mx;
            tm += k;
        }
        fuel += s[i + 1] - d[i];
        tm += d[i];
        mx = max(mx, s[i + 1]);
    }
    cout << tm << endl;

    return 0;
}

