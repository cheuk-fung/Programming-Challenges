#include <iostream>

using namespace std;

const int INF = 0x3f3f3f3f;

char mat[110][10010];
int f[110][10010];

int main()
{
    int n, m;
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++) {
            cin >> mat[i];
            for (int j = 0; j < m; j++) {
                f[i][j] = mat[i][j] == '1' ? 0 : INF;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m * 3; j++) {
                int now = j % m;
                int pre = (j - 1 + m) % m;
                f[i][now] = min(f[i][now], f[i][pre] + 1);
            }
            for (int j = m * 3; j >= 0; j--) {
                int now = j % m;
                int pre = (j + 1) % m;
                f[i][now] = min(f[i][now], f[i][pre] + 1);
            }
        }

        long long ans = INF;
        for (int j = 0; j < m; j++) {
            long long now = 0;
            for (int i = 0; i < n; i++) {
                now += f[i][j];
            }
            ans = min(ans, now);
        }

        cout << (ans == INF ? -1 : ans) << endl;
    }

    return 0;
}

