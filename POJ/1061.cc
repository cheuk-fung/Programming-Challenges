/*
 *  SRC: POJ 1061
 * PROB: frog's dating
 * ALGO: Number Theory
 * DATE: May 10, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

long long extended_gcd(long long a, long long b, long long* x, long long* y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    else{
        long long res = extended_gcd(b, a % b, x, y);
        long long t = *x;
        *x = *y;
        *y = t - a / b * *y;
        return res;
    }
}

int main()
{
    long long x, y, m, n, L;
    while (scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &L) != EOF) {
        long long a = n - m, b = x - y, k, t;
        long long g = extended_gcd(a, L, &k, &t);
        if (b % g != 0) {
            puts("Impossible");
        }
        else {
            long long ans = ((k * b / g) % (L / g) + L / g) % (L / g);
            printf("%lld\n", ans);
        }
    }

    return 0;
}

