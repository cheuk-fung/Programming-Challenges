/*
 *  SRC: POJ 2115
 * PROB: C Looooops
 * ALGO: Number Theory
 * DATE: Jul 13, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

long long gcd(long long a, long long b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long extendedEuclid(long long a, long long b, long long* x, long long* y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;

        return a;
    }

    long long r = extendedEuclid(b, a % b, x, y);
    long long t = *x;
    *x = *y;
    *y = t - a / b * *y;

    return r;
}

bool solve()
{
    long long a, b, c;
    int k;
    scanf("%lld%lld%lld%d", &a, &b, &c, &k);
    if ((a | b | c | k) == 0) return false;

    if (a == b) {
        puts("0");
        return true;
    }

    if (c == 0) {
        puts("FOREVER");
        return true;
    }

    const long long MOD = 1LL << k;

    long long x, y;
    long long g = extendedEuclid(c, MOD, &x, &y);

    if ((b - a) % g) puts("FOREVER");
    else {
        long long ans = (x * (b - a) / g) % (MOD / g);
        if (ans < 0) ans += (MOD / g);
        printf("%lld\n", ans);
    }

    return true;
}

int main()
{
    while (solve()) ;

    return 0;
}

