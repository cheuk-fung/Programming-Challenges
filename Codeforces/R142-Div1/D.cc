#include <iostream>
#include <algorithm>

using namespace std;

int h[5010], s[5010];
int f[5010][5010];

int main()
{
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + h[i];
    }

    f[1][1] = 0;
    for (int i = 2; i <= n; i++) f[1][i] = i - 1;
    for (int i = 1; i < n; i++) {
        int k = i;
        int cnt = n;
        for (int j = i + 1; j <= n; j++) {
            while (k > 0 && s[i] - s[k - 1] <= s[j] - s[i]) {
                cnt = min(cnt, f[k][i]);
                k--;
            }
            f[i + 1][j] = cnt + j - i - 1;
        }
    }

    int ans = n;
    for (int i = 1; i <= n; i++) ans = min(ans, f[i][n]);

    cout << ans << endl;

    return 0;
}
