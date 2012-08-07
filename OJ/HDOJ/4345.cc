/*
 *  SRC: HDOJ 4345
 * PROB: Permutation
 * ALGO: DP
 * DATE: Aug 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <cstring>

using namespace std;

long long f[1001][1001];
int prmcnt;
int prm[1001];
bool isprm[1001];

int getprm(int n, int *p, bool *b)
{
    memset(b, true, sizeof(bool) * n);
    b[0] = b[1] = false;
    int cnt = 0;
    for (int i = 2; i < n; i++) {
        if (b[i]) p[cnt++] = i;
        for (int j = 0; j < cnt && i * p[j] < n; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }
    return cnt;
}

long long dp(int n, int m)
{
    if (n == 0) return 1;
    if (f[n][m] != -1) return f[n][m];

    f[n][m] = 0;
    for (int i = m; i < prmcnt && prm[i] <= n; i++) {
        for (int j = prm[i]; j <= n; j *= prm[i]) {
            f[n][m] += dp(n - j, i + 1);
        }
    }

    return f[n][m];
}

int main()
{
    prmcnt = getprm(1001, prm, isprm);
    memset(f, 0xff, sizeof f);

    int n;
    while (cin >> n) {
        long long ans = 0;
        for (int i = 0; i <= n; i++) {
            ans += dp(i, 0);
        }
        cout << ans << endl;
    }

    return 0;
}

