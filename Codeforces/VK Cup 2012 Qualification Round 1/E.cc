#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

pii calls[4010];
int f[4010][4010];

int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> calls[i].first >> calls[i].second;
    calls[++n] = pii(86401, 0);

    int ans = 0;
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i][0] = max(f[i - 1][0], calls[i].first) + calls[i].second;
        for (int j = 1; j <= k; j++) {
            f[i][j] = min(f[i - 1][j - 1], max(f[i - 1][j], calls[i].first) + calls[i].second);
        }
        ans = max(ans, calls[i].first - f[i - 1][k]);
    }

    cout << ans << endl;

    return 0;
}

