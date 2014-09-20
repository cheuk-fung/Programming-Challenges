#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n, m;
    while (cin >> n >> m) {
        int a0, b0, t;
        cin >> a0;
        for (int i = 1; i <= n; i++) cin >> t;
        cin >> b0;
        for (int i = 1; i <= m; i++) cin >> t;
        if (n > m) {
            cout << (a0 * b0 < 0 ? "-" : "") << "Infinity" << endl;
        } else if (n < m) {
            cout << "0/1" << endl;
        } else {
            int r = __gcd(abs(a0), abs(b0));
            cout << (a0 * b0 < 0 ? "-" : "") << abs(a0) / r << "/" << abs(b0) / r << endl;
        }
    }

    return 0;
}

