#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
long long t, T, x, cost;

int main(int argc, char *argv[])
{
    cin >> n >> m;

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> t >> T >> x >> cost;
        if (T > t) {
            if (m <= T - t) {
                ans += cost;
            } else {
                long long cnt = m / (T - t);
                long long remain = m % (T - t);
                long long now = cnt * cost;
                if (remain) {
                    now += min((remain + T - t) * x, cost);
                }
                ans += min(now, cost + m * x);
            }
        } else {
            ans += cost + m * x;
        }
    }
    cout << ans << endl;

    return 0;
}
