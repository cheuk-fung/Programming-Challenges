/*
 *  SRC: POJ 2992
 * PROB: Divisors
 * ALGO: Prime
 * DATE: Jul 13, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int sum, p[100], cnt[100];
bool b[500];

void prime()
{
    memset(b, true, sizeof(b));
    b[0] = b[1] = false;

    for (int i = 0; i < 500; i++) {
        if (b[i]) p[sum++] = i;
        for (int j = 0; j < sum && i * p[j] < 500; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }
}

void divide(int n, int k)
{
    memset(cnt, 0, sizeof(cnt));

    for (int i = 0; i < sum && n >= p[i]; i++) {
        int a = n, b = k, c = n - k;

        while (a > 1) {
            a /= p[i];
            cnt[i] += a;
        }

        while (b > 1) {
            b /= p[i];
            cnt[i] -= b;
        }

        while (c > 1) {
            c /= p[i];
            cnt[i] -= c;
        }
    }
}

bool solve()
{
    int n, k;
    if (scanf("%d%d", &n, &k) != 2) return false;
    divide(n, k);

    long long ans = 1;
    for (int i = 0; i < sum; i++)
        if (cnt[i]) ans *= (cnt[i] + 1LL);

    printf("%lld\n", ans);

    return true;
}

int main()
{
    prime();
    
    while (solve()) ;

    return 0;
}
