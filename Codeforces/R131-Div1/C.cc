#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int NEGINF = 0xc0c0c0c0;
const int MAXN = 300;

int n;
int mat[MAXN][MAXN];
int f[MAXN * 2][MAXN][MAXN];

int main()
{
    // cout << (sizeof f + sizeof mat) * 1.0 / 1024 / 1024 << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }

    memset(f, 0xc0, sizeof f);
    f[0][0][0] = mat[0][0];
    for (int i = 1; i <= (n - 1) * 2; i++) {
        for (int j = 0; j <= min(i, n - 1); j++) {
            for (int k = j; k <= min(i, n - 1); k++) {
                int now = mat[j][i - j] + mat[k][i - k] * (j != k);
                f[i][j][k] = max(f[i][j][k], f[i - 1][j][k] + now);
                if (j > 0) {
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k] + now);
                }
                if (k > 0) {
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - 1] + now);
                }
                if (j > 0 && k > 0) {
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - 1] + now);
                }
            }
        }
    }
    cout << f[(n - 1) * 2][n - 1][n - 1] << endl;

    return 0;
}

