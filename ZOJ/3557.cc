/*
 *  SRC: ZOJ 3557
 * PROB: How Many Sets II
 * ALGO: Combination
 * DATE: Aug 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

const int MAXM = 10010;
int MOD;

long long gpow(long long a, long long b)
{
    long long r = 1;
    for ( ; b; b >>= 1) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
    }
    return r;
}

int main()
{
    int n, m;
    while (~scanf("%d%d%d", &n, &m, &MOD)) {
        if (n - m - m + 1 > 0) {
            long long ans = 1;
            int cnt = 0;
            for (int i = 0; i < m; i++) {
                long long up = n - m - i + 1;
                long long down = i + 1;
                while (up % MOD == 0) { cnt++; up /= MOD; }
                while (down % MOD == 0) { cnt--; down /= MOD; }
                ans = ans * up % MOD * gpow(down, MOD - 2) % MOD;
            }
            printf("%lld\n", cnt > 0 ? 0 : ans);
        } else {
            puts("0");
        }
    }

    return 0;
}

