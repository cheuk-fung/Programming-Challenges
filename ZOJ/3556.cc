/*
 *  SRC: ZOJ 3556
 * PROB: How Many Sets I
 * ALGO: Combination
 * DATE: Aug 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>

const int MOD = 1000000007;

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
    int n, k;
    while (~scanf("%d%d", &n, &k)) {
        printf("%lld\n", gpow(((gpow(2, k) - 1) + MOD) % MOD, n));
    }

    return 0;
}

