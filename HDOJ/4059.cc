/*
 *  SRC: HDOJ 4059
 * PROB: The Boss on Mars
 * ALGO: DP
 * DATE: Aug 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

const int MOD = 1000000007;
const int MAXP = 10010;

int prmcnt, prm[MAXP];
bool isprm[MAXP];

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

long long gpow(long long a, long long b)
{
    long long r = 1;
    while (b) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

inline long long sum(long long n) { return n * (n + 1) % MOD * (2 * n + 1) % MOD * (3 * n * n % MOD + 3 * n - 1) % MOD * gpow(30, MOD - 2) % MOD; }

int fac[32];

int divide(int n)
{
    int cnt = 0;
    for (int i = 0; i < prmcnt && prm[i] <= n; i++) {
        if (n % prm[i] == 0) {
            fac[cnt++] = prm[i];
            while (n % prm[i] == 0) n /= prm[i];
        }
    }
    if (n > 1) fac[cnt++] = n;
    return cnt;
}

int main()
{
    prmcnt = getprm(MAXP, prm, isprm);

    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        scanf("%d", &n);

        int fcnt = divide(n);
        long long ans = 0;
        for (int i = 0; i < 1 << fcnt; i++) {
            int bcnt = 0;
            long long t = 1;
            for (int j = 0; 1 << j <= i; j++) {
                if (i & (1 << j)) {
                    t = t * fac[j];
                    bcnt++;
                }
            }
            t = gpow(t, 4) * sum(n / t) % MOD;
            if (bcnt & 1) t = -t;
            ans = ((ans + t) % MOD + MOD) % MOD;
        }

        // printf("%lld\n", ans);
        printf("%I64d\n", ans);
    }

    return 0;
}

