#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, x, y;
string mat[1010];
int f[1010][2];
int col[1010];

int dp(int now, int c)
{
    if (f[now][c] < INF) return f[now][c];

    for (int i = now - x; i >= max(now - y, 0); i--) {
        int cnt = col[now] - col[i];
        if (c == 1) cnt = n * (now - i) - cnt;
        f[now][c] = min(f[now][c], dp(i, c ^ 1) + cnt);
    }
    return f[now][c];
}

int main()
{
    cin >> n >> m >> x >> y;
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
    }
    for (int j = 0; j < m; j++) {
        col[j + 1] = col[j];
        for (int i = 0; i < n; i++) {
            if (mat[i][j] == '.') {
                col[j + 1]++;
            }
        }
    }
    memset(f, 0x3f, sizeof f);
    f[0][0] = f[0][1] = 0;
    int r = min(dp(m, 0), dp(m, 1));
    cout << r << endl;

    return 0;
}

