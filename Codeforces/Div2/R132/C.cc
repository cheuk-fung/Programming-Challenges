#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    int n, m, s;
    cin >> n >> m >> s;

    long long ans = 0;
    for (int a = 0; a * 2 < n; a++) {
        for (int b = 0; b * 2 < m; b++) {
            int area = (2 * a + 1) * (2 * b + 1);
            if (area < s) {
                if ((s - area) & 1) continue;
                for (int c = 0; c < a; c++) {
                    if ((s - area) % (2 * c + 1)) continue;
                    int d = (s - area) / 2 / (2 * c + 1) + b;
                    assert(d > 0);
                    int w = 2 * a + 1, h = 2 * d + 1;
                    if (w > n || h > m) continue;
                    ans += (n - w + 1) * (m - h + 1) * 2;
                }
            } else if (area == s) {
                int w = 2 * a + 1, h = 2 * b + 1;
                int mul = (a + 1) * (b + 1) * 2 - 1;
                ans += (n - w + 1) * (m - h + 1) * mul;
            }
        }
    }
    cout << ans << endl;

    return 0;
}
