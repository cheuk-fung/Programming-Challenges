#include <iostream>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 110;

int a[11];
int tot[11];
long long C[MAXN][MAXN];
long long f[MAXN][11];

int main()
{
    for (int i = 0; i < MAXN; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    int n;
    cin >> n;
    for (int i = 0; i < 10; i++) {
        cin >> a[i];
    }

    a[10] = a[0];
    for (int i = 1; i <= 10; i++) {
        tot[i] = tot[i - 1] + a[i];
    }

    for (int i = 0; i < 10; i++) f[0][i] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 10; j++) {
            if (a[j] == 0) f[i][j] = f[i][j - 1];
            for (int k = a[j]; tot[j - 1] + k <= i; k++) {
                for (int l = 1; l <= k; l++) {
                    f[i][j] = (f[i][j] + f[i - k][j - 1] * C[i - k + (j != 10)][l] % MOD * C[k - 1][l - 1] % MOD) % MOD;
                }
            }
        }
    }

    long long ans = 0;
    for (int i = tot[10]; i <= n; i++) {
        ans = (ans + f[i][10]) % MOD;
    }
    cout << ans << endl;

    return 0;
}

